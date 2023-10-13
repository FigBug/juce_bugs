#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
	for (auto b : buttons)
	{
		addAndMakeVisible(b);
		b->setRadioGroupId(1);
		b->setClickingTogglesState(true);
		b->setToggleable(true);
	}

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
	auto rc = getLocalBounds();

	for (auto b : buttons)
		b->setBounds(rc.removeFromTop ( 15));
}
