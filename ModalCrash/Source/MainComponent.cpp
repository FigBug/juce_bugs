#include "MainComponent.h"

struct Blocker : public juce::Component
{
    void inputAttemptWhenModal() override {}
};

//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 400);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont (juce::Font (16.0f));
    g.setColour (juce::Colours::white);
    g.drawText ("Hello World!", getLocalBounds(), juce::Justification::centred, true);
}

void MainComponent::resized()
{
}

void MainComponent::mouseDown(const juce::MouseEvent& e)
{
    juce::PopupMenu m;
    m.addItem("Test", []() {});
    m.showMenuAsync({});

    Blocker blocker;
    blocker.enterModalState(false);

    juce::DocumentWindow w ("Test", juce::Colours::white, 0);
    w.setVisible(true);
    w.toFront(false);
}