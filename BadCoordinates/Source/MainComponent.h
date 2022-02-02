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
    void paint (juce::Graphics&) override;
    void resized() override;

    void mouseMove (const juce::MouseEvent& e) override { DBG("move: " + pos.toString()); pos = e.position; repaint(); }
    void mouseExit (const juce::MouseEvent& e) override { DBG("exit: " + pos.toString()); pos = e.position; repaint(); }
    void mouseDown (const juce::MouseEvent&) override
    {
        juce::PopupMenu m;
        m.addItem ("Nothing", []{});
        m.showMenuAsync ({});
    }

private:
    //==============================================================================
    juce::Point<float> pos;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
