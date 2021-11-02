#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component, public juce::FileDragAndDropTarget
{
public:
    //==============================================================================
    struct Drop
    {
        juce::String name;
        int x;
        int y;
    };

    juce::Array<Drop> drops;
    bool dragging = false;

    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void resized() override;

    bool isInterestedInFileDrag (const juce::StringArray& files) override
    {
        return true;
    }

    void filesDropped (const juce::StringArray& files, int x, int y) override
    {
        drops.add ({juce::File (files[0]).getFileName(), x, y});
        repaint();
    }

    void mouseDown ( const juce::MouseEvent& ) override
    {
        dragging = false;
    }

    void mouseDrag ( const juce::MouseEvent& e ) override
    {
        if (! dragging && e.getDistanceFromDragStart() > 10)
        {
            dragging = true;

            juce::StringArray files;
            files.add (juce::File::getSpecialLocation (juce::File::userDesktopDirectory).getFullPathName());

            juce::DragAndDropContainer::performExternalDragDropOfFiles (files, true, getTopLevelComponent());
        }
    }


private:


    void paint (juce::Graphics& g) override
    {
        g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

        g.setFont (juce::Font (16.0f));
        g.setColour (juce::Colours::white);

        for (auto& d : drops)
        {
            g.drawText (d.name, juce::Rectangle<int> (d.x, d.y, 100, 20), juce::Justification::topLeft, true);
        }
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
