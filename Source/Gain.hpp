
#pragma once

#include <JuceHeader.h>

/** a class containing a juce DSP gain object*/
class Gain
{
public:
    /** prepares the gain through the assignment of process specifics*/
    void prepare (juce::dsp::ProcessSpec);
    /** resets the gain*/
    void reset();
    /** processes sound (at block level) */
    void process (juce::dsp::ProcessContextReplacing<float> context);
    /** processes sound (at sample level) */
    void processSample(float s);
    /** sets decibels*/
    void setDecibels(float decibels);
    /** Returns current gain in a linear value*/
    float getGainLinear() const ;
    /** Applies a new gain as a linear value*/
    void setGainLinear(float newGain);
    /** Sets the duration of the ramp used for smoothing changes*/
    void setRampDurationSeconds(double newDurationSeconds);
private:
    dsp::Gain<float> gainVolume;
};
