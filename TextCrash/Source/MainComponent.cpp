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

	juce::String text = juce::CharPointer_UTF8 ("LOOPS 4 \xd7\xa1X \xd7\xa1""4");

    g.setFont (juce::FontOptions (16.0f));
    g.setColour (juce::Colours::white);
    g.drawText (text, getLocalBounds(), juce::Justification::centred, true);
}

void MainComponent::resized()
{
}
