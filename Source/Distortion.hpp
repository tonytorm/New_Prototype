
#pragma once

#include <JuceHeader.h>
#include "Gain.hpp"
#include "Identifiers.hpp"

/** A class that chains up various effects to obtain distortion*/
class Distortion  
{
public:
    /** Constructor, takes a VTS as argument*/
    Distortion(AudioProcessorValueTreeState& vt);
    /** Prepares all the underlying effects */
    void prepare (juce::dsp::ProcessSpec);
    /** resets all the underlying effects */
    void reset();
    /** processes audio signal
     * @param context  information that is passed into an algorithm's process method.*/
    void process (juce::dsp::ProcessContextReplacing<float> context);
    /** updates slider parameters*/
    void updateParameters();
    
    float sideCoeffCopier;
private:
    AudioProcessorValueTreeState& mParameters;
    juce::dsp::WaveShaper<float> mWaveShaper; // waveshaper
    juce::dsp::Compressor<float> compressor; // compressor
    Gain inputVolume, outputVolume;
    float mSampleRate = 44100.f;
    juce::uint32 mMaxBlockSize = 512;
    juce::uint32 mNumChannels = 2;
    std::unique_ptr<dsp::Oversampling<float>> mOversampling; // oversampling
    SmoothedValue<float, ValueSmoothingTypes::Linear> smoothedIn, smoothedOut;
      
};
