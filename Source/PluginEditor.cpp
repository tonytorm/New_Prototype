
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
New_PrototypeAudioProcessorEditor::New_PrototypeAudioProcessorEditor (New_PrototypeAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), mParameter(p.getState())
{
    scopeComponent = new AudioScope(audioProcessor.getAudioBufferQueue());
    setSize (400, 300);
    addAndMakeVisible(myInputVolumeSlider);
    myInputVolumeSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    myInputVolumeSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    
    myInputVolumeSlider.setLookAndFeel(&otherLookAndFeel);

    //meters
    addAndMakeVisible(meterL);
    addAndMakeVisible(meterR);
    meterL.toBack();
    meterR.toBack();
    auto area = getLocalBounds();
    addAndMakeVisible(*scopeComponent);
    scopeComponent->setTopLeftPosition (0, 240);
    scopeComponent->setSize (area.getWidth(), area.getHeight() - 240);
    scopeComponent->toBack();
    
    startTimerHz(60);
    initialiseGui();
    myInputVolumeSlider.addListener(this);
    
    // audio player

    filePlayerGui.setFilePlayer (audioProcessor.getFilePlayer());
    addAndMakeVisible (filePlayerGui);
    
    //title label
    addAndMakeVisible(title);
    title.setFont (juce::Font (16.0f, juce::Font::bold));
    title.setText ("SQUEEZE", juce::dontSendNotification);
    title.setColour(Label::textColourId, Colours::lightgoldenrodyellow);
    title.setJustificationType(juce::Justification::centred);
}

New_PrototypeAudioProcessorEditor::~New_PrototypeAudioProcessorEditor()
{
}

//==============================================================================
void New_PrototypeAudioProcessorEditor::paint (juce::Graphics& g)
{
    //g.fillAll(Colours::lightgoldenrodyellow);
}

void New_PrototypeAudioProcessorEditor::resized()
{
    myInputVolumeSlider.setBounds(getWidth()-20, getHeight(), 280, 500);
    myInputVolumeSlider.setCentrePosition(getWidth()-40, getHeight()/2-50);
    
    meterL.setBounds(0, 0, getWidth()/2, getHeight()-60);
    meterR.setBounds(getWidth()/2, 0, getWidth()/2, getHeight()-60);
    
    myInputVolumeSlider.isAlwaysOnTop();
    filePlayerGui.setBounds(0, 0, getWidth(), 30);
    
    title.setBounds(getWidth()/2, 20, 100, 100);
    title.setCentrePosition(getWidth()/2, 50);
    title.setAlwaysOnTop(true);
    scopeComponent->setAlwaysOnTop(true);
}

void New_PrototypeAudioProcessorEditor::initialiseGui() // initialise slider values/attachments
{
    myInputVolumeAttachment.reset(new SliderAttachment(mParameter, IDs::inputVolume, myInputVolumeSlider));
}

void New_PrototypeAudioProcessorEditor::timerCallback()
{
    // all time sensible operations (animations) are done in here
    meterL.setLevel(audioProcessor.getRMSValue(0));
    meterR.setLevel(audioProcessor.getRMSValue(1));
    meterL.repaint();
    meterR.repaint();
    // update various components color based on slider value
    meterL.changeColour((int)myInputVolumeSlider.getValue());
    meterR.changeColour((int)myInputVolumeSlider.getValue());
    scopeComponent->changeColour((int)myInputVolumeSlider.getValue());
    otherLookAndFeel.colourChanger((int)myInputVolumeSlider.getValue()*6);
    meterL.setFrameCount(frameCount);
    meterR.setFrameCount(frameCount);
    frameCount++;
    if (frameCount > 60)
        frameCount = 1;
}


void New_PrototypeAudioProcessorEditor::sliderValueChanged(Slider *slider)
{
    
}
void New_PrototypeAudioProcessorEditor::sliderDragStarted(Slider* slider)
{
    meterL.isSliderDragging(true); // pass boolean value
    meterR.isSliderDragging(true);
}
void New_PrototypeAudioProcessorEditor::sliderDragEnded(Slider* slider)
{
    meterL.isSliderDragging(false); // pass boolean value
    meterR.isSliderDragging(false);
}


