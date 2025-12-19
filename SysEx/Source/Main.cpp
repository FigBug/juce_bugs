#include <JuceHeader.h>
#include "MainComponent.h"

class SysExApplication : public juce::JUCEApplication
{
public:
    SysExApplication() {}

    const juce::String getApplicationName() override       { return ProjectInfo::projectName; }
    const juce::String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override             { return true; }

    void initialise (const juce::String& commandLine) override
    {
        bool isReceiver = commandLine.contains ("--receiver");

        juce::String windowTitle = getApplicationName();
        windowTitle += isReceiver ? " (Receiver)" : " (Sender)";

        mainWindow.reset (new MainWindow (windowTitle, isReceiver));

        // If we're the sender, launch the receiver instance
        if (! isReceiver)
        {
            auto exePath = juce::File::getSpecialLocation (juce::File::currentExecutableFile);
            receiverProcess.start (exePath.getFullPathName() + " --receiver");
        }
    }

    void shutdown() override
    {
        mainWindow = nullptr;

        if (receiverProcess.isRunning())
            receiverProcess.kill();
    }

    void systemRequestedQuit() override
    {
        quit();
    }

    void anotherInstanceStarted (const juce::String&) override {}

    class MainWindow : public juce::DocumentWindow
    {
    public:
        MainWindow (juce::String name, bool isReceiver)
            : DocumentWindow (name,
                              juce::Desktop::getInstance().getDefaultLookAndFeel()
                                  .findColour (juce::ResizableWindow::backgroundColourId),
                              DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar (true);
            setContentOwned (new MainComponent (isReceiver), true);

            if (isReceiver)
                setTopLeftPosition (100, 150);
            else
                setTopLeftPosition (520, 150);

            setVisible (true);
        }

        void closeButtonPressed() override
        {
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

private:
    std::unique_ptr<MainWindow> mainWindow;
    juce::ChildProcess receiverProcess;
};

START_JUCE_APPLICATION (SysExApplication)
