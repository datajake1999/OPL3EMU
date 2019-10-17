#include "ReverbEffect.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <string.h>



/* This coefficient is used to define the maximum frequency range controlled
 * by the modulation depth.  The current value of 0.1 will allow it to swing
 * from 0.9x to 1.1x.  This value must be below 1.  At 1 it will cause the
 * sampler to stall on the downswing, and above 1 it will cause it to sample
 * backwards.
 */
static const float MODULATION_DEPTH_COEFF = 0.1f;

/* A filter is used to avoid the terrible distortion caused by changing
 * modulation time and/or depth.  To be consistent across different sample
 * rates, the coefficient must be raised to a constant divided by the sample
 * rate:  coeff^(constant / rate).
 */
static const float MODULATION_FILTER_COEFF = 0.048f;
static const float MODULATION_FILTER_CONST = 100000.0f;

// When diffusion is above 0, an all-pass filter is used to take the edge off
// the echo effect.  It uses the following line length (in seconds).
static const float ECHO_ALLPASS_LENGTH = 0.0133f;

// Input into the late reverb is decorrelated between four channels.  Their
// timings are dependent on a fraction and multiplier.  See the
// UpdateDecorrelator() routine for the calculations involved.
static const float DECO_FRACTION = 0.15f;
static const float DECO_MULTIPLIER = 2.0f;

// All delay line lengths are specified in seconds.

// The lengths of the early delay lines.
static const float EARLY_LINE_LENGTH[4] =
{
    0.0015f, 0.0045f, 0.0135f, 0.0405f
};

// The lengths of the late all-pass delay lines.
static const float ALLPASS_LINE_LENGTH[4] =
{
    0.0151f, 0.0167f, 0.0183f, 0.0200f,
};

// The lengths of the late cyclical delay lines.
static const float LATE_LINE_LENGTH[4] =
{
    0.0211f, 0.0311f, 0.0461f, 0.0680f
};

// The late cyclical delay lines have a variable length dependent on the
// effect's density parameter (inverted for some reason) and this multiplier.
static const float LATE_LINE_MULTIPLIER = 4.0f;



inline float lerp(float val1, float val2, float mu)
{
    return val1 + (val2-val1)*mu;
}

/* Find the next power-of-2 for non-power-of-2 numbers. */
inline uint32_t NextPowerOf2(uint32_t value)
{
    if(value > 0)
    {
        value--;
        value |= value>>1;
        value |= value>>2;
        value |= value>>4;
        value |= value>>8;
        value |= value>>16;
    }
    return value+1;
}

inline uint32_t Truncate(float f)
{
    return (uint32_t)f;
}

inline float minf(float a, float b)
{ return ((a > b) ? b : a); }

inline float maxf(float a, float b)
{ return ((a > b) ? a : b); }

inline float clampf(float val, float min, float max)
{ return minf(max, maxf(min, val)); }

inline uint32_t maxu(uint32_t a, uint32_t b)
{ return ((a > b) ? a : b); }


inline float FilterState_Process(FilterState *filter, float sample)
{
    float outsmp;

    outsmp = filter->b[0] * sample +
             filter->b[1] * filter->x[0] +
             filter->b[2] * filter->x[1] -
             filter->a[1] * filter->y[0] -
             filter->a[2] * filter->y[1];
    filter->x[1] = filter->x[0];
    filter->x[0] = sample;
    filter->y[1] = filter->y[0];
    filter->y[0] = outsmp;

    return outsmp;
}

void FilterState_clear(FilterState *filter)
{
    filter->x[0] = 0.0f;
    filter->x[1] = 0.0f;
    filter->y[0] = 0.0f;
    filter->y[1] = 0.0f;
}

void FilterState_setParams(FilterState *filter, FilterType type, float gain, float freq_mult, float bandwidth)
{
    float alpha;
    float w0;

    // Limit gain to -100dB
    gain = maxf(gain, 0.00001f);

    w0 = F_2PI * freq_mult;

    /* Calculate filter coefficients depending on filter type */
    switch(type)
    {
        case Filter_HighShelf:
            alpha = sinf(w0)/2.0f*sqrtf((gain + 1.0f/gain)*(1.0f/0.75f - 1.0f) + 2.0f);
            filter->b[0] =       gain*((gain+1.0f) + (gain-1.0f)*cosf(w0) + 2.0f*sqrtf(gain)*alpha);
            filter->b[1] = -2.0f*gain*((gain-1.0f) + (gain+1.0f)*cosf(w0)                         );
            filter->b[2] =       gain*((gain+1.0f) + (gain-1.0f)*cosf(w0) - 2.0f*sqrtf(gain)*alpha);
            filter->a[0] =             (gain+1.0f) - (gain-1.0f)*cosf(w0) + 2.0f*sqrtf(gain)*alpha;
            filter->a[1] =  2.0f*     ((gain-1.0f) - (gain+1.0f)*cosf(w0)                         );
            filter->a[2] =             (gain+1.0f) - (gain-1.0f)*cosf(w0) - 2.0f*sqrtf(gain)*alpha;
            break;
        case Filter_LowShelf:
            alpha = sinf(w0)/2.0f*sqrtf((gain + 1.0f/gain)*(1.0f/0.75f - 1.0f) + 2.0f);
            filter->b[0] =       gain*((gain+1.0f) - (gain-1.0f)*cosf(w0) + 2.0f*sqrtf(gain)*alpha);
            filter->b[1] =  2.0f*gain*((gain-1.0f) - (gain+1.0f)*cosf(w0)                         );
            filter->b[2] =       gain*((gain+1.0f) - (gain-1.0f)*cosf(w0) - 2.0f*sqrtf(gain)*alpha);
            filter->a[0] =             (gain+1.0f) + (gain-1.0f)*cosf(w0) + 2.0f*sqrtf(gain)*alpha;
            filter->a[1] = -2.0f*     ((gain-1.0f) + (gain+1.0f)*cosf(w0)                         );
            filter->a[2] =             (gain+1.0f) + (gain-1.0f)*cosf(w0) - 2.0f*sqrtf(gain)*alpha;
            break;
    }

    filter->b[2] /= filter->a[0];
    filter->b[1] /= filter->a[0];
    filter->b[0] /= filter->a[0];
    filter->a[2] /= filter->a[0];
    filter->a[1] /= filter->a[0];
    filter->a[0] /= filter->a[0];
}

