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
class Popup;
class Bad_scaleAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Timer
{
public:
    Bad_scaleAudioProcessorEditor (Bad_scaleAudioProcessor&);
    ~Bad_scaleAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void mouseDown (const juce::MouseEvent& e);
    void timerCallback();

private:
    Bad_scaleAudioProcessor& audioProcessor;
    juce::OwnedArray<Popup> popups;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Bad_scaleAudioProcessorEditor)
};
