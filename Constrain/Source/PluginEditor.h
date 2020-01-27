/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
class WackyBoundsConstrainer : public ComponentBoundsConstrainer
{
public:
    void checkBounds (Rectangle<int>& bounds,
                              const Rectangle<int>& previousBounds,
                              const Rectangle<int>& limits,
                              bool isStretchingTop,
                              bool isStretchingLeft,
                              bool isStretchingBottom,
                              bool isStretchingRight) override
    {
        bounds.setWidth (jmax (100, bounds.getWidth() / 100 * 100));
        bounds.setHeight (jmax (100, bounds.getHeight() / 100 * 100));
    }
};

//==============================================================================
/**
*/
class ConstrainAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    ConstrainAudioProcessorEditor (ConstrainAudioProcessor&);
    ~ConstrainAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    ConstrainAudioProcessor& processor;

    WackyBoundsConstrainer constrainer;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConstrainAudioProcessorEditor)
};