void ReverbEffect::ComputeAmbientGains(float ingain, float gains[OUTPUT_CHANNELS])
{
    uint32_t i;

    for(i = 0;i < OUTPUT_CHANNELS;i++)
    {
        // The W coefficients are based on a mathematical average of the
        // output, scaled by sqrt(2) to compensate for FuMa-style Ambisonics
        // scaling the W channel input by sqrt(0.5). The square root of the
        // base average provides for a more perceptual average volume, better
        // suited to non-directional gains.
        gains[i] = sqrtf(ambiCoeffs[i][0]/1.4142f) * ingain;
    }
}

void ReverbEffect::ComputeDirectionalGains(const float dir[3], float ingain, float gains[OUTPUT_CHANNELS])
{
    float coeffs[MAX_AMBI_COEFFS];
    uint32_t i, j;
    /* Convert from OpenAL coords to Ambisonics. */
    float x = -dir[2];
    float y = -dir[0];
    float z =  dir[1];

    /* Zeroth-order */
    coeffs[0] = 0.7071f; /* W = sqrt(1.0 / 2.0) */
    /* First-order */
    coeffs[1] = y; /* Y = Y */
    coeffs[2] = z; /* Z = Z */
    coeffs[3] = x; /* X = X */

    for(i = 0;i < OUTPUT_CHANNELS;i++)
    {
        float gain = 0.0f;
        for(j = 0;j < MAX_AMBI_COEFFS;j++)
            gain += ambiCoeffs[i][j]*coeffs[j];
        gains[i] = gain * ingain;
    }
}


// Basic delay line input/output routines.
static inline float DelayLineOut(DelayLine *Delay, uint32_t offset)
{
    return Delay->Line[offset&Delay->Mask];
}

static inline void DelayLineIn(DelayLine *Delay, uint32_t offset, float in)
{
    Delay->Line[offset&Delay->Mask] = in;
}

// Attenuated delay line output routine.
static inline float AttenuatedDelayLineOut(DelayLine *Delay, uint32_t offset, float coeff)
{
    return coeff * Delay->Line[offset&Delay->Mask];
}

// Basic attenuated all-pass input/output routine.
static inline float AllpassInOut(DelayLine *Delay, uint32_t outOffset, uint32_t inOffset, float in, float feedCoeff, float coeff)
{
    float out, feed;

    out = DelayLineOut(Delay, outOffset);
    feed = feedCoeff * in;
    DelayLineIn(Delay, inOffset, (feedCoeff * (out - feed)) + in);

    // The time-based attenuation is only applied to the delay output to
    // keep it from affecting the feed-back path (which is already controlled
    // by the all-pass feed coefficient).
    return (coeff * out) - feed;
}

// Given an input sample, this function produces modulation for the late reverb.
inline float ReverbEffect::EAXModulation(float in)
{
    float sinus, frac;
    uint32_t offset;
    float out0, out1;

    // Calculate the sinus rythm (dependent on modulation time and the
    // sampling rate).  The center of the sinus is moved to reduce the delay
    // of the effect when the time or depth are low.
    sinus = 1.0f - cosf(F_2PI * this->Mod.Index / this->Mod.Range);

    // The depth determines the range over which to read the input samples
    // from, so it must be filtered to reduce the distortion caused by even
    // small parameter changes.
    this->Mod.Filter = lerp(this->Mod.Filter, this->Mod.Depth,
                             this->Mod.Coeff);

    // Calculate the read offset and fraction between it and the next sample.
    frac   = (1.0f + (this->Mod.Filter * sinus));
    offset = Truncate(frac);
    frac  -= offset;

    // Get the two samples crossed by the offset, and feed the delay line
    // with the next input sample.
    out0 = DelayLineOut(&this->Mod.Delay, this->Offset - offset);
    out1 = DelayLineOut(&this->Mod.Delay, this->Offset - offset - 1);
    DelayLineIn(&this->Mod.Delay, this->Offset, in);

    // Step the modulation index forward, keeping it bound to its range.
    this->Mod.Index = (this->Mod.Index + 1) % this->Mod.Range;

    // The output is obtained by linearly interpolating the two samples that
    // were acquired above.
    return lerp(out0, out1, frac);
}

// Delay line output routine for early reflections.
inline float ReverbEffect::EarlyDelayLineOut(uint32_t index)
{
    return AttenuatedDelayLineOut(&this->Early.Delay[index], this->Offset - this->Early.Offset[index], this->Early.Coeff[index]);
}

// Given an input sample, this function produces four-channel output for the  early reflections.
inline void ReverbEffect::EarlyReflection(float in, float *out)
{
    float d[4], v, f[4];

    // Obtain the decayed results of each early delay line.
    d[0] = this->EarlyDelayLineOut(0);
    d[1] = this->EarlyDelayLineOut(1);
    d[2] = this->EarlyDelayLineOut(2);
    d[3] = this->EarlyDelayLineOut(3);

    /* The following uses a lossless scattering junction from waveguide
     * theory.  It actually amounts to a householder mixing matrix, which
     * will produce a maximally diffuse response, and means this can probably
     * be considered a simple feed-back delay network (FDN).
     *          N
     *         ---
     *         \
     * v = 2/N /   d_i
     *         ---
     *         i=1
     */
    v = (d[0] + d[1] + d[2] + d[3]) * 0.5f;
    // The junction is loaded with the input here.
    v += in;

    // Calculate the feed values for the delay lines.
    f[0] = v - d[0];
    f[1] = v - d[1];
    f[2] = v - d[2];
    f[3] = v - d[3];

    // Re-feed the delay lines.
    DelayLineIn(&this->Early.Delay[0], this->Offset, f[0]);
    DelayLineIn(&this->Early.Delay[1], this->Offset, f[1]);
    DelayLineIn(&this->Early.Delay[2], this->Offset, f[2]);
    DelayLineIn(&this->Early.Delay[3], this->Offset, f[3]);

    // Output the results of the junction for all four channels.
    out[0] = this->Early.Gain * f[0];
    out[1] = this->Early.Gain * f[1];
    out[2] = this->Early.Gain * f[2];
    out[3] = this->Early.Gain * f[3];
}


