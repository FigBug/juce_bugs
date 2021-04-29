/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class AU_Wont_BuildAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    AU_Wont_BuildAudioProcessorEditor (AU_Wont_BuildAudioProcessor&);
    ~AU_Wont_BuildAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AU_Wont_BuildAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AU_Wont_BuildAudioProcessorEditor)
};
