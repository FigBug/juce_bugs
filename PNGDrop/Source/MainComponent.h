#pragma once

#include <JuceHeader.h>

class MainComponent : public juce::Component,
                      public juce::FileDragAndDropTarget,
                      public juce::TextDragAndDropTarget
{
public:
    MainComponent();
    ~MainComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    // FileDragAndDropTarget interface
    bool isInterestedInFileDrag (const juce::StringArray& files) override;
    void fileDragEnter (const juce::StringArray& files, int x, int y) override;
    void fileDragExit (const juce::StringArray& files) override;
    void filesDropped (const juce::StringArray& files, int x, int y) override;

    // TextDragAndDropTarget interface
    bool isInterestedInTextDrag (const juce::String& text) override;
    void textDragEnter (const juce::String& text, int x, int y) override;
    void textDragExit (const juce::String& text) override;
    void textDropped (const juce::String& text, int x, int y) override;

private:
    void loadImageFromURL (const juce::String& urlString);

    juce::Image loadedImage;
    juce::String imagePath;
    bool isDraggingOver = false;
    bool isDownloading = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
