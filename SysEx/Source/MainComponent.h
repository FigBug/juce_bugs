#pragma once

#include <JuceHeader.h>

class MainComponent : public juce::Component,
                      public juce::Timer,
                      public juce::MidiInputCallback
{
public:
    MainComponent (bool isReceiver);
    ~MainComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void timerCallback() override;
    void handleIncomingMidiMessage (juce::MidiInput* source, const juce::MidiMessage& message) override;

private:
    bool receiverMode;

    juce::Label titleLabel;
    juce::TextEditor log;

    std::unique_ptr<juce::MidiOutput> midiOutput;
    std::unique_ptr<juce::MidiInput> midiInput;

    juce::Random random;
    int noteCounter = 0;

    void appendToLog (const juce::String& text);
    juce::String sysexToHexString (const juce::MidiMessage& msg);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
