
#pragma once

#include <JuceHeader.h>
#include "Distortion.hpp"
#include "Identifiers.hpp"
#include "Gain.hpp"
#include "FilePlayer.hpp"
#include "AudioScopeCollector.h"
#include "AudioBufferQueue.h"


//==============================================================================
/**
*/
class New_PrototypeAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    New_PrototypeAudioProcessor();
    ~New_PrototypeAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override; 
    void setStateInformation (const void* data, int sizeInBytes) override;
    juce::AudioProcessorValueTreeState& getState(); // returns state of ValueTreeState
    float getRMSValue(const int channel) const; // grabs rms value from channel
    FilePlayer* getFilePlayer() {return &filePlayer;}; // links file player guy
    AudioBufferQueue& getAudioBufferQueue() noexcept { return audioBufferQueue; };
    
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (New_PrototypeAudioProcessor)
    Distortion myDistorter;
    Gain sideGain;
    juce::AudioProcessorValueTreeState mParameters;
    float sideCoeff;
    LinearSmoothedValue<float> leftRMS, rightRMS;
    FilePlayer filePlayer;
    AudioBufferQueue audioBufferQueue;
    AudioScopeCollector* audioScopeCollector { nullptr };
   
    
};


