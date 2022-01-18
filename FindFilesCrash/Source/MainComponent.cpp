#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 400);

    auto f = juce::File::getSpecialLocation(juce::File::tempDirectory);
    auto top = f.getChildFile("a");
    auto bot = top.getChildFile("b/c/d/e");
    bot.createDirectory();

    auto ln = bot.getChildFile("f");
    top.createSymbolicLink (ln, true);

    auto files = top.findChildFiles (juce::File::findFilesAndDirectories, true);
    for (auto f : files)
        DBG(f.getFullPathName());
    DBG(files.size());
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
