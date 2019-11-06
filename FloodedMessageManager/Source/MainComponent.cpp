/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
	for (int i = 0; i < 2500; i++)
	{
		auto s = new Slider();
		s->setTextBoxStyle (Slider::TextBoxLeft, false, 50, 20);
		s->setRange ({-1, 1}, 0.5);
		s->setValue (0.25);
		sliders.add (s);
	}

    setSize (600, 400);

	addActionListener (this);

	sendActionMessage ("Start up complete!");
}

MainComponent::~MainComponent()
{
	removeActionListener (this);
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setFont (Font (16.0f));
    g.setColour (Colours::white);
    g.drawText (text, getLocalBounds(), Justification::centred, true);
}

void MainComponent::resized()
{
}

void MainComponent::actionListenerCallback (const String& message) 
{
	text = message;
}