/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class Connection : public Thread
{
public:
    Connection (StreamingSocket* s)
        : Thread("Connection"), socket (s)
    {
        startThread();
    }
    
    void run() override
    {
        while (socket->isConnected())
        {
            char buf[1024];
            socket->read (buf, 1024, false);
        }
    }
    
    std::unique_ptr<StreamingSocket> socket;
};

class MainComponent : public Component,
                      private Thread
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void run() override;

private:
    //==============================================================================
    StreamingSocket readSock;
    OwnedArray<Connection> connections;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
