
#include "Distortion.hpp"


Distortion::Distortion(AudioProcessorValueTreeState& vt) : mParameters(vt)
{
    // type of waveshaping function
    mWaveShaper.functionToUse = [] (float x)
    {
        return std::tanh(x);
    };
    // initialise oversmapling type
    mOversampling.reset(new dsp::Oversampling<float>(2, 3, dsp::Oversampling<float>::filterHalfBandPolyphaseIIR, false));
    
}

void Distortion::prepare(juce::dsp::ProcessSpec spec)
{
    // prepare various components of the chain
    mSampleRate = static_cast<float>(spec.sampleRate);
    mMaxBlockSize = spec.maximumBlockSize;
    mNumChannels = spec.numChannels;
    
    mWaveShaper.prepare(spec);
    inputVolume.prepare(spec);
    outputVolume.prepare(spec);
    
    compressor.prepare(spec);
    compressor.setRatio(4.f);
    compressor.setRelease(50);
    compressor.setAttack(50);
    mOversampling->initProcessing(static_cast<size_t> (mMaxBlockSize));
    reset();
    smoothedIn.reset(mSampleRate, 0.2);
    smoothedOut.reset(mSampleRate, 0.2);
    
    inputVolume.setRampDurationSeconds(0.1);
    outputVolume.setRampDurationSeconds(0.1);
    
}

void Distortion::reset()
{
    mOversampling->reset();
}

// process audio blocks in a precise order
void Distortion::process (juce::dsp::ProcessContextReplacing<float> context)
{
    juce::ScopedNoDenormals noDenormals;
    inputVolume.process(context);
    compressor.process(context);
    
    dsp::AudioBlock<float> oversampledBlock  = mOversampling -> processSamplesUp(context.getInputBlock());
    
    auto waveshaperContext = dsp::ProcessContextReplacing<float>(oversampledBlock);
    mWaveShaper.process(waveshaperContext);
    waveshaperContext.getOutputBlock() *= 0.8f;
   
    mOversampling->processSamplesDown(context.getOutputBlock());
    
    outputVolume.process(context);
}

// update value tree state parameters
void Distortion::updateParameters()
{
    float offset = *mParameters.getRawParameterValue(IDs::inputVolume);
    float inVolume = *mParameters.getRawParameterValue(IDs::inputVolume);
    float outVolume = -offset + (offset/2) ;

    auto inputdB = Decibels::decibelsToGain(inVolume);
    auto outputdB = Decibels::decibelsToGain(outVolume);
    compressor.setThreshold(-outputdB/2);
    sideCoeffCopier = inputdB;
    smoothedIn.setTargetValue(inputdB);
    smoothedOut.setTargetValue(outputdB);
   
    if (inputVolume.getGainLinear() != inputdB)
    {
        inputVolume.setGainLinear(inputdB);
    }
    if (outputVolume.getGainLinear() != outputdB)
    {
        outputVolume.setGainLinear(outputdB);
    }
}
