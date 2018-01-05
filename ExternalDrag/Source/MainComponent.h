/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
class SourceComp : public ListBox,
                   public ListBoxModel
{
public:
    SourceComp()
    {
        setModel (this);

        File dir = File::getSpecialLocation (File::userDocumentsDirectory);
        printf ("%s\n", dir.getFullPathName().toRawUTF8());

        dir.findChildFiles (files, File::findFilesAndDirectories, false, "*.*");

        for (auto f : files)
            printf ("%s\n", f.getFullPathName().toRawUTF8());

        updateContent();
    }

    int getNumRows() override
    {
        return files.size();
    }

    void paintListBoxItem (int, Graphics&, int, int, bool) override
    {
    }

    Component* refreshComponentForRow (int rowNumber, bool, Component* existingComponentToUpdate) override
    {
        RowComp* c = dynamic_cast<RowComp*>(existingComponentToUpdate);

        if (c == nullptr)
            c = new RowComp();

        c->f = files[rowNumber];
        c->repaint();

        return c;
    }

    class RowComp : public Component
    {
    public:
        void mouseDrag (const MouseEvent&) override
        {
            StringArray str;
            str.add (f.getFullPathName());

            DragAndDropContainer::performExternalDragDropOfFiles (str, true, this);
        }

        void paint (Graphics& g) override
        {
            g.setColour (Colours::white);
            g.drawText (f.getFileName(), getLocalBounds().reduced (4), Justification::centredLeft);
        };

        File f;
    };

    Array<File> files;
};

//==============================================================================
class DestComp : public Component,
                 public FileDragAndDropTarget
{
public:
    bool isInterestedInFileDrag (const StringArray&) override
    {
        return true;
    }

    void fileDragEnter (const StringArray&, int, int) override
    {
        dragOver = true;
        repaint();
    }

    void fileDragExit (const StringArray&) override
    {
        dragOver = false;
        repaint();
    }

    void filesDropped (const StringArray& files, int, int) override
    {
        dragOver = false;
        text = files.joinIntoString ("\n");
        repaint();
    }

    void paint (Graphics& g) override
    {
        if (dragOver)
        {
            g.setColour (Colours::white.withAlpha (0.2f));
            g.fillAll();
        }
        g.setColour (Colours::white);
        g.drawMultiLineText (text, 8, 20, getWidth() - 16);
    }

    String text;
    bool dragOver = false;
};

//==============================================================================
class MainContentComponent   : public Component
{
public:
    //==============================================================================
    MainContentComponent();
    ~MainContentComponent();

    void paint (Graphics&) override;
    void resized() override;

private:
    SourceComp srcComp;
    DestComp dstComp;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};
