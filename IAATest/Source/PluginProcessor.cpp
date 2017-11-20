/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
IaatestAudioProcessor::IaatestAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

IaatestAudioProcessor::~IaatestAudioProcessor()
{
}

//==============================================================================
const String IaatestAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool IaatestAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool IaatestAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool IaatestAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double IaatestAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int IaatestAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int IaatestAudioProcessor::getCurrentProgram()
{
    return 0;
}

void IaatestAudioProcessor::setCurrentProgram (int index)
{
}

const String IaatestAudioProcessor::getProgramName (int index)
{
    return {};
}

void IaatestAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void IaatestAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void IaatestAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool IaatestAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void IaatestAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    buffer.clear();

    float* channelData0 = buffer.getWritePointer (0);
    float* channelData1 = totalNumOutputChannels > 1 ? buffer.getWritePointer (1) : nullptr;
    
    double currentStep = 200 / getSampleRate();
    
    const int num =  buffer.getNumSamples();
    for (int i = 0; i < num; i++)
    {
        phase += currentStep;
        if (phase >= 1.0)
            phase -= 1.0;
        
        float val = 0;
        
        val = std::sin (phase * float_Pi * 2);
        
        channelData0[i] = val;
        if (channelData1 != nullptr) channelData1[i] = val;
    }
}

//==============================================================================
bool IaatestAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* IaatestAudioProcessor::createEditor()
{
    return new IaatestAudioProcessorEditor (*this);
}

//==============================================================================
void IaatestAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void IaatestAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new IaatestAudioProcessor();
}
