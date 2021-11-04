#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================

private:
    //==============================================================================

    juce::MouseCursor getMouseCursor () override
    {
        juce::Image image (juce::Image::ARGB, 32, 32, true);

        {
            juce::Graphics g (image);
            g.fillAll (juce::Colours::pink);
        }

        return juce::MouseCursor (image, 0, 0, 2.0f);
    }

    void paint (juce::Graphics& g) override
    {
        auto c1 = getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId);
        auto c2 = c1.overlaidWith (juce::Colours::white.withAlpha (0.5f));

        g.fillCheckerBoard (getLocalBounds().toFloat(), 16, 16, c1, c2);
    }

    void resized () override
    {
    }
    //==============================================================================

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
