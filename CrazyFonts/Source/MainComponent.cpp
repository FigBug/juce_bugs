/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

Colour goldenRatioColor (int idx)
{
    double h = std::fmod (idx * 0.618033988749895, 1);
    return Colour (float (h), 0.8f, 0.95f, 1.0f);
}

//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 400);
    startTimerHz (30);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    static int idx = 0;
    idx++;

    for (int i = 0; i < 10; i++)
    {
        auto typeface = Typeface::createSystemTypefaceFor (BinaryData::OpenSansRegular_ttf,  BinaryData::OpenSansRegular_ttfSize);
        Font f (typeface);

        g.setFont (f);
        g.setColour (goldenRatioColor (idx));
        g.drawText ("Hello World!", getLocalBounds(), Justification::centred, true);
    }
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
