#pragma once

#include <JuceHeader.h>

//==============================================================================
class Bar : public juce::Component
          , private juce::Timer
{
public:
    Bar (bool fa) : fillAll (fa)
    {
        setOpaque (true);
        startTimerHz (10);
    }

    void timerCallback() override
    {
        repaint();
    }

    void paint (juce::Graphics& g) override
    {
        DBG("paint bar");
        if (fillAll)
        {
            g.fillAll (juce::Colours::darkgrey);
        }
        else
        {
            g.setColour (juce::Colours::darkgrey);
            g.fillRect (getLocalBounds().expanded (100));
        }
    }

    juce::ComponentDragger myDragger;

    void mouseDown (const juce::MouseEvent& e) override
    {
        myDragger.startDraggingComponent (this, e);
    }

    void mouseDrag (const juce::MouseEvent& e) override
    {
        myDragger.dragComponent (this, e, nullptr);
    }

    bool fillAll = false;
};

//==============================================================================
class Wrapper : public juce::Component
{
public:
    Wrapper ()
    {
        setName("wrapper");
        setTransform (juce::AffineTransform ().scaled (0.70f));

        addAndMakeVisible (bar1);
    }

    void paint ( juce::Graphics& g) override
    {
        DBG("paint wrapper");
        auto R = uint8_t (random.nextInt (256));
        auto G = uint8_t (random.nextInt (256));
        auto B = uint8_t (random.nextInt (256));

        g.fillAll (juce::Colour (R, G, B, 1.0f));
    }

    void resized () override
    {
        bar1.setBounds (209, 194, 100, 24);
    }

    juce::Random random;
    Bar bar1 { true };
};

//==============================================================================
class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    Wrapper wrapper;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
