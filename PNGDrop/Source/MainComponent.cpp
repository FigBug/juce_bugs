#include "MainComponent.h"

MainComponent::MainComponent()
{
    setSize (600, 400);
}

MainComponent::~MainComponent()
{
}

void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::darkgrey);

    if (isDownloading)
    {
        g.setColour (juce::Colours::white);
        g.setFont (juce::FontOptions (24.0f));
        g.drawText ("Downloading...", getLocalBounds(), juce::Justification::centred);
        return;
    }

    if (loadedImage.isValid())
    {
        // Calculate scaling to fit image within component while maintaining aspect ratio
        auto bounds = getLocalBounds().reduced (20);
        float imageAspect = (float) loadedImage.getWidth() / (float) loadedImage.getHeight();
        float boundsAspect = (float) bounds.getWidth() / (float) bounds.getHeight();

        juce::Rectangle<float> destRect;

        if (imageAspect > boundsAspect)
        {
            // Image is wider than bounds
            float height = bounds.getWidth() / imageAspect;
            destRect = juce::Rectangle<float> (
                (float) bounds.getX(),
                bounds.getCentreY() - height / 2.0f,
                (float) bounds.getWidth(),
                height);
        }
        else
        {
            // Image is taller than bounds
            float width = bounds.getHeight() * imageAspect;
            destRect = juce::Rectangle<float> (
                bounds.getCentreX() - width / 2.0f,
                (float) bounds.getY(),
                width,
                (float) bounds.getHeight());
        }

        g.drawImage (loadedImage, destRect);

        // Draw filename at the bottom
        g.setColour (juce::Colours::white);
        g.setFont (juce::FontOptions (14.0f));
        g.drawText (imagePath, getLocalBounds().removeFromBottom (30), juce::Justification::centred);
    }
    else
    {
        // Draw drop zone placeholder
        auto bounds = getLocalBounds().reduced (40);

        if (isDraggingOver)
            g.setColour (juce::Colours::lightgreen.withAlpha (0.3f));
        else
            g.setColour (juce::Colours::grey.withAlpha (0.3f));

        g.fillRoundedRectangle (bounds.toFloat(), 10.0f);

        g.setColour (isDraggingOver ? juce::Colours::lightgreen : juce::Colours::grey);
        g.drawRoundedRectangle (bounds.toFloat(), 10.0f, 2.0f);

        g.setColour (isDraggingOver ? juce::Colours::white : juce::Colours::lightgrey);

        g.setFont (juce::FontOptions (24.0f));
        g.drawText ("Drop PNG Here", bounds, juce::Justification::centred);

        g.setFont (juce::FontOptions (14.0f));
        g.drawText ("Drag and drop a PNG file or URL from your browser",
                    bounds.withTrimmedTop (40), juce::Justification::centred);
    }
}

void MainComponent::resized()
{
}

bool MainComponent::isInterestedInFileDrag (const juce::StringArray& files)
{
    for (const auto& file : files)
    {
        if (file.endsWithIgnoreCase (".png"))
            return true;
    }
    return false;
}

void MainComponent::fileDragEnter (const juce::StringArray& files, int x, int y)
{
    juce::ignoreUnused (x, y);

    for (const auto& filePath : files)
    {
        if (! filePath.endsWithIgnoreCase (".png"))
        {
            juce::File file (filePath);
            DBG ("Unsupported format: " + file.getFileExtension());
        }
    }

    isDraggingOver = true;
    repaint();
}

void MainComponent::fileDragExit (const juce::StringArray& files)
{
    juce::ignoreUnused (files);
    isDraggingOver = false;
    repaint();
}

void MainComponent::filesDropped (const juce::StringArray& files, int x, int y)
{
    juce::ignoreUnused (x, y);
    isDraggingOver = false;

    for (const auto& filePath : files)
    {
        if (filePath.endsWithIgnoreCase (".png"))
        {
            juce::File file (filePath);
            loadedImage = juce::ImageFileFormat::loadFrom (file);

            if (loadedImage.isValid())
            {
                imagePath = file.getFileName();
                repaint();
                return;
            }
        }
    }
}

bool MainComponent::isInterestedInTextDrag (const juce::String& text)
{
    // Accept URLs that look like PNG images
    auto trimmed = text.trim();

    if (trimmed.startsWithIgnoreCase ("http://") || trimmed.startsWithIgnoreCase ("https://"))
    {
        // Check if URL path ends with .png (ignore query params)
        juce::URL url (trimmed);
        auto path = url.getSubPath();
        return path.endsWithIgnoreCase (".png");
    }

    return false;
}

void MainComponent::textDragEnter (const juce::String& text, int x, int y)
{
    juce::ignoreUnused (text, x, y);
    isDraggingOver = true;
    repaint();
}

void MainComponent::textDragExit (const juce::String& text)
{
    juce::ignoreUnused (text);
    isDraggingOver = false;
    repaint();
}

void MainComponent::textDropped (const juce::String& text, int x, int y)
{
    juce::ignoreUnused (x, y);
    isDraggingOver = false;

    auto trimmed = text.trim();
    DBG ("URL dropped: " + trimmed);

    loadImageFromURL (trimmed);
}

void MainComponent::loadImageFromURL (const juce::String& urlString)
{
    isDownloading = true;
    repaint();

    // Run download on background thread
    auto safeThis = juce::Component::SafePointer<MainComponent> (this);

    std::thread ([safeThis, urlString]()
    {
        juce::URL url (urlString);
        juce::Image downloadedImage;
        juce::String fileName;

        auto inputStream = url.createInputStream (juce::URL::InputStreamOptions (juce::URL::ParameterHandling::inAddress)
                                                      .withConnectionTimeoutMs (10000)
                                                      .withNumRedirectsToFollow (5));

        if (inputStream != nullptr)
        {
            juce::MemoryBlock data;
            inputStream->readIntoMemoryBlock (data);

            downloadedImage = juce::ImageFileFormat::loadFrom (data.getData(), data.getSize());
            fileName = juce::URL (urlString).getFileName();
        }

        juce::MessageManager::callAsync ([safeThis, downloadedImage, fileName]()
        {
            if (safeThis != nullptr)
            {
                safeThis->isDownloading = false;

                if (downloadedImage.isValid())
                {
                    safeThis->loadedImage = downloadedImage;
                    safeThis->imagePath = fileName;
                }
                else
                {
                    DBG ("Failed to download or decode image");
                }

                safeThis->repaint();
            }
        });
    }).detach();
}
