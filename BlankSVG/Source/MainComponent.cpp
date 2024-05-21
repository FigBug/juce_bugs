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

    if (auto svg = juce::XmlDocument::parse (BinaryData::Synthwave_2_svg))
        if (auto drawable = juce::Drawable::createFromSVG (*svg))
            drawable->drawWithin (g, juce::Rectangle<float>(float (getWidth()), float (getHeight())), 0, 1.0f);
}

void MainComponent::resized()
{
}
