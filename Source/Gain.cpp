
#include "Gain.hpp"




void Gain::prepare (juce::dsp::ProcessSpec spec)
{
    gainVolume.prepare(spec);
    
}

void Gain::setDecibels(float decibels)
{
    gainVolume.setGainDecibels(decibels);
    
}
void Gain::reset()
{
    
}

void Gain::process (juce::dsp::ProcessContextReplacing<float> context)
{
    juce::ScopedNoDenormals noDenormals;
    gainVolume.process(context);
}

float Gain::getGainLinear() const
{
    return gainVolume.getGainLinear();
}

void Gain::setGainLinear(float newGain)
{
    gainVolume.setGainLinear(newGain);
}

void Gain::setRampDurationSeconds(double newDurationSeconds)
{
    gainVolume.setRampDurationSeconds(newDurationSeconds);
}


void Gain::processSample(float s)
{
    gainVolume.processSample(s);
}
