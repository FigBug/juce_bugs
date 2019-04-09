/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public Component,
                        private OSCReceiver::Listener<OSCReceiver::MessageLoopCallback>,
                        private Timer
{
public:
    //==============================================================================
    MainComponent()
    {
        setSize (600, 400);
        recv.addListener (this);
        bool ok = recv.connect (34531);
        jassert (ok);
        
        startTimerHz (1);
        
        ok = send.connect ("127.0.0.1", 34531);
        jassert (ok);
        
        is_number ("cow");
        is_number ("123");
        is_number ("12cow");
        is_number ("cow12");
    }

    ~MainComponent();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void timerCallback() override
    {
        String bigString;
        
        for (int i = 0; i < 800; i++)
            bigString += "1234567890";
        
        OSCMessage m ("/test", bigString);
        
        bool ok = send.send (m);
        jassert (ok);
        
        if (ok)
            DBG("Send size: " + String (bigString.length()));
    }
    
    void oscMessageReceived (const OSCMessage& m) override
    {
        if (m.size() == 1)
        {
            auto arg = m[0];
            if (arg.isString())
            {
                auto s = arg.getString();
                DBG(String ("Recv Size: ") + String (s.length()) + String (" ") + s);
            }
        }
    }
    
    void oscBundleReceived (const OSCBundle& bundle) override
    {
        for (auto e : bundle)
            if (e.isMessage())
                oscMessageReceived (e.getMessage());
    }
    
    bool is_number(const juce::String& s)
    {
        auto t = s.getCharPointer();
        while (*t)
        {
            if (! t.isDigit())
                return false;
            
            t++;
        }
        
        return true;
    }

private:
    //==============================================================================
    OSCReceiver recv;
    OSCSender send;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
