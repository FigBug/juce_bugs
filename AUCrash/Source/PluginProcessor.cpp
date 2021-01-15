/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AUCrashAudioProcessor::AUCrashAudioProcessor() : AudioProcessor ()
{
}

AUCrashAudioProcessor::~AUCrashAudioProcessor()
{
}

//==============================================================================
const juce::String AUCrashAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AUCrashAudioProcessor::acceptsMidi() const
{
    return false;
}

bool AUCrashAudioProcessor::producesMidi() const
{
    return false;
}

bool AUCrashAudioProcessor::isMidiEffect() const
{
    return true;
}

double AUCrashAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AUCrashAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int AUCrashAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AUCrashAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String AUCrashAudioProcessor::getProgramName (int index)
{
    return {};
}

void AUCrashAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void AUCrashAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void AUCrashAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AUCrashAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
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

void AUCrashAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
bool AUCrashAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* AUCrashAudioProcessor::createEditor()
{
    return new AUCrashAudioProcessorEditor (*this);
}

//==============================================================================
void AUCrashAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
	destData.setSize (2200);
	destData.fillWith (0);
}

void AUCrashAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	criticalSection.enter();
	
	juce::Thread::sleep (1000);
	
	uint8_t* p = (uint8_t*)data;
	for (int i = 0; i < sizeInBytes; i++)
		if (p[i] != 0)
			ohShit = true;

	criticalSection.exit();
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AUCrashAudioProcessor();
}
