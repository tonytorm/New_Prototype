
#pragma once

#include <JuceHeader.h>
#include "AudioBufferQueue.h"



/** a class that represents a graphic oscilloscope*/
class AudioScope  : public juce::Component,
                    public juce::Timer
{
public:
    using SampleType = float; // hardcoding the type of an ex-template class
    using Queue = AudioBufferQueue;
    
    /** constructor, takes the buffer queue which it reads from as argument*/
    AudioScope (Queue& queueToUse);
    /** sets the framerate at which thiis component is being painted*/
    void setFramesPerSecond (int framesPerSecond);
    void paint (juce::Graphics& g) override;
    void resized() override {}
    void timerCallback() override;
    /**Simply takes and return an integer value, used to change RGBA values in colors*/
    int changeColour(int value);
    /**plots (paints) a line within a defined rectangle, the points of the line are defined by the buffer queue data*/
    static void plot (const SampleType* data,
                      size_t numSamples,
                      juce::Graphics& g,
                      juce::Rectangle<SampleType> rect,
                      SampleType scaler = SampleType (1),
                      SampleType offset = SampleType (0));
    

private:
    Queue& audioBufferQueue;
    std::array<SampleType, Queue::bufferSize> sampleData;
    juce::dsp::FFT fft { Queue::order };
    using WindowFun = juce::dsp::WindowingFunction<SampleType>;
    WindowFun windowFun { (size_t) fft.getSize(), WindowFun::hann };
    std::array<SampleType, 2 * Queue::bufferSize> spectrumData;
    int colourChanger = 0;
};
