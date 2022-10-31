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
class AccessibleModals2AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    AccessibleModals2AudioProcessorEditor (AccessibleModals2AudioProcessor&);
    ~AccessibleModals2AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    AccessibleModals2AudioProcessor& audioProcessor;

	juce::TextButton open { "open" };
	juce::Component frame;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AccessibleModals2AudioProcessorEditor)
};
