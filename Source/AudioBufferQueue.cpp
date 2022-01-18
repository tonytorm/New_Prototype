/*
  ==============================================================================

    AudioBufferQueue.cpp
    Created: 18 Jan 2022 11:01:41am
    Author:  Giulio Iacomino

  ==============================================================================
*/

#include "AudioBufferQueue.h"

void AudioBufferQueue::push (const SampleType* dataToPush, size_t numSamples)
   {
       jassert (numSamples <= bufferSize);

       int start1, size1, start2, size2;
       abstractFifo.prepareToWrite (1, start1, size1, start2, size2);

       jassert (size1 <= 1);
       jassert (size2 == 0);

       if (size1 > 0)
           juce::FloatVectorOperations::copy (buffers[(size_t) start1].data(), dataToPush, (int) juce::jmin (bufferSize, numSamples));

       abstractFifo.finishedWrite (size1);
   }

void AudioBufferQueue::pop (SampleType* outputBuffer)
   {
       int start1, size1, start2, size2;
       abstractFifo.prepareToRead (1, start1, size1, start2, size2);

       jassert (size1 <= 1);
       jassert (size2 == 0);

       if (size1 > 0)
           juce::FloatVectorOperations::copy (outputBuffer, buffers[(size_t) start1].data(), (int) bufferSize);

       abstractFifo.finishedRead (size1);
   }
