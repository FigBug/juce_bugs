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

    g.setFont (juce::Font (16.0f));
    g.setColour (juce::Colours::white);

    auto sp = juce::String (juce::CharPointer_UTF8 ("\xc2\xa0"));

    auto text = juce::String ("This should not wrap") + sp + "<here!";

    g.drawFittedText ( text, getLocalBounds (), juce::Justification::centred, 3, 1.0f );
}

void MainComponent::resized()
{
}
