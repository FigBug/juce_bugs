#pragma once

#include <JuceHeader.h>

//==============================================================================
class Bar : public juce::Component, public juce::Timer
{
public:
    Bar ()
    {
        setOpaque (true);
        startTimerHz(60);
    }

    void timerCallback() override
    {
        repaint();
    }

    void paint (juce::Graphics& g) override
    {
        g.setColour (juce::Colours::red);
        g.fillRect (getLocalBounds().expanded (1));
        g.fillAll (juce::Colours::darkgrey);

        //g.setColour (juce::Colours::darkgrey);
        //g.fillRect (getLocalBounds().expanded (1));

        g.setColour(juce::Colours::white);
        g.drawText(getBounds().toString(), getLocalBounds(), juce::Justification::centred, 1);
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
};

class Box1 : public juce::Component
{
public:
    void paint (juce::Graphics& g) override
    {
        g.fillAll (juce::Colours::white);
    }
};

class Box2 : public juce::Component
{
public:
    Box2()
    {
        addAndMakeVisible(bar);
        bar.setBounds (209, 194, 100, 100);
    }

    void paint (juce::Graphics& g) override
    {
        g.fillAll (juce::Colours::black);
    }

    Bar bar;
};

//==============================================================================
class Wrapper : public juce::Component, public juce::Timer
{
public:
    Wrapper ()
    {
        setTransform (juce::AffineTransform ().scaled (0.70f));

        addAndMakeVisible (box2);
        addChildComponent (box1);

        //startTimerHz (1);
    }

    void timerCallback() override
    {
        box1.setVisible (! box1.isVisible());
        box2.setVisible (! box2.isVisible());
    }

    void paint ( juce::Graphics& g) override
    {
        g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    }

    void resized () override
    {
        box1.setBounds (getLocalBounds() * 2);
        box2.setBounds (getLocalBounds() * 2);
    }

    Box1 box1;
    Box2 box2;
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
