#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
	addAndMakeVisible (source);
	addAndMakeVisible (dest);

    setSize (600, 400);
	startTimerHz (30);
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
	auto rc = getLocalBounds();
	source.setBounds (rc.removeFromLeft (rc.getWidth() / 2));
	dest.setBounds (rc);
}

void MainComponent::timerCallback() 
{
	repaint();
	dest.image = source.createComponentSnapshot (source.getLocalBounds());
}
