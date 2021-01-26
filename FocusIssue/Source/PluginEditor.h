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
										private juce::ListBoxModel
{
public:
	FocusIssueAudioProcessorEditor (FocusIssueAudioProcessor& p)
		: AudioProcessorEditor (&p), audioProcessor (p)
	{
		setSize (400, 300);
		startTimer (3000);

		addAndMakeVisible (box);
		box.setModel (this);
		box.updateContent();
		setWantsKeyboardFocus (false);
	}

    ~FocusIssueAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics& g) override
	{
		g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
	}

	int getNumRows() override
	{
		return 20;
	}

	void paintListBoxItem (int rowNumber, juce::Graphics& g, int width, int height, bool rowIsSelected) override
	{
		if (rowIsSelected)
		{
			g.setColour (box.isEnabled() ? juce::Colours::blue : juce::Colours::blue.withAlpha (0.5f));
			g.fillRect (juce::Rectangle<int> (0, 0, width, height));
		}

		g.setColour (box.isEnabled() ? juce::Colours::white : juce::Colours::white.withAlpha (0.5f));
		g.setFont (15.0f);
		g.drawFittedText (juce::String (rowNumber), juce::Rectangle<int> (0, 0, width, height), juce::Justification::centredLeft, 1);
	}

	void resized() override
	{
		box.setBounds (getLocalBounds().reduced (8));
	}

	void timerCallback() override
	{
		if (box.hasKeyboardFocus (true))
		{
			box.setEnabled (false);
			box.repaint ();
			stopTimer();
		}
	}

private:
    FocusIssueAudioProcessor& audioProcessor;

	juce::ListBox box;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FocusIssueAudioProcessorEditor)
};
