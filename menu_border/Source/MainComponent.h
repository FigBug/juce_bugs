#pragma once

#include <JuceHeader.h>

//==============================================================================
class WackyLookAndFeel : public juce::LookAndFeel_V4
{
public:

    int getPopupMenuBorderSize ()
    {
        return 10;
    }
};

class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void mouseDown (const juce::MouseEvent&) override;

private:
    //==============================================================================
    WackyLookAndFeel lf;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
