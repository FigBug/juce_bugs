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

Typeface::Ptr getTypeface()
{
    static int idx = 0;
    idx++;
    
    switch (idx % 4)
    {
        case 0:
            return Typeface::createSystemTypefaceFor (BinaryData::OpenSansRegular_ttf, BinaryData::OpenSansRegular_ttfSize);
        case 1:
            return Typeface::createSystemTypefaceFor (BinaryData::RobotoMonoRegular_ttf, BinaryData::RobotoMonoRegular_ttfSize);
        case 2:
            return Typeface::createSystemTypefaceFor (BinaryData::TitilliumWebRegular_ttf, BinaryData::TitilliumWebRegular_ttfSize);
        case 3:
            return Typeface::createSystemTypefaceFor (BinaryData::RobotoLight_ttf, BinaryData::RobotoLight_ttfSize);
        default:
            return Typeface::createSystemTypefaceFor (BinaryData::TitilliumWebRegular_ttf, BinaryData::TitilliumWebRegular_ttfSize);
    }
}

//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 400);
    startTimerHz (200);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    
    int h = getHeight() / 20;
    int w = getWidth()  / 10;
    
    auto area = getLocalBounds();
    
    static Array<Typeface::Ptr> typefaces;
    
    for (int j = 0; j < 10; j++)
    {
        auto rc = area.removeFromLeft (w);

        for (int i = 0; i < 20; i += 4)
        {
            auto typeface = getTypeface();
            typefaces.add (typeface);
            if (typefaces.size() > 100)
                typefaces.remove (0);
            
            Font f (typeface);
            
            static int idx = 0;
            idx++;

            g.setFont (f);
            g.setColour (goldenRatioColor (idx));
            g.drawFittedText ("Hello World!\nHullo World!\nGoodbye Wolrd!\nPeace out!",
                              rc.removeFromTop (h * 4), Justification::centred, 4.0);
        }
    }
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