// All-pass input/output routine for late reverb.
inline float ReverbEffect::LateAllPassInOut(uint32_t index, float in)
{
    return AllpassInOut(&this->Late.ApDelay[index], this->Offset - this->Late.ApOffset[index], this->Offset, in, this->Late.ApFeedCoeff, this->Late.ApCoeff[index]);
}

// Delay line output routine for late reverb.
inline float ReverbEffect::LateDelayLineOut(uint32_t index)
{
    return AttenuatedDelayLineOut(&this->Late.Delay[index], this->Offset - this->Late.Offset[index], this->Late.Coeff[index]);
}

// Low-pass filter input/output routine for late reverb.
inline float ReverbEffect::LateLowPassInOut(uint32_t index, float in)
{
    in = lerp(in, this->Late.LpSample[index], this->Late.LpCoeff[index]);
    this->Late.LpSample[index] = in;
    return in;
}

// Given four decorrelated input samples, this function produces four-channel output for the late reverb.
inline void ReverbEffect::LateReverb(const float *in, float *out)
{
    float d[4], f[4];

    // Obtain the decayed results of the cyclical delay lines, and add the
    // corresponding input channels.  Then pass the results through the
    // low-pass filters.

    // This is where the feed-back cycles from line 0 to 1 to 3 to 2 and back
    // to 0.
    d[0] = this->LateLowPassInOut(2, in[2] + this->LateDelayLineOut(2));
    d[1] = this->LateLowPassInOut(0, in[0] + this->LateDelayLineOut(0));
    d[2] = this->LateLowPassInOut(3, in[3] + this->LateDelayLineOut(3));
    d[3] = this->LateLowPassInOut(1, in[1] + this->LateDelayLineOut(1));

    // To help increase diffusion, run each line through an all-pass filter.
    // When there is no diffusion, the shortest all-pass filter will feed the
    // shortest delay line.
    d[0] = this->LateAllPassInOut(0, d[0]);
    d[1] = this->LateAllPassInOut(1, d[1]);
    d[2] = this->LateAllPassInOut(2, d[2]);
    d[3] = this->LateAllPassInOut(3, d[3]);

    /* Late reverb is done with a modified feed-back delay network (FDN)
     * topology.  Four input lines are each fed through their own all-pass
     * filter and then into the mixing matrix.  The four outputs of the
     * mixing matrix are then cycled back to the inputs.  Each output feeds
     * a different input to form a circlular feed cycle.
     *
     * The mixing matrix used is a 4D skew-symmetric rotation matrix derived
     * using a single unitary rotational parameter:
     *
     *  [  d,  a,  b,  c ]          1 = a^2 + b^2 + c^2 + d^2
     *  [ -a,  d,  c, -b ]
     *  [ -b, -c,  d,  a ]
     *  [ -c,  b, -a,  d ]
     *
     * The rotation is constructed from the effect's diffusion parameter,
     * yielding:  1 = x^2 + 3 y^2; where a, b, and c are the coefficient y
     * with differing signs, and d is the coefficient x.  The matrix is thus:
     *
     *  [  x,  y, -y,  y ]          n = sqrt(matrix_order - 1)
     *  [ -y,  x,  y,  y ]          t = diffusion_parameter * atan(n)
     *  [  y, -y,  x,  y ]          x = cos(t)
     *  [ -y, -y, -y,  x ]          y = sin(t) / n
     *
     * To reduce the number of multiplies, the x coefficient is applied with
     * the cyclical delay line coefficients.  Thus only the y coefficient is
     * applied when mixing, and is modified to be:  y / x.
     */
    f[0] = d[0] + (this->Late.MixCoeff * (         d[1] + -d[2] + d[3]));
    f[1] = d[1] + (this->Late.MixCoeff * (-d[0]         +  d[2] + d[3]));
    f[2] = d[2] + (this->Late.MixCoeff * ( d[0] + -d[1]         + d[3]));
    f[3] = d[3] + (this->Late.MixCoeff * (-d[0] + -d[1] + -d[2]       ));

    // Output the results of the matrix for all four channels, attenuated by
    // the late reverb gain (which is attenuated by the 'x' mix coefficient).
    out[0] = this->Late.Gain * f[0];
    out[1] = this->Late.Gain * f[1];
    out[2] = this->Late.Gain * f[2];
    out[3] = this->Late.Gain * f[3];

    // Re-feed the cyclical delay lines.
    DelayLineIn(&this->Late.Delay[0], this->Offset, f[0]);
    DelayLineIn(&this->Late.Delay[1], this->Offset, f[1]);
    DelayLineIn(&this->Late.Delay[2], this->Offset, f[2]);
    DelayLineIn(&this->Late.Delay[3], this->Offset, f[3]);
}

// Given an input sample, this function mixes echo into the four-channel late
// reverb.
inline void ReverbEffect::EAXEcho(float in, float *late)
{
    float out, feed;

    // Get the latest attenuated echo sample for output.
    feed = AttenuatedDelayLineOut(&this->Echo.Delay,
                                  this->Offset - this->Echo.Offset,
                                  this->Echo.Coeff);

    // Mix the output into the late reverb channels.
    out = this->Echo.MixCoeff[0] * feed;
    late[0] = (this->Echo.MixCoeff[1] * late[0]) + out;
    late[1] = (this->Echo.MixCoeff[1] * late[1]) + out;
    late[2] = (this->Echo.MixCoeff[1] * late[2]) + out;
    late[3] = (this->Echo.MixCoeff[1] * late[3]) + out;

    // Mix the energy-attenuated input with the output and pass it through
    // the echo low-pass filter.
    feed += this->Echo.DensityGain * in;
    feed = lerp(feed, this->Echo.LpSample, this->Echo.LpCoeff);
    this->Echo.LpSample = feed;

    // Then the echo all-pass filter.
    feed = AllpassInOut(&this->Echo.ApDelay,
                        this->Offset - this->Echo.ApOffset,
                        this->Offset, feed, this->Echo.ApFeedCoeff,
                        this->Echo.ApCoeff);

    // Feed the delay with the mixed and filtered sample.
    DelayLineIn(&this->Echo.Delay, this->Offset, feed);
}


