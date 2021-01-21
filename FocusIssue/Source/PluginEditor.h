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
class FocusIssueAudioProcessorEditor  : public juce::AudioProcessorEditor,
										private juce::Timer,
										private juce::TextEditor::Listener
{
public:
	FocusIssueAudioProcessorEditor (FocusIssueAudioProcessor& p)
		: AudioProcessorEditor (&p), audioProcessor (p)
	{
		setSize (400, 300);
		startTimer (3000);

		addAndMakeVisible (text);
		text.addListener (this);
		setWantsKeyboardFocus (false);
	}

    ~FocusIssueAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics& g) override
	{
		g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

		g.setColour (juce::Colours::white);
		g.setFont (15.0f);
		g.drawFittedText (text.getText(), getLocalBounds(), juce::Justification::centred, 1);
	}

	void resized() override
	{
		text.setBounds (10, 10, 380, 25);
	}

	void timerCallback() override
	{
		text.setVisible (! text.isVisible());
	}

	void textEditorTextChanged (juce::TextEditor&) override
	{
		repaint ();
	}

private:
    FocusIssueAudioProcessor& audioProcessor;

	juce::TextEditor text;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FocusIssueAudioProcessorEditor)
};
