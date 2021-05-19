#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setLookAndFeel (&lf);
    addAndMakeVisible(box);
    setSize (1000, 800);

    if (auto m = box.getRootMenu())
    {
        for (int i = 0; i < 150; i++)
            m->addItem("zug zug " + juce::String(i + 1));
    }
    box.setSelectedItemIndex(0, juce::dontSendNotification);
}

MainComponent::~MainComponent()
{
    setLookAndFeel (nullptr);
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    box.setBounds(getLocalBounds().withSizeKeepingCentre(120, 30).translated(0, 100));
}

void MainComponent::mouseDown (const juce::MouseEvent&)
{
    juce::PopupMenu m, s;
    m.setLookAndFeel (&lf);

    s.addItem ("Test 1", []{});
    s.addItem ("Test 2", []{});
    s.addItem ("Test 3", []{});
    s.addItem ("Test 3", []{});

    m.addSubMenu ("Test", s);

    m.showMenuAsync (juce::PopupMenu::Options());
}