// Perform the EAX reverb pass on a given input sample, resulting in four-channel output.
inline void ReverbEffect::EAXVerbPass(float in, float *early, float *late)
{
    float feed, taps[4];

    // Low-pass filter the incoming sample.
    in = FilterState_Process(&this->LpFilter, in);
    in = FilterState_Process(&this->HpFilter, in);

    // Perform any modulation on the input.
    in = this->EAXModulation(in);

    // Feed the initial delay line.
    DelayLineIn(&this->Delay, this->Offset, in);

    // Calculate the early reflection from the first delay tap.
    in = DelayLineOut(&this->Delay, this->Offset - this->DelayTap[0]);
    this->EarlyReflection(in, early);

    // Feed the decorrelator from the energy-attenuated output of the second
    // delay tap.
    in = DelayLineOut(&this->Delay, this->Offset - this->DelayTap[1]);
    feed = in * this->Late.DensityGain;
    DelayLineIn(&this->Decorrelator, this->Offset, feed);

    // Calculate the late reverb from the decorrelator taps.
    taps[0] = feed;
    taps[1] = DelayLineOut(&this->Decorrelator, this->Offset - this->DecoTap[0]);
    taps[2] = DelayLineOut(&this->Decorrelator, this->Offset - this->DecoTap[1]);
    taps[3] = DelayLineOut(&this->Decorrelator, this->Offset - this->DecoTap[2]);
    this->LateReverb(taps, late);

    // Calculate and mix in any echo.
    this->EAXEcho(in, late);

    // Step all delays forward one sample.
    this->Offset++;
}

void ReverbEffect::Process(uint32_t SamplesToDo, const float *SamplesIn, float *SamplesOut)
{
    float (*early)[4] = this->EarlySamples;
    float (*late)[4] = this->ReverbSamples;
    uint32_t index, c;

    /* Process reverb for these samples. */
    for(index = 0;index < SamplesToDo;index++)
        this->EAXVerbPass(SamplesIn[index], early[index], late[index]);

    for(c = 0;c < OUTPUT_CHANNELS ; c++)
    {
        float earlyGain, lateGain;

        earlyGain = this->Early.PanGain[c];
        if(fabsf(earlyGain) > GAIN_SILENCE_THRESHOLD)
        {
            for(index = 0;index < SamplesToDo;index++)
                SamplesOut[index * 2 + c] = earlyGain*early[index][c&3];
        }


        lateGain = this->Late.PanGain[c];
        if(fabsf(lateGain) > GAIN_SILENCE_THRESHOLD)
        {
            for(index = 0;index < SamplesToDo;index++)
                SamplesOut[index * 2 + c] = lateGain*late[index][c&3];
        }
    }
}

// Given the allocated sample buffer, this function updates each delay line offset.
static inline void RealizeLineOffset(float *sampleBuffer, DelayLine *Delay)
{
    Delay->Line = &sampleBuffer[(ptrdiff_t)Delay->Line];
}

// Calculate the length of a delay line and store its mask and offset.
static uint32_t CalcLineLength(float length, ptrdiff_t offset, uint32_t frequency, DelayLine *Delay)
{
    uint32_t samples;

    // All line lengths are powers of 2, calculated from their lengths, with
    // an additional sample in case of rounding errors.
    samples = NextPowerOf2(Truncate(length * frequency) + 1);
    // All lines share a single sample buffer.
    Delay->Mask = samples - 1;
    Delay->Line = (float*)offset;
    // Return the sample count for accumulation.
    return samples;
}

// Calculates the delay line metrics and allocates the shared sample buffer for all lines given the sample rate (frequency).
void ReverbEffect::AllocLines(uint32_t frequency)
{
    uint32_t totalSamples, index;
    float length;

    // All delay line lengths are calculated to accomodate the full range of lengths given their respective paramters.
    totalSamples = 0;

    /* The modulator's line length is calculated from the maximum modulation
     * time and depth coefficient, and halfed for the low-to-high frequency
     * swing.  An additional sample is added to keep it stable when there is no modulation.
     */
    length = (EAXREVERB_MAX_MODULATION_TIME*MODULATION_DEPTH_COEFF/2.0f) + (1.0f / frequency);
    totalSamples += CalcLineLength(length, totalSamples, frequency, &this->Mod.Delay);

    // The initial delay is the sum of the reflections and late reverb delays.
    length = EAXREVERB_MAX_REFLECTIONS_DELAY + EAXREVERB_MAX_LATE_REVERB_DELAY;
    totalSamples += CalcLineLength(length, totalSamples, frequency, &this->Delay);

    // The early reflection lines.
    for(index = 0;index < 4;index++)
        totalSamples += CalcLineLength(EARLY_LINE_LENGTH[index], totalSamples, frequency, &this->Early.Delay[index]);

    // The decorrelator line is calculated from the lowest reverb density (a
    // parameter value of 1).
    length = (DECO_FRACTION * DECO_MULTIPLIER * DECO_MULTIPLIER) * LATE_LINE_LENGTH[0] * (1.0f + LATE_LINE_MULTIPLIER);
    totalSamples += CalcLineLength(length, totalSamples, frequency, &this->Decorrelator);

    // The late all-pass lines.
    for(index = 0;index < 4;index++)
        totalSamples += CalcLineLength(ALLPASS_LINE_LENGTH[index], totalSamples, frequency, &this->Late.ApDelay[index]);

    // The late delay lines are calculated from the lowest reverb density.
    for(index = 0;index < 4;index++)
    {
        length = LATE_LINE_LENGTH[index] * (1.0f + LATE_LINE_MULTIPLIER);
        totalSamples += CalcLineLength(length, totalSamples, frequency, &this->Late.Delay[index]);
    }

    // The echo all-pass and delay lines.
    totalSamples += CalcLineLength(ECHO_ALLPASS_LENGTH, totalSamples, frequency, &this->Echo.ApDelay);
    totalSamples += CalcLineLength(EAXREVERB_MAX_ECHO_TIME, totalSamples, frequency, &this->Echo.Delay);

    float* newBuf = new float[totalSamples];
    this->SampleBuffer = newBuf;
    this->TotalSamples = totalSamples;

    // Update all delays to reflect the new sample buffer.
    RealizeLineOffset(this->SampleBuffer, &this->Delay);
    RealizeLineOffset(this->SampleBuffer, &this->Decorrelator);
    for(index = 0;index < 4;index++)
    {
        RealizeLineOffset(this->SampleBuffer, &this->Early.Delay[index]);
        RealizeLineOffset(this->SampleBuffer, &this->Late.ApDelay[index]);
        RealizeLineOffset(this->SampleBuffer, &this->Late.Delay[index]);
    }
    RealizeLineOffset(this->SampleBuffer, &this->Mod.Delay);
    RealizeLineOffset(this->SampleBuffer, &this->Echo.ApDelay);
    RealizeLineOffset(this->SampleBuffer, &this->Echo.Delay);

    // Clear the sample buffer.
    for(index = 0;index < this->TotalSamples;index++)
        this->SampleBuffer[index] = 0.0f;
}

