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
class MainContentComponent   : public Component, public AsyncUpdater
{
public:
    //==============================================================================
    MainContentComponent();
    ~MainContentComponent();

    void paint (Graphics&) override;
    void resized() override;
    
    void handleAsyncUpdate() override
    {
        Thread::sleep (250);
        repaint();
    }

    void mouseDown (const MouseEvent&) override 
    { 
        beginDragAutoRepeat (10); 
    }

    void mouseDrag (const MouseEvent& e) override 
    { 
        triggerAsyncUpdate(); 
        pt = e.getPosition(); 
    }

private:
    Point<int> pt;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};
