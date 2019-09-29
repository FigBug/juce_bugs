/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Test_pluginAudioProcessorEditor::Test_pluginAudioProcessorEditor (Test_pluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    addAndMakeVisible (text1);
    addAndMakeVisible (text2);
    addAndMakeVisible (text3);
    addAndMakeVisible (text4);

    setSize (400, 300);
}

Test_pluginAudioProcessorEditor::~Test_pluginAudioProcessorEditor()
{
}

//==============================================================================
void Test_pluginAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
}

void Test_pluginAudioProcessorEditor::resized()
{
    text1.setBounds (8, 8, 150, 20);
    text2.setBounds (8, 30, 150, 20);
    text3.setBounds (8, 60, 150, 20);
    text4.setBounds (8, 90, 150, 20);
}
