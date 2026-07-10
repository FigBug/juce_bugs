#pragma once

#include <JuceHeader.h>

/*  Demonstrates that juce::Timer::startTimer() must not be called from a
    background thread.  The constructor kicks off the thread, and the thread's
    run() method calls startTimer() - which should trigger a JUCE assertion
    (the timer thread / message-manager machinery is not thread safe).
*/
class ThreadedTimer : public juce::Thread,
                      public juce::Timer
{
public:
    ThreadedTimer (int idToUse)
        : juce::Thread ("ThreadedTimer " + juce::String (idToUse)),
          id (idToUse)
    {
        startTimer (1);
        startThread();
    }

    ~ThreadedTimer() override
    {
        stopThread (2000);
        stopTimer();
    }

    void run() override
    {
        while (! juce::Thread::threadShouldExit())
            startTimer (1);
    }

    void timerCallback() override
    {
        stopTimer();
    }

private:
    int id = 0;
    std::atomic<int> callbackCount { 0 };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ThreadedTimer)
};
