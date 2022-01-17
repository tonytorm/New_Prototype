
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
New_PrototypeAudioProcessor::New_PrototypeAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
            // initialise and assign parameters in the tree state
            mParameters(*this, nullptr, Identifier("Distortion"),
            {
            std::make_unique<AudioParameterFloat>(IDs::inputVolume,
                                                    "INPUTVOLUME",
                                                    NormalisableRange<float>(0.f, 20.f),
                                                    0.f,
                                                    " dB",
                                                    AudioProcessorParameter::genericParameter,
                                                    [](float value, int) {return static_cast<String>(round(value * 100.f) / 100.f); },
                                                    nullptr
                                                    ),
                
            std::make_unique<AudioParameterFloat>(IDs::outputVolume,
                                                    "OUTPUTVOLUME",
                                                    NormalisableRange<float>(-40.f, 40.f),
                                                    0.f,
                                                    " dB",
                                                    AudioProcessorParameter::genericParameter,
                                                    [](float value, int) {return static_cast<String>(round(value * 100.f) / 100.f); },
                                                    nullptr
                                                    )
                }),
                    myDistorter(mParameters) // initialise distortion effect
        
#endif
{
    
}

New_PrototypeAudioProcessor::~New_PrototypeAudioProcessor()
{
    
}

//==============================================================================
const juce::String New_PrototypeAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool New_PrototypeAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool New_PrototypeAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool New_PrototypeAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double New_PrototypeAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int New_PrototypeAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int New_PrototypeAudioProcessor::getCurrentProgram()
{
    return 0;
}

void New_PrototypeAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String New_PrototypeAudioProcessor::getProgramName (int index)
{
    return {};
}

void New_PrototypeAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void New_PrototypeAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
                                    // prepare specifics for disortion chain and sides gain
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
    myDistorter.prepare(spec);
    sideGain.prepare(spec);
    leftRMS.reset(sampleRate, 0.5);                  // reset rms values
    rightRMS.reset(sampleRate, 0.5);
    leftRMS.setCurrentAndTargetValue(-100.f);        // initialize rms values to minimum
    rightRMS.setCurrentAndTargetValue(-100.f);       // initialize rms values to minimum
    filePlayer.prepareToPlay(samplesPerBlock, sampleRate);
    
}

void New_PrototypeAudioProcessor::releaseResources()
{
    
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool New_PrototypeAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
   
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void New_PrototypeAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    sideCoeff = myDistorter.sideCoeffCopier/10;
 
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());
    }
    float* leftChannel = buffer.getWritePointer(0);
    float* rightChannel = buffer.getWritePointer(1);
    
    filePlayer.getNextAudioBlock(AudioSourceChannelInfo(buffer));
    myDistorter.updateParameters();
    
    juce::dsp::AudioBlock<float> block(buffer);

    myDistorter.process(juce::dsp::ProcessContextReplacing<float>(block));
    sideGain.setGainLinear(sideCoeff);
    
    for (int i = 0; i < buffer.getNumSamples(); ++i)
    {
        float mid = (leftChannel[i] + rightChannel[i]);
        float sides = (rightChannel[i] - leftChannel[i]);
        sideGain.processSample(sides);
            
        leftChannel[i] = mid - sides;
        rightChannel[i] = mid + sides;
    }
    
    leftRMS.skip(buffer.getNumSamples());
    rightRMS.skip(buffer.getNumSamples());
    
    
    //================================================ smooth left channel values
    {
        const auto value = Decibels::gainToDecibels(buffer.getRMSLevel(0, 0, buffer.getNumSamples()));
        if (value < leftRMS.getCurrentValue())
            leftRMS.setTargetValue(value);
        else
            leftRMS.setCurrentAndTargetValue(value);
    }
    
    //================================================ smooth right channel values
    {
        const auto value = Decibels::gainToDecibels(buffer.getRMSLevel(1, 0, buffer.getNumSamples()));
        if (value < rightRMS.getCurrentValue())
            rightRMS.setTargetValue(value);
        else
            rightRMS.setCurrentAndTargetValue(value);
    }
}

//==============================================================================
bool New_PrototypeAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* New_PrototypeAudioProcessor::createEditor()
{
    return new New_PrototypeAudioProcessorEditor (*this);
}

//==============================================================================
void New_PrototypeAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = mParameters.copyState();
    std::unique_ptr<XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void New_PrototypeAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
   std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
    {
        if (xmlState->hasTagName(mParameters.state.getType()))
            mParameters.replaceState(ValueTree::fromXml(*xmlState));

    }
}

juce::AudioProcessorValueTreeState& New_PrototypeAudioProcessor::getState()
{
    return mParameters;
}

float New_PrototypeAudioProcessor::getRMSValue(const int channel) const
{
    jassert(channel == 0 || channel == 1);
    if (channel == 0)
        return leftRMS.getCurrentValue();
    else if (channel == 1)
        return rightRMS.getCurrentValue();
    return 0.f;
}



//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new New_PrototypeAudioProcessor();
}


