#pragma once

#include <JuceHeader.h>


class Preview : public juce::FilePreviewComponent
{
public:
    Preview ()
    {
        setSize (300, 300);
    }

    void selectedFileChanged (const juce::File& newSelectedFile) override
    {
    }

    void paint (juce::Graphics& g)
    {
        g.fillAll (juce::Colours::pink);
    }
};

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
    void mouseDown (const juce::MouseEvent& e) override;

private:
    //==============================================================================
    Preview preview;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
