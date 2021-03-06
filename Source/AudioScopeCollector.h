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

/** a class that handles the collection of data from the buffer stream*/
class AudioScopeCollector
{
public:
    using SampleType = float;   // hardcoding the type of an ex-template class
    /** constructor, takes the queue to write into as an argument
     * @param queueToUse the AudioBufferQueue to read from */
    AudioScopeCollector (AudioBufferQueue& queueToUse);
    /** process the output buffer into useful to data for the buffer queuee
     * @param data the actual buffer data
     * @param numSamples the number of samples per buffer*/
    void process (const SampleType* data, size_t numSamples);
   

private:
    AudioBufferQueue& audioBufferQueue;
    std::array<SampleType, AudioBufferQueue::bufferSize> buffer;
    size_t numCollected;
    SampleType prevSample = SampleType (100);
    static constexpr auto triggerLevel = SampleType (0.05);
    enum class State { waitingForTrigger, collecting } state { State::waitingForTrigger };
};
