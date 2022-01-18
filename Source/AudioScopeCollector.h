/*
  ==============================================================================

    AudioScope.h
    Created: 18 Jan 2022 10:55:40am
    Author:  Giulio Iacomino

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "AudioBufferQueue.h"


class AudioScopeCollector
{
public:
    using SampleType = float;   // hardcoding the type of an ex-template class
    
    AudioScopeCollector (AudioBufferQueue& queueToUse);
    void process (const SampleType* data, size_t numSamples);
   

private:
    AudioBufferQueue& audioBufferQueue;
    std::array<SampleType, AudioBufferQueue::bufferSize> buffer;
    size_t numCollected;
    SampleType prevSample = SampleType (100);
    static constexpr auto triggerLevel = SampleType (0.05);
    enum class State { waitingForTrigger, collecting } state { State::waitingForTrigger };
};
