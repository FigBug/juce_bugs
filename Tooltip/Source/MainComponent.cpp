#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 400);
	addAndMakeVisible (child);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.setFont (juce::FontOptions (16.0f));
}

void MainComponent::resized()
{
	child.setBounds (getWidth() * 2 - 200, getHeight() * 2 - 200, 200, 200);
}
