#ifndef REVERBEFFECT_H
#define REVERBEFFECT_H

#include <stdint.h>
#include "efx-presets.h"

typedef int BOOL;

#define OUTPUT_CHANNELS 2
#define TRUE 1
#define FALSE 0
#define REVERB_BUFFERSIZE (2048u)
#define F_2PI (6.28318530717958647692f)
#define FLT_EPSILON 1.19209290E-07F

#define  MAX_AMBI_COEFFS 4

#define SPEEDOFSOUNDMETRESPERSEC 343.3f

#define GAIN_SILENCE_THRESHOLD  0.00001f

/* This is a user config option for modifying the overall output of the reverb effect. */
#define ReverbBoost 1.0f

/* Effect parameter ranges. */
#define EAXREVERB_MIN_DENSITY                 (0.0f)
#define EAXREVERB_MAX_DENSITY                 (1.0f)

#define EAXREVERB_MIN_DIFFUSION               (0.0f)
#define EAXREVERB_MAX_DIFFUSION               (1.0f)

#define EAXREVERB_MIN_GAIN                    (0.0f)
#define EAXREVERB_MAX_GAIN                    (1.0f)

#define EAXREVERB_MIN_GAINHF                  (0.0f)
#define EAXREVERB_MAX_GAINHF                  (1.0f)

#define EAXREVERB_MIN_GAINLF                  (0.0f)
#define EAXREVERB_MAX_GAINLF                  (1.0f)

#define EAXREVERB_MIN_DECAY_TIME              (0.1f)
#define EAXREVERB_MAX_DECAY_TIME              (20.0f)

#define EAXREVERB_MIN_DECAY_HFRATIO           (0.1f)
#define EAXREVERB_MAX_DECAY_HFRATIO           (2.0f)

#define EAXREVERB_MIN_DECAY_LFRATIO           (0.1f)
#define EAXREVERB_MAX_DECAY_LFRATIO           (2.0f)

#define EAXREVERB_MIN_REFLECTIONS_GAIN        (0.0f)
#define EAXREVERB_MAX_REFLECTIONS_GAIN        (3.16f)

#define EAXREVERB_MIN_REFLECTIONS_DELAY       (0.0f)
#define EAXREVERB_MAX_REFLECTIONS_DELAY       (0.3f)

#define EAXREVERB_MIN_LATE_REVERB_GAIN        (0.0f)
#define EAXREVERB_MAX_LATE_REVERB_GAIN        (10.0f)

#define EAXREVERB_MIN_LATE_REVERB_DELAY       (0.0f)
#define EAXREVERB_MAX_LATE_REVERB_DELAY       (0.1f)

#define EAXREVERB_MIN_ECHO_TIME               (0.075f)
#define EAXREVERB_MAX_ECHO_TIME               (0.25f)

#define EAXREVERB_MIN_ECHO_DEPTH              (0.0f)
#define EAXREVERB_MAX_ECHO_DEPTH              (1.0f)

#define EAXREVERB_MIN_MODULATION_TIME         (0.04f)
#define EAXREVERB_MAX_MODULATION_TIME         (4.0f)

#define EAXREVERB_MIN_MODULATION_DEPTH        (0.0f)
#define EAXREVERB_MAX_MODULATION_DEPTH        (1.0f)

#define EAXREVERB_MIN_AIR_ABSORPTION_GAINHF   (0.892f)
#define EAXREVERB_MAX_AIR_ABSORPTION_GAINHF   (1.0f)

#define EAXREVERB_MIN_HFREFERENCE             (1000.0f)
#define EAXREVERB_MAX_HFREFERENCE             (20000.0f)

#define EAXREVERB_MIN_LFREFERENCE             (20.0f)
#define EAXREVERB_MAX_LFREFERENCE             (1000.0f)

#define EAXREVERB_MIN_ROOM_ROLLOFF_FACTOR     (0.0f)
#define EAXREVERB_MAX_ROOM_ROLLOFF_FACTOR     (10.0f)

#define EAXREVERB_MIN_DECAY_HFLIMIT           FALSE
#define EAXREVERB_MAX_DECAY_HFLIMIT           TRUE

typedef enum FilterType {
    /** EFX-style low-pass filter, specifying a gain and reference frequency. */
    Filter_HighShelf,
    /** EFX-style high-pass filter, specifying a gain and reference frequency. */
    Filter_LowShelf,
} FilterType;

typedef struct
{
    // The delay lines use sample lengths that are powers of 2 to allow the
    // use of bit-masking instead of a modulus for wrapping.
    uint32_t   Mask;
    float *Line;
} DelayLine;

typedef struct {
    float x[2]; /* History of two last input samples  */
    float y[2]; /* History of two last output samples */
    float a[3]; /* Transfer function coefficients "a" */
    float b[3]; /* Transfer function coefficients "b" */
} FilterState;

typedef struct {
    // Shared Reverb Properties
    float Density;
    float Diffusion;
    float Gain;
    float GainHF;
    float DecayTime;
    float DecayHFRatio;
    float ReflectionsGain;
    float ReflectionsDelay;
    float LateReverbGain;
    float LateReverbDelay;
    float AirAbsorptionGainHF;
    float RoomRolloffFactor;
    BOOL DecayHFLimit;

    // Additional EAX Reverb Properties
    float GainLF;
    float DecayLFRatio;
    float ReflectionsPan[3];
    float LateReverbPan[3];
    float EchoTime;
    float EchoDepth;
    float ModulationTime;
    float ModulationDepth;
    float HFReference;
    float LFReference;

} ReverbSettings;