// Calculate a decay coefficient given the length of each cycle and the time until the decay reaches -60 dB.
static inline float CalcDecayCoeff(float length, float decayTime)
{
    return powf(0.001f/*-60 dB*/, length/decayTime);
}

// Calculate a decay length from a coefficient and the time until the decay reaches -60 dB.
static inline float CalcDecayLength(float coeff, float decayTime)
{
    return log10f(coeff) * decayTime / log10f(0.001f)/*-60 dB*/;
}

// Calculate an attenuation to be applied to the input of any echo models to
// compensate for modal density and decay time.
static inline float CalcDensityGain(float a)
{
    /* The energy of a signal can be obtained by finding the area under the
     * squared signal.  This takes the form of Sum(x_n^2), where x is the
     * amplitude for the sample n.
     *
     * Decaying feedback matches exponential decay of the form Sum(a^n),
     * where a is the attenuation coefficient, and n is the sample.  The area
     * under this decay curve can be calculated as:  1 / (1 - a).
     *
     * Modifying the above equation to find the squared area under the curve
     * (for energy) yields:  1 / (1 - a^2).  Input attenuation can then be
     * calculated by inverting the square root of this approximation,
     * yielding:  1 / sqrt(1 / (1 - a^2)), simplified to: sqrt(1 - a^2).
     */
    return sqrtf(1.0f - (a * a));
}

// Calculate the mixing matrix coefficients given a diffusion factor.
static inline void CalcMatrixCoeffs(float diffusion, float *x, float *y)
{
    float n, t;

    // The matrix is of order 4, so n is sqrt (4 - 1).
    n = sqrtf(3.0f);
    t = diffusion * atanf(n);

    // Calculate the first mixing matrix coefficient.
    *x = cosf(t);
    // Calculate the second mixing matrix coefficient.
    *y = sinf(t) / n;
}

// Calculate the limited HF ratio for use with the late reverb low-pass filters.
static float CalcLimitedHfRatio(float hfRatio, float airAbsorptionGainHF, float decayTime)
{
    float limitRatio;

    /* Find the attenuation due to air absorption in dB (converting delay
     * time to meters using the speed of sound).  Then reversing the decay
     * equation, solve for HF ratio.  The delay length is cancelled out of
     * the equation, so it can be calculated once for all lines.
     */
    limitRatio = 1.0f / (CalcDecayLength(airAbsorptionGainHF, decayTime) * SPEEDOFSOUNDMETRESPERSEC);
    /* Using the limit calculated above, apply the upper bound to the HF
     * ratio. Also need to limit the result to a minimum of 0.1, just like the
     * HF ratio parameter. */
    return clampf(limitRatio, 0.1f, hfRatio);
}

// Calculate the coefficient for a HF (and eventually LF) decay damping filter.
static inline float CalcDampingCoeff(float hfRatio, float length, float decayTime, float decayCoeff, float cw)
{
    float coeff, g;

    // Eventually this should boost the high frequencies when the ratio
    // exceeds 1.
    coeff = 0.0f;
    if (hfRatio < 1.0f)
    {
        // Calculate the low-pass coefficient by dividing the HF decay
        // coefficient by the full decay coefficient.
        g = CalcDecayCoeff(length, decayTime * hfRatio) / decayCoeff;

        // Damping is done with a 1-pole filter, so g needs to be squared.
        g *= g;
        if(g < 0.9999f) /* 1-epsilon */
        {
            /* Be careful with gains < 0.001, as that causes the coefficient
             * head towards 1, which will flatten the signal. */
            g = maxf(g, 0.001f);
            coeff = (1 - g*cw - sqrtf(2*g*(1-cw) - g*g*(1 - cw*cw))) /
                    (1 - g);
        }

        // Very low decay times will produce minimal output, so apply an
        // upper bound to the coefficient.
        coeff = minf(coeff, 0.98f);
    }
    return coeff;
}

// Update the EAX modulation index, range, and depth.
// Keep in mind that this kind of vibrato is additive and not multiplicative as one may expect.
// The downswing will sound stronger than the upswing.
void ReverbEffect::UpdateModulator(float modTime, float modDepth, uint32_t frequency)
{
    uint32_t range;

    /* Modulation is calculated in two parts.
     *
     * The modulation time effects the sinus applied to the change in
     * frequency.  An index out of the current time range (both in samples)
     * is incremented each sample.  The range is bound to a reasonable
     * minimum (1 sample) and when the timing changes, the index is rescaled
     * to the new range (to keep the sinus consistent).
     */
    range = maxu(Truncate(modTime*frequency), 1);
    this->Mod.Index = (uint32_t)(this->Mod.Index * (uint64_t)range / this->Mod.Range);
    this->Mod.Range = range;

    /* The modulation depth effects the amount of frequency change over the
     * range of the sinus.  It needs to be scaled by the modulation time so
     * that a given depth produces a consistent change in frequency over all
     * ranges of time.  Since the depth is applied to a sinus value, it needs
     * to be halfed once for the sinus range and again for the sinus swing
     * in time (half of it is spent decreasing the frequency, half is spent
     * increasing it).
     */
    this->Mod.Depth = modDepth * MODULATION_DEPTH_COEFF * modTime / 2.0f /
                       2.0f * frequency;
}

