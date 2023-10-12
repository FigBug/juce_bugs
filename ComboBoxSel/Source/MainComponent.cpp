#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 400);

    addAndMakeVisible (box);
    box.setBounds (10, 10, 200, 20);

    for (int i = 0; i < 112; i++)
    {
        box.addItem ("id: " + juce::String (i + 1), i + 1);
        if (i == 0)
            box.addSeparator();
    }
    box.setSelectedItemIndex (111);

    box.addListener(this);
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
    g.drawText ("Hello World!", getLocalBounds(), juce::Justification::centred, true);
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
