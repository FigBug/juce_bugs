/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ConstrainAudioProcessorEditor::ConstrainAudioProcessorEditor (ConstrainAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
   #if 1
    setResizable (true, true);

    constrainer.setSizeLimits (100, 100, 1000, 1000);
    setConstrainer (&constrainer);
   #else
    setResizeLimits (100, 100, 1000, 1000);
    getConstrainer()->setFixedAspectRatio (400.0 / 300.0);
   #endif

    setSize (400, 300);
}

ConstrainAudioProcessorEditor::~ConstrainAudioProcessorEditor()
{
}

//==============================================================================
void ConstrainAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void ConstrainAudioProcessorEditor::resized()
{
    AudioProcessorEditor::resized ();
}
