#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
	addAndMakeVisible(viewport);
    setSize (600, 400);

	viewport.setViewedComponent(new Frame(), true);
	viewport.setScrollOnDragMode(juce::Viewport::ScrollOnDragMode::all);
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
	viewport.setBounds(getLocalBounds());
}
