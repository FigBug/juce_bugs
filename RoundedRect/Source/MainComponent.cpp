#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
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

    g.setFont (juce::FontOptions (16.0f));

	juce::ColourGradient grad (juce::Colours::red, 0, 0, juce::Colours::green, 0, getHeight(), false);
	g.setGradientFill (grad);

	g.drawRoundedRectangle (getLocalBounds().reduced (50).toFloat(), 2.0f, 5.0f);
}

void MainComponent::resized()
{
}
