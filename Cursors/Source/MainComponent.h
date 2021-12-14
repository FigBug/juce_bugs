#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component, public juce::Timer
{
public:
    //==============================================================================
    MainComponent()
    {
        setSize(600, 400);
        startTimerHz ( 1 );
    }

    ~MainComponent() override;

    //==============================================================================

private:
    //==============================================================================

    juce::MouseCursor getMouseCursor () override
    {
        int scale = 2;
        juce::Image image (juce::Image::ARGB, cx * scale, cx * scale, true);

        {
            juce::Graphics g (image);
            g.fillAll (juce::Colours::pink);
        }

        juce::ScaledImage si (image, scale);
        DBG(juce::String::formatted ("Getting mouse cursor of size: %d", cx));

        return juce::MouseCursor (si, {0, 0});
    }

    void paint (juce::Graphics& g) override
    {
        auto c1 = getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId);
        auto c2 = c1.overlaidWith (juce::Colours::white.withAlpha (0.5f));

        g.fillCheckerBoard (getLocalBounds().toFloat(), cx, cx, c1, c2);
    }

    void resized () override
    {
    }

    void timerCallback() override
    {
        cx *= 2;
        if (cx > 128)
            cx = 1;

        juce::Desktop::getInstance().getMainMouseSource().forceMouseCursorUpdate();
        repaint ();
    }
    //==============================================================================

    int cx = 1;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
