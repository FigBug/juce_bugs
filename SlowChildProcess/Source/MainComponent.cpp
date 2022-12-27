#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 400);

    auto start = juce::Time::getCurrentTime();

    juce::StringArray arguments;
    arguments.add ("/opt/homebrew/bin/ffmpeg");

    juce::ChildProcess p;
    p.start (arguments);
    p.waitForProcessToFinish (500000);


    auto end = juce::Time::getCurrentTime();

    DBG(juce::String((end - start).inSeconds(), 2) + " seconds");
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont (juce::Font (16.0f));
    g.setColour (juce::Colours::white);
    g.drawText ("Hello World!", getLocalBounds(), juce::Justification::centred, true);
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
