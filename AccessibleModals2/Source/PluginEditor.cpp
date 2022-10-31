/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

class Modal : public juce::Component
{
public:
	Modal()
	{
		addAndMakeVisible (close);
		close.setBounds ( 10, 10, 75, 20 );
		close.onClick = [ this ] { delete this; };
	}

	void paint (juce::Graphics& g) override
	{
		g.fillAll (juce::Colours::white);
	}

	juce::TextButton close { "close" };
};


//==============================================================================
AccessibleModals2AudioProcessorEditor::AccessibleModals2AudioProcessorEditor (AccessibleModals2AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
	setFocusContainerType ( juce::Component::FocusContainerType::keyboardFocusContainer );
	frame.setFocusContainerType ( juce::Component::FocusContainerType::keyboardFocusContainer );
	addAndMakeVisible ( frame );
	frame.addAndMakeVisible ( open );

	open.onClick = [ this ]
	{
		auto m = new Modal();
		m->setBounds (200, 100, 200, 200);
		addAndMakeVisible (m);
		m->enterModalState();
	};


	setSize (600, 400);
}

AccessibleModals2AudioProcessorEditor::~AccessibleModals2AudioProcessorEditor()
{
}

//==============================================================================
void AccessibleModals2AudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void AccessibleModals2AudioProcessorEditor::resized()
{
	frame.setBounds( getLocalBounds());
	open.setBounds ( 10, 10, 75, 20 );
}
