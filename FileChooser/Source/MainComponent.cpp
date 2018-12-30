/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

class Preview : public FilePreviewComponent
{
public:
    Preview()
    {
        addAndMakeVisible (test);
        test.onClick = [&]
        {
            AlertWindow::showMessageBox (AlertWindow::InfoIcon, "Test", "Hi");
        };
        setSize (116, 100);
    }

    void selectedFileChanged (const File&) override
    {
    }

    void resized() override
    {
        test.setBounds (8, 8, 100, 20);
    }

    TextButton test {"Test"};
};

//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible (openFile);
    openFile.onClick = [&]
    {
        Preview preview;
        FileChooser chooser ("Open");
        chooser.browseForMultipleFilesToOpen (&preview);
    };

    setSize (600, 400);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    openFile.setBounds (8, 8, 100, 20);
}
