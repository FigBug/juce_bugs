#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
	text.setText ("Hello World!");
	text.setIndents (6, 0);
	text.setJustification (juce::Justification::centredLeft);
	addAndMakeVisible (text);

    setSize (600, 400);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
	text.setBounds (10, 10, 150, 24);
}
