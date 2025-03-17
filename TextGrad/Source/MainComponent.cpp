#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    scaler.addAndMakeVisible (box);
	box.setBounds (20, 20, 650, 400);

	addAndMakeVisible (scaler);
	scaler.setSize (650, 400);

    setSize (650, 400);
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
    auto scale = int (float (getWidth()) / 650 * 10) / 10.0f;
	scaler.setTransform (juce::AffineTransform().scaled (scale));
}
