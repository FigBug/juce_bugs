#pragma once

#include <JuceHeader.h>
#include "ThreadedTimer.h"

class MainComponent : public juce::Component
{
public:
    MainComponent();
    ~MainComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::OwnedArray<ThreadedTimer> timers;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
