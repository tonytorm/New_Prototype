/*
  ==============================================================================

    AudioScopeCollector.cpp
    Created: 18 Jan 2022 11:01:54am
    Author:  Giulio Iacomino

  ==============================================================================
*/

#include "AudioScopeCollector.h"



AudioScopeCollector::AudioScopeCollector (AudioBufferQueue& queueToUse)
    : audioBufferQueue (queueToUse)
{}


void AudioScopeCollector::process (const SampleType* data, size_t numSamples)
{
    size_t index = 0;

    if (state == State::waitingForTrigger)
    {
        while (index++ < numSamples)
        {
            auto currentSample = *data++;

            if (currentSample >= triggerLevel && prevSample < triggerLevel)
            {
                numCollected = 0;
                state = State::collecting;
                break;
            }

            prevSample = currentSample;
        }
    }

    if (state == State::collecting)
    {
        while (index++ < numSamples)
        {
            buffer[numCollected++] = *data++;

            if (numCollected == buffer.size())
            {
                audioBufferQueue.push (buffer.data(), buffer.size());
                state = State::waitingForTrigger;
                prevSample = SampleType (100);
                break;
            }
        }
    }
}