// Update the offsets for the initial effect delay line.
void ReverbEffect::UpdateDelayLine(float earlyDelay, float lateDelay, uint32_t frequency)
{
    // Calculate the initial delay taps.
    this->DelayTap[0] = Truncate(earlyDelay * frequency);
    this->DelayTap[1] = Truncate((earlyDelay + lateDelay) * frequency);
}

// Update the early reflections gain and line coefficients.
void ReverbEffect::UpdateEarlyLines(float reverbGain, float earlyGain, float lateDelay)
{
    uint32_t index;

    // Calculate the early reflections gain (from the master effect gain, and
    // reflections gain parameters) with a constant attenuation of 0.5.
    this->Early.Gain = 0.5f * reverbGain * earlyGain;

    // Calculate the gain (coefficient) for each early delay line using the
    // late delay time.  This expands the early reflections to the start of
    // the late reverb.
    for(index = 0;index < 4;index++)
        this->Early.Coeff[index] = CalcDecayCoeff(EARLY_LINE_LENGTH[index],
                                                   lateDelay);
}

// Update the offsets for the decorrelator line.
void ReverbEffect::UpdateDecorrelator(float density, uint32_t frequency)
{
    uint32_t index;
    float length;

    /* The late reverb inputs are decorrelated to smooth the reverb tail and
     * reduce harsh echos.  The first tap occurs immediately, while the
     * remaining taps are delayed by multiples of a fraction of the smallest
     * cyclical delay time.
     *
     * offset[index] = (FRACTION (MULTIPLIER^index)) smallest_delay
     */
    for(index = 0;index < 3;index++)
    {
        length = (DECO_FRACTION * powf(DECO_MULTIPLIER, (float)index)) *
                 LATE_LINE_LENGTH[0] * (1.0f + (density * LATE_LINE_MULTIPLIER));
        this->DecoTap[index] = Truncate(length * frequency);
    }
}

// Update the late reverb gains, line lengths, and line coefficients.
void ReverbEffect::UpdateLateLines(float reverbGain, float lateGain, float xMix, float density, float decayTime, float diffusion, float hfRatio, float cw, uint32_t frequency)
{
    float length;
    uint32_t index;

    /* Calculate the late reverb gain (from the master effect gain, and late
     * reverb gain parameters).  Since the output is tapped prior to the
     * application of the next delay line coefficients, this gain needs to be
     * attenuated by the 'x' mixing matrix coefficient as well.
     */
    this->Late.Gain = reverbGain * lateGain * xMix;

    /* To compensate for changes in modal density and decay time of the late
     * reverb signal, the input is attenuated based on the maximal energy of
     * the outgoing signal.  This approximation is used to keep the apparent
     * energy of the signal equal for all ranges of density and decay time.
     *
     * The average length of the cyclcical delay lines is used to calculate
     * the attenuation coefficient.
     */
    length = (LATE_LINE_LENGTH[0] + LATE_LINE_LENGTH[1] +
              LATE_LINE_LENGTH[2] + LATE_LINE_LENGTH[3]) / 4.0f;
    length *= 1.0f + (density * LATE_LINE_MULTIPLIER);
    this->Late.DensityGain = CalcDensityGain(CalcDecayCoeff(length,
                                                             decayTime));

    // Calculate the all-pass feed-back and feed-forward coefficient.
    this->Late.ApFeedCoeff = 0.5f * powf(diffusion, 2.0f);

    for(index = 0;index < 4;index++)
    {
        // Calculate the gain (coefficient) for each all-pass line.
        this->Late.ApCoeff[index] = CalcDecayCoeff(ALLPASS_LINE_LENGTH[index],
                                                    decayTime);

        // Calculate the length (in seconds) of each cyclical delay line.
        length = LATE_LINE_LENGTH[index] * (1.0f + (density *
                                                    LATE_LINE_MULTIPLIER));

        // Calculate the delay offset for each cyclical delay line.
        this->Late.Offset[index] = Truncate(length * frequency);

        // Calculate the gain (coefficient) for each cyclical line.
        this->Late.Coeff[index] = CalcDecayCoeff(length, decayTime);

        // Calculate the damping coefficient for each low-pass filter.
        this->Late.LpCoeff[index] =
            CalcDampingCoeff(hfRatio, length, decayTime,
                             this->Late.Coeff[index], cw);

        // Attenuate the cyclical line coefficients by the mixing coefficient
        // (x).
        this->Late.Coeff[index] *= xMix;
    }
}

// Update the echo gain, line offset, line coefficients, and mixing coefficients.
void ReverbEffect::UpdateEchoLine(float reverbGain, float lateGain, float echoTime, float decayTime, float diffusion, float echoDepth, float hfRatio, float cw, uint32_t frequency)
{
    // Update the offset and coefficient for the echo delay line.
    this->Echo.Offset = Truncate(echoTime * frequency);

    // Calculate the decay coefficient for the echo line.
    this->Echo.Coeff = CalcDecayCoeff(echoTime, decayTime);

    // Calculate the energy-based attenuation coefficient for the echo delay
    // line.
    this->Echo.DensityGain = CalcDensityGain(this->Echo.Coeff);

    // Calculate the echo all-pass feed coefficient.
    this->Echo.ApFeedCoeff = 0.5f * powf(diffusion, 2.0f);

    // Calculate the echo all-pass attenuation coefficient.
    this->Echo.ApCoeff = CalcDecayCoeff(ECHO_ALLPASS_LENGTH, decayTime);

    // Calculate the damping coefficient for each low-pass filter.
    this->Echo.LpCoeff = CalcDampingCoeff(hfRatio, echoTime, decayTime,
                                           this->Echo.Coeff, cw);

    /* Calculate the echo mixing coefficients.  The first is applied to the
     * echo itself.  The second is used to attenuate the late reverb when
     * echo depth is high and diffusion is low, so the echo is slightly
     * stronger than the decorrelated echos in the reverb tail.
     */
    this->Echo.MixCoeff[0] = reverbGain * lateGain * echoDepth;
    this->Echo.MixCoeff[1] = 1.0f - (echoDepth * 0.5f * (1.0f - diffusion));
}

