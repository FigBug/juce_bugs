#include "MainComponent.h"

MainComponent::MainComponent (bool isReceiver)
    : receiverMode (isReceiver)
{
    if (receiverMode)
        titleLabel.setText ("Receiver - Incoming SysEx:", juce::dontSendNotification);
    else
        titleLabel.setText ("Sender - Outgoing SysEx:", juce::dontSendNotification);

    addAndMakeVisible (titleLabel);

    log.setMultiLine (true);
    log.setReadOnly (true);
    log.setScrollbarsShown (true);
    addAndMakeVisible (log);

    if (receiverMode)
    {
        // Receiver mode: open the "Loopback" MIDI input
        auto midiInputs = juce::MidiInput::getAvailableDevices();
        for (const auto& device : midiInputs)
        {
            if (device.name == "Loopback")
            {
                midiInput = juce::MidiInput::openDevice (device.identifier, this);
                if (midiInput != nullptr)
                {
                    midiInput->start();
                    appendToLog ("Opened MIDI input: Loopback");
                }
                break;
            }
        }

        if (midiInput == nullptr)
            appendToLog ("Failed to open Loopback input - is sender running?");
    }
    else
    {
        // Sender mode: create the "Loopback" MIDI output device
        midiOutput = juce::MidiOutput::createNewDevice ("Loopback");

        if (midiOutput != nullptr)
            appendToLog ("Created MIDI output: Loopback");
        else
            appendToLog ("Failed to create Loopback MIDI output");

        // Start timer - first 5 callbacks send notes, then SysEx
        startTimer (1000);
    }

    setSize (400, 500);
}

MainComponent::~MainComponent()
{
    stopTimer();

    if (midiInput != nullptr)
        midiInput->stop();
}

void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    auto bounds = getLocalBounds().reduced (10);

    titleLabel.setBounds (bounds.removeFromTop (25));
    log.setBounds (bounds);
}

void MainComponent::timerCallback()
{
    if (midiOutput == nullptr)
        return;

    // First 10 callbacks: send 5 note on/off pairs
    if (noteCounter < 10)
    {
        int noteNum = 60 + (noteCounter / 2);

        if (noteCounter % 2 == 0)
        {
            auto noteOn = juce::MidiMessage::noteOn (1, noteNum, 0.8f);
            midiOutput->sendMessageNow (noteOn);
            appendToLog ("Note On: " + juce::String (noteNum));
        }
        else
        {
            auto noteOff = juce::MidiMessage::noteOff (1, noteNum);
            midiOutput->sendMessageNow (noteOff);
            appendToLog ("Note Off: " + juce::String (noteNum));
        }

        noteCounter++;

        if (noteCounter == 10)
            appendToLog ("Now sending SysEx...");

        return;
    }

    // Generate a random SysEx message
    // SysEx format: F0 <manufacturer> <data...> F7
    juce::Array<juce::uint8> sysexData;
    sysexData.add (0xF0);                               // SysEx start
    sysexData.add ((juce::uint8) random.nextInt (128)); // Manufacturer ID

    // Add 3-10 random data bytes (values 0-127 for valid SysEx data)
    int numDataBytes = random.nextInt ({3, 11});
    for (int i = 0; i < numDataBytes; ++i)
        sysexData.add ((juce::uint8) random.nextInt (128));

    sysexData.add (0xF7);                               // SysEx end

    auto sysexMessage = juce::MidiMessage::createSysExMessage (sysexData.data(), sysexData.size());

    // Send the message
    midiOutput->sendMessageNow (sysexMessage);

    // Log what we sent
    appendToLog (sysexToHexString (sysexMessage));
}

void MainComponent::handleIncomingMidiMessage (juce::MidiInput*, const juce::MidiMessage& message)
{
    // Use MessageManager to update UI from MIDI thread
    juce::MessageManager::callAsync ([this, message]()
    {
        if (message.isSysEx())
        {
            appendToLog (sysexToHexString (message));
        }
        else if (message.isNoteOn())
        {
            appendToLog ("Note On: " + juce::String (message.getNoteNumber()));
        }
        else if (message.isNoteOff())
        {
            appendToLog ("Note Off: " + juce::String (message.getNoteNumber()));
        }
    });
}

void MainComponent::appendToLog (const juce::String& text)
{
    log.moveCaretToEnd();
    log.insertTextAtCaret (text + "\n");
}

juce::String MainComponent::sysexToHexString (const juce::MidiMessage& msg)
{
    juce::String result;
    auto* data = msg.getRawData();
    auto size = msg.getRawDataSize();

    for (int i = 0; i < size; ++i)
    {
        if (i > 0)
            result += " ";
        result += juce::String::toHexString (data[i]).toUpperCase().paddedLeft ('0', 2);
    }

    return result;
}
