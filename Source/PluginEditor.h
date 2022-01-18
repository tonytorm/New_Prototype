
#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Identifiers.hpp"
#include "OtherLookAndFeel.hpp"
#include "MyMeter.hpp"
#include "FilePlayerGui.hpp"
#include "AudioScope.h"
//==============================================================================
/**
*/
class New_PrototypeAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                                  juce::Timer,
                                                  juce::Slider::Listener
                                                  
{
public:
    New_PrototypeAudioProcessorEditor (New_PrototypeAudioProcessor&);
    ~New_PrototypeAudioProcessorEditor() override;

    //==============================================================================
    void timerCallback() override;
    void paint (juce::Graphics&) override;
    void resized() override;
    void initialiseGui(); // initialises values of slider
    void sliderValueChanged(Slider* slider) override;
    void sliderDragStarted(Slider*) override;
    void sliderDragEnded(Slider*) override;
    
  
    
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    New_PrototypeAudioProcessor& audioProcessor;
    AudioProcessorValueTreeState& mParameter;

    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    OtherLookAndFeel otherLookAndFeel;
    Slider myInputVolumeSlider;
    Slider myOutputVolumeSlider;
    
    std::unique_ptr<SliderAttachment> myInputVolumeAttachment;
    std::unique_ptr<SliderAttachment> myOutputVolumeAttachment;
    
    MyMeter meterL, meterR;
    
    FilePlayerGui filePlayerGui;
    Label title {"O.G.uicer"};
    float frameCount; 
    AudioScope* scopeComponent;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (New_PrototypeAudioProcessorEditor)
};
