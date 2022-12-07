#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
	box.setModel (this);
	box.updateContent();
	box.setWantsKeyboardFocus(true);
	addAndMakeVisible (box);
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
	box.setBounds (getLocalBounds().reduced (8));
}
