#pragma once

#include <JuceHeader.h>

class Frame : public juce::Component
{
public:
    void paint ( juce::Graphics& g ) override
    {
        auto rc = getLocalBounds();
        auto textRight = rc.getCentreX ();

        auto font = juce::FontOptions ( 14.0f );
        g.setFont ( font );

        auto txt = "Pika Pika Pika Pika Pika Pika";
        auto textWidth = juce::GlyphArrangement::getStringWidth ( font, txt );

        auto c = juce::Colours::white;

        if ( rc.getX () + textWidth >= textRight )
        {
            const auto    gradRect = rc.withTrimmedLeft ( rc.getWidth () - 30.0f );
            auto    grad = juce::ColourGradient::horizontal ( c, c.withAlpha ( 0.0f ), gradRect );

            g.setGradientFill ( grad );
        }
        else
        {
            g.setColour ( c );
        }
        g.drawText ( txt, rc, juce::Justification::centredLeft, false );
    }
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
    Frame frame;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
