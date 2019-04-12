/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

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
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    RectangleList<float> events;

    for (int i = 100; i < 200; i++)
        events.addWithoutMerging ({1302850.25f + (i + 1) * 60000.0f , 19.0000000f, 1.00000000f, 53.0000000f });

    g.setColour (Colours::red);
    g.fillRectList (events);
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
