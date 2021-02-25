#include "MainComponent.h"

#include <sys/select.h>

//==============================================================================
MainComponent::MainComponent()
{
    setSize (800, 600);

    juce::OwnedArray<juce::StreamingSocket> sockets;

    while (sockets.size() < int (FD_SETSIZE * 1.5))
    {
        auto s = new juce::StreamingSocket();
        if (s->connect ("figbug.com", 80))
        {
            printf ("creating socket %d\n", s->getRawSocketHandle());
            sockets.add (s);
        }
        else
        {
            delete s;
            break;
        }
    }

    for (int i = sockets.size(); --i >= 0;)
    {
        auto s = sockets[i];
        printf ("testing socket %d\n", s->getRawSocketHandle());

        s->waitUntilReady (true, 1);
        s->waitUntilReady (false, 1);
    }
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
