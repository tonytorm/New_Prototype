/*
  ==============================================================================

    AudioScope.cpp
    Created: 18 Jan 2022 10:55:40am
    Author:  Giulio Iacomino

  ==============================================================================
*/

#include "AudioScope.h"

AudioScope::AudioScope (Queue& queueToUse)
    : audioBufferQueue (queueToUse)
{
    sampleData.fill (SampleType (0));
    setFramesPerSecond (30);
}

void AudioScope::setFramesPerSecond(int framesPerSecond)
{
      jassert (framesPerSecond > 0 && framesPerSecond < 1000);
      startTimerHz (framesPerSecond);
}

void AudioScope::paint (juce::Graphics& g) 
   {
       g.fillAll (juce::Colours::black);
       g.setColour (juce::Colours::white);

       auto area = getLocalBounds();
       auto h = (SampleType) area.getHeight();
       auto w = (SampleType) area.getWidth();

       // Oscilloscope
       auto scopeRect = juce::Rectangle<SampleType> { SampleType (0), SampleType (0), w, h / 2 };
       plot (sampleData.data(), sampleData.size(), g, scopeRect, SampleType (1), h / 4);

       // Spectrum
       auto spectrumRect = juce::Rectangle<SampleType> { SampleType (0), h / 2, w, h / 2 };
       plot (spectrumData.data(), spectrumData.size() / 4, g, spectrumRect);
   }


void AudioScope::timerCallback()
   {
       audioBufferQueue.pop (sampleData.data());
       juce::FloatVectorOperations::copy (spectrumData.data(), sampleData.data(), (int) sampleData.size());

       auto fftSize = (size_t) fft.getSize();

       jassert (spectrumData.size() == 2 * fftSize);
       windowFun.multiplyWithWindowingTable (spectrumData.data(), fftSize);
       fft.performFrequencyOnlyForwardTransform (spectrumData.data());

       static constexpr auto mindB = SampleType (-160);
       static constexpr auto maxdB = SampleType (0);

       for (auto& s : spectrumData)
           s = juce::jmap (juce::jlimit (mindB, maxdB, juce::Decibels::gainToDecibels (s) - juce::Decibels::gainToDecibels (SampleType (fftSize))), mindB, maxdB, SampleType (0), SampleType (1));

       repaint();
   }

 void AudioScope::plot (const SampleType* data,
                  size_t numSamples,
                  juce::Graphics& g,
                  juce::Rectangle<SampleType> rect,
                  SampleType scaler,
                  SampleType offset)
{
    auto w = rect.getWidth();
    auto h = rect.getHeight();
    auto right = rect.getRight();

    auto center = rect.getBottom() - offset;
    auto gain = h * scaler;

    for (size_t i = 1; i < numSamples; ++i)
        g.drawLine ({ juce::jmap (SampleType (i - 1), SampleType (0), SampleType (numSamples - 1), SampleType (right - w), SampleType (right)),
                      center - gain * data[i - 1],
                      juce::jmap (SampleType (i), SampleType (0), SampleType (numSamples - 1), SampleType (right - w), SampleType (right)),
                      center - gain * data[i] });
}
