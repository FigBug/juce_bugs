#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
    Reproduces the DropShadowEffect crash / broken-render caused by:

        // juce_DropShadowEffect.cpp, DropShadowEffect::applyEffect()
        s.radius = roundToInt ((float) s.radius * scaleFactor);   // can round to 0

    When a component that has a DropShadowEffect attached is rendered at a
    physical-pixel scale factor below 1.0 (e.g. a zoomed-out / down-scaled UI,
    which is common on Windows), a small shadow radius multiplied by that scale
    factor rounds down to 0.

    DropShadowEffect::applyEffect() then calls DropShadow::drawForImage() with
    radius == 0, which:
      * fires  jassert (radius > 0)  -> crash in a Debug build, and
      * produces a degenerate blur    -> broken shadow in a Release build.

    Here we give the shadowed component a small radius (2) and a downscaling
    transform (0.2). At paint time the effective scale factor is ~0.2, so:

        roundToInt (2 * 0.2) == roundToInt (0.4) == 0

    ...which triggers the bug the moment the component is first painted.
*/
class MainComponent   : public juce::Component
{
public:
    MainComponent()
    {
        setSize (400, 400);

        addAndMakeVisible (shadowed);

        // A small, perfectly valid shadow radius.
        shadowed.setEffect (2);

        // Simulate a down-scaled UI. The effective physical-pixel scale factor
        // seen inside DropShadowEffect::applyEffect() becomes ~0.2, so
        // roundToInt (radius * scale) == roundToInt (2 * 0.2) == 0.
        shadowed.setTransform (juce::AffineTransform::scale (0.2f));
    }

    void paint (juce::Graphics& g) override
    {
        g.fillAll (juce::Colours::darkgrey);

        g.setColour (juce::Colours::white);
        g.setFont (14.0f);
        g.drawFittedText ("A DropShadowEffect component is drawn (scaled down) in the corner.\n"
                          "In a Debug build this asserts in DropShadow::drawForImage (radius > 0).",
                          getLocalBounds().reduced (10), juce::Justification::topLeft, 4);
    }

    void resized() override
    {
        // Large logical size; the 0.2 transform shrinks it on screen.
        shadowed.setBounds (0, 0, 200, 200);
    }

private:
    //==============================================================================
    /*  A simple component that fills itself and casts a drop shadow via a
        DropShadowEffect (an ImageEffectFilter). */
    class ShadowedBox : public juce::Component
    {
    public:
        ShadowedBox()
        {
            setOpaque (false);
        }

        void setEffect (int radius)
        {
            effect.setShadowProperties (juce::DropShadow (juce::Colours::black.withAlpha (0.7f),
                                                          radius,
                                                          { 4, 4 }));
            setComponentEffect (&effect);
        }

        void paint (juce::Graphics& g) override
        {
            g.setColour (juce::Colours::orange);
            g.fillRoundedRectangle (getLocalBounds().toFloat().reduced (20.0f), 12.0f);
        }

    private:
        juce::DropShadowEffect effect;
    };

    ShadowedBox shadowed;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
