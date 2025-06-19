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
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

	auto str = juce::String ("firstrun:status:-nan(ind)");
	DBG(str.fromLastOccurrenceOf (":", false, false).getDoubleValue());
}

void MainComponent::resized()
{
}