// Update the early and late 3D panning gains.
void ReverbEffect::Update3DPanning(const float *ReflectionsPan, const float *LateReverbPan, float Gain)
{
    float earlyPan[3] = { ReflectionsPan[0], ReflectionsPan[1], -ReflectionsPan[2] };
    float latePan[3] = { LateReverbPan[0], LateReverbPan[1], -LateReverbPan[2] };
    float AmbientGains[OUTPUT_CHANNELS];
    float DirGains[OUTPUT_CHANNELS];
    float length, invlen;
    uint32_t i;

    ComputeAmbientGains(1.4142f, AmbientGains);

    length = earlyPan[0]*earlyPan[0] + earlyPan[1]*earlyPan[1] + earlyPan[2]*earlyPan[2];
    if(!(length > FLT_EPSILON))
    {
        for(i = 0;i < OUTPUT_CHANNELS;i++)
            this->Early.PanGain[i] = AmbientGains[i] * Gain;
    }
    else
    {
        invlen = 1.0f / sqrtf(length);
        earlyPan[0] *= invlen;
        earlyPan[1] *= invlen;
        earlyPan[2] *= invlen;

        length = minf(length, 1.0f);
        ComputeDirectionalGains(earlyPan, 1.4142f, DirGains);
        for(i = 0;i < OUTPUT_CHANNELS;i++)
            this->Early.PanGain[i] = lerp(AmbientGains[i], DirGains[i], length) * Gain;
    }

    length = latePan[0]*latePan[0] + latePan[1]*latePan[1] + latePan[2]*latePan[2];
    if(!(length > FLT_EPSILON))
    {
        for(i = 0;i < OUTPUT_CHANNELS;i++)
            this->Late.PanGain[i] = AmbientGains[i] * Gain;
    }
    else
    {
        invlen = 1.0f / sqrtf(length);
        latePan[0] *= invlen;
        latePan[1] *= invlen;
        latePan[2] *= invlen;

        length = minf(length, 1.0f);
        ComputeDirectionalGains(latePan, 1.4142f, DirGains);
        for(i = 0;i < OUTPUT_CHANNELS;i++)
            this->Late.PanGain[i] = lerp(AmbientGains[i], DirGains[i], length) * Gain;
    }
}


void ReverbEffect::Update(int frequency)
{
    float lfscale, hfscale, hfRatio;
    float cw, x, y;

    this->CutoffFrequency = (frequency / 2) - (frequency / 2) / (22050.f / 2050.f);
    if (this->settings.HFReference > this->CutoffFrequency) this->settings.HFReference = this->CutoffFrequency;
    if (this->settings.LFReference > this->CutoffFrequency) this->settings.LFReference = this->CutoffFrequency;

    // Calculate the master low-pass filter (from the master effect HF gain).
    hfscale = this->settings.HFReference / frequency;
    FilterState_setParams(&this->LpFilter, Filter_HighShelf, this->settings.GainHF, hfscale, 0.0f);

    lfscale = this->settings.LFReference / frequency;
    FilterState_setParams(&this->HpFilter, Filter_LowShelf, this->settings.GainLF, lfscale, 0.0f);

    // Update the modulator line.
    this->UpdateModulator(this->settings.ModulationTime, this->settings.ModulationDepth, frequency);

    // Update the initial effect delay.
    this->UpdateDelayLine(this->settings.ReflectionsDelay, this->settings.LateReverbDelay, frequency);

    // Update the early lines.
    this->UpdateEarlyLines(this->settings.Gain, this->settings.ReflectionsGain, this->settings.LateReverbDelay);

    // Update the decorrelator.
    this->UpdateDecorrelator(this->settings.Density, frequency);

    // Get the mixing matrix coefficients (x and y).
    CalcMatrixCoeffs(this->settings.Diffusion, &x, &y);
    // Then divide x into y to simplify the matrix calculation.
    this->Late.MixCoeff = y / x;

    // If the HF limit parameter is flagged, calculate an appropriate limit
    // based on the air absorption parameter.
    hfRatio = this->settings.DecayHFRatio;

    if(this->settings.DecayHFLimit && this->settings.AirAbsorptionGainHF < 1.0f)
            hfRatio = CalcLimitedHfRatio(hfRatio, this->settings.AirAbsorptionGainHF, this->settings.DecayTime);

    cw = cosf(F_2PI * hfscale);
    // Update the late lines.
    this->UpdateLateLines(this->settings.Gain, this->settings.LateReverbGain, x, this->settings.Density, this->settings.DecayTime, this->settings.Diffusion, hfRatio, cw, frequency);

    // Update the echo line.
    this->UpdateEchoLine(this->settings.Gain, this->settings.LateReverbGain, this->settings.EchoTime, this->settings.DecayTime, this->settings.Diffusion, this->settings.EchoDepth, hfRatio, cw, frequency);

    // Update early and late 3D panning.
    this->Update3DPanning(this->settings.ReflectionsPan, this->settings.LateReverbPan, ReverbBoost);
}


