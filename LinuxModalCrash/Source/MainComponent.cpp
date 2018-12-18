/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

class AnotherWindow : public TopLevelWindow
{
public:
    AnotherWindow() : TopLevelWindow ("Another Window", true)
    {
        setVisible (true);
        setAlwaysOnTop (true);
        toFront (true);
        centreWithSize (30, 30);
    }
    
    void paint (Graphics& g) override
    {
        g.fillAll (Colours::pink);
    }
};

//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 400);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::mouseUp (const MouseEvent&)
{
    PopupMenu m;
    m.addItem (1, "Crash");
    
    if (m.show() == 1)
    {
        //AlertWindow::showOkCancelBox (AlertWindow::NoIcon, "Please Wait", "Please Wait");
        aw = new AnotherWindow();
    }
}

void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setFont (Font (16.0f));
    g.setColour (Colours::white);
    g.drawText ("Hello World!", getLocalBounds(), Justification::centred, true);
}

void MainComponent::resized()
{
}
