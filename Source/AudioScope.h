
#pragma once

#include <JuceHeader.h>
#include "AudioBufferQueue.h"




class AudioScope  : public juce::Component,
                    public juce::Timer
{
public:
    using SampleType = float; // hardcoding the type of an ex-template class
    using Queue = AudioBufferQueue;
    
    
    AudioScope (Queue& queueToUse);
    void setFramesPerSecond (int framesPerSecond);
    void paint (juce::Graphics& g) override;
    void resized() override {}
    void timerCallback() override;
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
};
