#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setLookAndFeel (&lf);
    setSize (600, 400);
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
}

void MainComponent::mouseDown (const juce::MouseEvent& e)
{
    if (e.x < getWidth() / 2)
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
    else
    {
        juce::PopupMenu m;
        m.setLookAndFeel (&lf);

        for (int i = 0; i < 100; i++)
        {
            if (i % 25 == 0)
                m.addColumnBreak();

            m.addItem ("Test" + juce::String (i + 1), []{});
        }

        m.showMenuAsync (juce::PopupMenu::Options());
    }
}
