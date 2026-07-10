#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
    Reproduces a crash by hammering the network image path from many threads
    at once.

    On startup we spin up 20 threads. Each thread fetches an image from
    https://picsum.photos/ , decodes it, and then uses
    MessageManager::callAsync() to hand the decoded image back to the message
    thread. MainComponent keeps the most recently received image and paints it.
*/
class MainComponent   : public juce::Component
{
public:
    MainComponent()
    {
        setSize (600, 400);

        for (int i = 0; i < numThreads; ++i)
            threads.push_back (std::thread ([this] { fetchLoop(); }));
    }

    ~MainComponent() override
    {
        shouldExit = true;

        for (auto& t : threads)
            if (t.joinable())
                t.join();
    }

    void paint (juce::Graphics& g) override
    {
        g.fillAll (juce::Colours::darkgrey);

        if (mostRecent.isValid())
            g.drawImage (mostRecent, getLocalBounds().toFloat(),
                         juce::RectanglePlacement::centred);

        g.setColour (juce::Colours::white);
        g.setFont (14.0f);
        g.drawText ("Received: " + juce::String (received),
                    getLocalBounds().reduced (8), juce::Justification::topLeft);
    }

    void resized() override
    {
    }

private:
    //==============================================================================
    void fetchLoop()
    {
        while (! shouldExit)
        {
            juce::URL url ("https://picsum.photos/600/400");

            int statusCode = 0;

            auto options = juce::URL::InputStreamOptions (juce::URL::ParameterHandling::inAddress)
                               .withConnectionTimeoutMs (10000)
                               .withNumRedirectsToFollow (5)
                               .withExtraHeaders ("User-Agent: NetworkImageCrash/1.0")
                               .withStatusCode (&statusCode);

            if (auto stream = url.createInputStream (options))
            {
                // Read the whole body into memory first, then decode. Decoding
                // straight from a non-seekable WebInputStream breaks format
                // detection (see juce_ImageFileFormat findImageFormatForStream).
                juce::MemoryBlock body;
                stream->readIntoMemoryBlock (body);

                auto image = juce::ImageFileFormat::loadFrom (body.getData(), body.getSize());

                if (! image.isValid())
                    DBG ("decode failed, status=" << statusCode
                          << " received=" << body.getSize());

                if (image.isValid())
                {
                    juce::MessageManager::callAsync ([this, image]
                    {
                        mostRecent = image;
                        ++received;
                        repaint();
                    });
                }
            }
            else
            {
                DBG ("createInputStream failed, status=" << statusCode);
            }
        }
    }

    static constexpr int numThreads = 20;

    std::vector<std::thread> threads;
    std::atomic<bool> shouldExit { false };

    juce::Image mostRecent;
    int received = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
