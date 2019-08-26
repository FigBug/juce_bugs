/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
    : Thread("server")
{
    setSize (600, 400);
    startThread();
    
    if (readSock.connect("localhost", 6755))
    {
        char buf[1024];
        readSock.read (buf, 1024, false);
        printf ("Why do I never get here?\n");
    }
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setFont (Font (16.0f));
    g.setColour (Colours::white);
    g.drawText ("Hello World!", getLocalBounds(), Justification::centred, true);
}

void MainComponent::resized()
{
}

void MainComponent::run()
{
    StreamingSocket ss;
    
    
    if (ss.createListener(6755))
    {
        while (auto s = ss.waitForNextConnection())
            connections.add (new Connection (s));
    }
}
