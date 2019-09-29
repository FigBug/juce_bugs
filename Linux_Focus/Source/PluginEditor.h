/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Test_pluginAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    Test_pluginAudioProcessorEditor (Test_pluginAudioProcessor&);
    ~Test_pluginAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    TextEditor text1, text2, text3, text4;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Test_pluginAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Test_pluginAudioProcessorEditor)
};
