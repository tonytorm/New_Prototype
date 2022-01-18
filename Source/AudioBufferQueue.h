/*
  ==============================================================================

    AudioScope.h
    Created: 18 Jan 2022 10:55:40am
    Author:  Giulio Iacomino

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


class AudioBufferQueue
{
public:
    using SampleType = float;
    static constexpr size_t order = 9;
    static constexpr size_t bufferSize = 1U << order;
    static constexpr size_t numBuffers = 5;

    //==============================================================================
    void push (const SampleType* dataToPush, size_t numSamples);
    void pop (SampleType* outputBuffer);
   

private:
    juce::AbstractFifo abstractFifo { numBuffers };
    std::array<std::array<SampleType, bufferSize>, numBuffers> buffers;
};
