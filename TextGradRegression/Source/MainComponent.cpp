#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible(frame);
    setSize (600, 400);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    frame.setBounds (getLocalBounds().reduced(getWidth() / 4, getHeight() / 4));
}
