#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Create the nested opaque components (4 levels deep)
    nestedComponents.reset (new NestedComponent (1, juce::Colours::white));
    addAndMakeVisible (nestedComponents.get());

    setSize (800, 600);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::darkgrey);

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (16.0f));
    g.drawText ("Opaque Test: 4 nested opaque components + non-opaque tab bar", 10, 10, 780, 30, juce::Justification::centred);
}

void MainComponent::resized()
{
    auto bounds = getLocalBounds().reduced (20);

    if (nestedComponents)
        nestedComponents->setBounds (bounds);
}