void ReverbEffect::LoadPreset(float Density, float Diffusion, float Gain, float GainHF, float GainLF, float DecayTime, float DecayHFRatio, float DecayLFRatio, float ReflectionsGain, float ReflectionsDelay, float ReflectionsPanX, float ReflectionsPanY, float ReflectionsPanZ, float LateReverbGain, float LateReverbDelay, float LateReverbPanX, float LateReverbPanY, float LateReverbPanZ, float EchoTime, float EchoDepth, float ModulationTime, float ModulationDepth, float AirAbsorptionGainHF, float HFReference, float LFReference, float RoomRolloffFactor, int DecayHFLimit)
{
    if (HFReference > this->CutoffFrequency) HFReference = this->CutoffFrequency;
    if (LFReference > this->CutoffFrequency) LFReference = this->CutoffFrequency;
    this->settings.Density = Density;
    this->settings.Diffusion = Diffusion;
    this->settings.Gain =  Gain;
    this->settings.GainHF = GainHF;
    this->settings.GainLF = GainLF;
    this->settings.DecayTime = DecayTime;
    this->settings.DecayHFRatio = DecayHFRatio;
    this->settings.DecayLFRatio = DecayLFRatio;
    this->settings.ReflectionsGain = ReflectionsGain;
    this->settings.ReflectionsDelay = ReflectionsDelay;
    this->settings.ReflectionsPan[0] = ReflectionsPanX;
    this->settings.ReflectionsPan[1] = ReflectionsPanY;
    this->settings.ReflectionsPan[2] = ReflectionsPanZ;
    this->settings.LateReverbGain = LateReverbGain;
    this->settings.LateReverbDelay = LateReverbDelay;
    this->settings.LateReverbPan[0] = LateReverbPanX;
    this->settings.LateReverbPan[1] = LateReverbPanY;
    this->settings.LateReverbPan[2] = LateReverbPanZ;
    this->settings.EchoTime = EchoTime;
    this->settings.EchoDepth = EchoDepth;
    this->settings.ModulationTime = ModulationTime;
    this->settings.ModulationDepth = ModulationDepth;
    this->settings.AirAbsorptionGainHF = AirAbsorptionGainHF;
    this->settings.HFReference = HFReference;
    this->settings.LFReference = LFReference;
    this->settings.RoomRolloffFactor = RoomRolloffFactor;
    this->settings.DecayHFLimit = DecayHFLimit;
}

void ReverbEffect::Create(uint32_t frequency)
{
    ambiCoeffs[0][0] = 0.7071f;
    ambiCoeffs[0][1] = 0.5f;
    ambiCoeffs[0][2] = 0.0f;
    ambiCoeffs[0][3] = 0.0f;

    ambiCoeffs[1][0] = 0.7071f;
    ambiCoeffs[1][1] = -0.5f;
    ambiCoeffs[2][2] = 0.0f;
    ambiCoeffs[3][3] = 0.0f;

    uint32_t index;

    this->CutoffFrequency = (frequency / 2) - (frequency / 2) / (22050.f / 2050.f);
    this->TotalSamples = 0;
    this->SampleBuffer = NULL;

    FilterState_clear(&this->LpFilter);
    FilterState_clear(&this->HpFilter);

    this->Mod.Delay.Mask = 0;
    this->Mod.Delay.Line = NULL;
    this->Mod.Index = 0;
    this->Mod.Range = 1;
    this->Mod.Depth = 0.0f;
    this->Mod.Coeff = 0.0f;
    this->Mod.Filter = 0.0f;

    this->Delay.Mask = 0;
    this->Delay.Line = NULL;
    this->DelayTap[0] = 0;
    this->DelayTap[1] = 0;

    this->Early.Gain = 0.0f;
    for(index = 0;index < 4;index++)
    {
        this->Early.Coeff[index] = 0.0f;
        this->Early.Delay[index].Mask = 0;
        this->Early.Delay[index].Line = NULL;
        this->Early.Offset[index] = 0;
    }

    this->Decorrelator.Mask = 0;
    this->Decorrelator.Line = NULL;
    this->DecoTap[0] = 0;
    this->DecoTap[1] = 0;
    this->DecoTap[2] = 0;

    this->Late.Gain = 0.0f;
    this->Late.DensityGain = 0.0f;
    this->Late.ApFeedCoeff = 0.0f;
    this->Late.MixCoeff = 0.0f;
    for(index = 0;index < 4;index++)
    {
        this->Late.ApCoeff[index] = 0.0f;
        this->Late.ApDelay[index].Mask = 0;
        this->Late.ApDelay[index].Line = NULL;
        this->Late.ApOffset[index] = 0;

        this->Late.Coeff[index] = 0.0f;
        this->Late.Delay[index].Mask = 0;
        this->Late.Delay[index].Line = NULL;
        this->Late.Offset[index] = 0;

        this->Late.LpCoeff[index] = 0.0f;
        this->Late.LpSample[index] = 0.0f;
    }

    for(index = 0;index < OUTPUT_CHANNELS;index++)
    {
        this->Early.PanGain[index] = 0.0f;
        this->Late.PanGain[index] = 0.0f;
    }

    this->Echo.DensityGain = 0.0f;
    this->Echo.Delay.Mask = 0;
    this->Echo.Delay.Line = NULL;
    this->Echo.ApDelay.Mask = 0;
    this->Echo.ApDelay.Line = NULL;
    this->Echo.Coeff = 0.0f;
    this->Echo.ApFeedCoeff = 0.0f;
    this->Echo.ApCoeff = 0.0f;
    this->Echo.Offset = 0;
    this->Echo.ApOffset = 0;
    this->Echo.LpCoeff = 0.0f;
    this->Echo.LpSample = 0.0f;
    this->Echo.MixCoeff[0] = 0.0f;
    this->Echo.MixCoeff[1] = 0.0f;

    this->Offset = 0;

    LoadPreset(EFX_REVERB_PRESET_GENERIC);

    // Allocate the delay lines.
    AllocLines(frequency);

    // Calculate the modulation filter coefficient.  Notice that the exponent
    // is calculated given the current sample rate.  This ensures that the
    // resulting filter response over time is consistent across all sample
    // rates.
    this->Mod.Coeff = powf(MODULATION_FILTER_COEFF,
                            MODULATION_FILTER_CONST / frequency);

    // The early reflection and late all-pass filter line lengths are static,
    // so their offsets only need to be calculated once.
    for(index = 0;index < 4;index++)
    {
        this->Early.Offset[index] = Truncate(EARLY_LINE_LENGTH[index] *
                                             frequency);
        this->Late.ApOffset[index] = Truncate(ALLPASS_LINE_LENGTH[index] *
                                              frequency);
    }

    // The echo all-pass filter line length is static, so its offset only
    // needs to be calculated once.
    this->Echo.ApOffset = Truncate(ECHO_ALLPASS_LENGTH * frequency);

}

void ReverbEffect::Destroy()
{
    delete[] this->SampleBuffer;
    this->SampleBuffer = NULL;
}
