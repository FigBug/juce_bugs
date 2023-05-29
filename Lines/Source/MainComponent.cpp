#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (800, 100);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);

    juce::Path p;
    p.addLineSegment (juce::Line<float>(-86368088.0f, 100.0000000f, 169523792.0f, 1.00000000f), 1.0f);

    g.strokePath (p, juce::PathStrokeType(1));
}

void MainComponent::resized()
{
}
