/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class UpdateDisplayAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    UpdateDisplayAudioProcessorEditor (UpdateDisplayAudioProcessor&);
    ~UpdateDisplayAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    UpdateDisplayAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (UpdateDisplayAudioProcessorEditor)
};
