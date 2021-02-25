/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

class Popup : public juce::DocumentWindow
{
public:
    Popup() : juce::DocumentWindow ("Test", getBK(), juce::DocumentWindow::allButtons, true)
    {
        setBounds (100, 100, 200, 200);
        setVisible (true);
    }

    juce::Colour getBK ()
    {
        auto& r = juce::Random::getSystemRandom();
        return juce::Colour::fromRGB (r.nextInt(256), r.nextInt(256), r.nextInt(256));
    }
};

//==============================================================================
Bad_scaleAudioProcessorEditor::Bad_scaleAudioProcessorEditor (Bad_scaleAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (400, 300);
    startTimer (1000);
}

Bad_scaleAudioProcessorEditor::~Bad_scaleAudioProcessorEditor()
{
}

//==============================================================================
void Bad_scaleAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::pink);
}

void Bad_scaleAudioProcessorEditor::resized()
{
}

void Bad_scaleAudioProcessorEditor::mouseDown (const juce::MouseEvent& )
{
    juce::PopupMenu m;
    m.addItem ("Test", [this]
    {
        popups.add (new Popup());
    });
    m.showMenuAsync (juce::PopupMenu::Options());
}

void Bad_scaleAudioProcessorEditor::timerCallback()
{
    popups.add (new Popup());
}