typedef struct {
    // Modulator delay line.
    DelayLine Delay;

    // The vibrato time is tracked with an index over a modulus-wrapped
    // range (in samples).
    uint32_t    Index;
    uint32_t    Range;

    // The depth of frequency change (also in samples) and its filter.
    float   Depth;
    float   Coeff;
    float   Filter;
} Modulator;

typedef struct {
    // Output gain for early reflections.
    float   Gain;

    // Early reflections are done with 4 delay lines.
    float   Coeff[4];
    DelayLine Delay[4];
    uint32_t    Offset[4];

    // The gain for each output channel based on 3D panning (only for the
    // EAX path).
    float   PanGain[OUTPUT_CHANNELS];
} EarlyDelay;

typedef struct {
    // Output gain for late reverb.
    float   Gain;

    // Attenuation to compensate for the modal density and decay rate of
    // the late lines.
    float   DensityGain;

    // The feed-back and feed-forward all-pass coefficient.
    float   ApFeedCoeff;

    // Mixing matrix coefficient.
    float   MixCoeff;

    // Late reverb has 4 parallel all-pass filters.
    float   ApCoeff[4];
    DelayLine ApDelay[4];
    uint32_t    ApOffset[4];

    // In addition to 4 cyclical delay lines.
    float   Coeff[4];
    DelayLine Delay[4];
    uint32_t    Offset[4];

    // The cyclical delay lines are 1-pole low-pass filtered.
    float   LpCoeff[4];
    float   LpSample[4];

    // The gain for each output channel based on 3D panning (only for the
    // EAX path).
    float   PanGain[OUTPUT_CHANNELS];
} LateDelay;

typedef struct {
    // Attenuation to compensate for the modal density and decay rate of
    // the echo line.
    float   DensityGain;

    // Echo delay and all-pass lines.
    DelayLine Delay;
    DelayLine ApDelay;

    float   Coeff;
    float   ApFeedCoeff;
    float   ApCoeff;

    uint32_t    Offset;
    uint32_t    ApOffset;

    // The echo line is 1-pole low-pass filtered.
    float   LpCoeff;
    float   LpSample;

    // Echo mixing coefficients.
    float   MixCoeff[2];
} ReverbEcho;

class ReverbEffect
{
    public:
        void Create(uint32_t frequency);
        void Destroy();

        void Process(uint32_t SamplesToDo, const float *SamplesIn, float *SamplesOut);
        void Update(int frequency);

        void LoadPreset(float Density, float Diffusion, float Gain, float GainHF, float GainLF, float DecayTime, float DecayHFRatio, float DecayLFRatio, float ReflectionsGain, float ReflectionsDelay, float ReflectionsPanX, float ReflectionsPanY, float ReflectionsPanZ, float LateReverbGain, float LateReverbDelay, float LateReverbPanX, float LateReverbPanY, float LateReverbPanZ, float EchoTime, float EchoDepth, float ModulationTime, float ModulationDepth, float AirAbsorptionGainHF, float HFReference, float LFReference, float RoomRolloffFactor, int DecayHFLimit);


    private:
    ReverbSettings settings;

    // All delay lines are allocated as a single buffer to reduce memory
    // fragmentation and management code.
    float  *SampleBuffer;
    uint32_t    TotalSamples;
    float CutoffFrequency;

    // Master effect filters
    FilterState LpFilter;
    FilterState HpFilter; // EAX only

    Modulator Mod;

    // Initial effect delay.
    DelayLine Delay;
    // The tap points for the initial delay.  First tap goes to early
    // reflections, the last to late reverb.
    uint32_t    DelayTap[2];

    EarlyDelay Early;

    // Decorrelator delay line.
    DelayLine Decorrelator;
    // There are actually 4 decorrelator taps, but the first occurs at the
    // initial sample.
    uint32_t    DecoTap[3];

    LateDelay Late;

    ReverbEcho Echo;

    // The current read offset for all delay lines.
    uint32_t Offset;

        /* Temporary storage used when processing, before deinterlacing. */
    float ReverbSamples[REVERB_BUFFERSIZE][4];
    float EarlySamples[REVERB_BUFFERSIZE][4];

    float ambiCoeffs[OUTPUT_CHANNELS][MAX_AMBI_COEFFS];

    void ComputeAmbientGains(float ingain, float gains[OUTPUT_CHANNELS]);
    void ComputeDirectionalGains(const float dir[3], float ingain, float gains[OUTPUT_CHANNELS]);

    void AllocLines(uint32_t frequency);

    inline float EAXModulation(float in);

    inline float EarlyDelayLineOut(uint32_t index);
    inline void EarlyReflection(float in, float *out);

    inline float LateAllPassInOut(uint32_t index, float in);
    inline float LateDelayLineOut(uint32_t index);

    inline float LateLowPassInOut(uint32_t index, float in);
    inline void LateReverb(const float *in, float *out);

    inline void EAXEcho(float in, float *late);
    inline void EAXVerbPass(float in, float *early, float *late);

    void UpdateDelayLine(float earlyDelay, float lateDelay, uint32_t frequency);
    void UpdateModulator(float modTime, float modDepth, uint32_t frequency);
    void UpdateEarlyLines(float reverbGain, float earlyGain, float lateDelay);
    void UpdateDecorrelator(float density, uint32_t frequency);
    void UpdateLateLines(float reverbGain, float lateGain, float xMix, float density, float decayTime, float diffusion, float hfRatio, float cw, uint32_t frequency);
    void UpdateEchoLine(float reverbGain, float lateGain, float echoTime, float decayTime, float diffusion, float echoDepth, float hfRatio, float cw, uint32_t frequency);

    void Update3DPanning(const float *ReflectionsPan, const float *LateReverbPan, float Gain);
};

#endif // REVERBEFFECT_H
