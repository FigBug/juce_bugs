#include "MainComponent.h"

MainComponent::MainComponent()
{
    for (int i = 0; i < 100; ++i)
        timers.add (new ThreadedTimer (i));

    setSize (600, 400);
}

MainComponent::~MainComponent()
{
    timers.clear();
}

void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (24.0f));
    g.drawText ("ThreadedTimerTest - " + juce::String (timers.size()) + " threaded timers",
                getLocalBounds(), juce::Justification::centred);
}

void MainComponent::resized()
{
}
