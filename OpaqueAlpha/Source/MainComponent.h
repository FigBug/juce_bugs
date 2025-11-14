#pragma once

#include <JuceHeader.h>


class MainComponent   : public juce::Component
{
public:
    MainComponent()
    {
        setSize (200, 300);

        addAndMakeVisible (&outer);
        outer.setColour (juce::Colours::white);
        outer.setOpaque (false); // we're going to toggle the alpha of this

        outer.addAndMakeVisible (&inner);
        inner.setColour (juce::Colours::yellow);
        inner.setOpaque (true); // this will always be full alpha

        addAndMakeVisible (&button);
        button.setButtonText ("press");

        mouseListener.listenTo (button);
        mouseListener.setMouseDown (
            [this]()
            {
                float newAlpha = outer.getAlpha() == 1.0f ? 0.5f : 1.0f;
                outer.setAlpha (newAlpha);
            });
    }

    void paint (juce::Graphics& g) override
    {
        g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    }

    void resized() override
    {
        outer.setBounds ({50, 50, 100, 100});
        inner.setBounds ({25, 0, 50, 100});
        button.setBounds ({50, 200, 100, 50});
    }

private:
    //==============================================================================
    class Block : public juce::Component
    {
    public:
        void setColour (juce::Colour c) { colour = c; }

    private:
        void paint (juce::Graphics& g) override { g.fillAll (colour); }
        juce::Colour colour;
    };

    class MouseListener : public juce::MouseListener
    {
    public:
        MouseListener() {}
        void listenTo (juce::Component& c) { c.addMouseListener (this, false); }
        void setMouseDown (std::function<void()> onDown) { onMouseDown = onDown; }
        void mouseDown (const juce::MouseEvent&) override { onMouseDown(); }

    private:
        std::function<void()> onMouseDown;
    };

    Block outer;
    Block inner;
    juce::TextButton button;
    MouseListener mouseListener;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
