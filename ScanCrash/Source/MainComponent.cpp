/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

class FakeScanner : public KnownPluginList::CustomScanner
{
public:
    bool findPluginTypesFor (AudioPluginFormat& format, OwnedArray<PluginDescription>& result, const String& fileOrIdentifier) override
    {
        ignoreUnused (format);

        PluginDescription pd;
        pd.category = "Fake";
        pd.descriptiveName = fileOrIdentifier;
        pd.fileOrIdentifier = fileOrIdentifier;
        pd.manufacturerName = fileOrIdentifier;
        pd.name = fileOrIdentifier;
        pd.pluginFormatName = "Fake";
        pd.uid = fileOrIdentifier.getIntValue();
        pd.numInputChannels = 2;
        pd.numOutputChannels = 2;

        result.add (new PluginDescription (pd));

        return true;
    }

    /** Called when a scan has finished, to allow clean-up of resources. */
    void scanFinished() override
    {
    }
};

void wasteMemory()
{
    static Random r;
    int sz = r.nextInt ({ 100, 50000 });
    char* p = (char*) malloc (sz);
    memset (p, 0, sz);
    free (p);
}

//==============================================================================
MainComponent::MainComponent()
    : Thread ("Scan")
{
    setSize (600, 400);

    pluginList.setCustomScanner (new FakeScanner());
    pluginList.addChangeListener (this);
    
    startThread();
}

MainComponent::~MainComponent()
{
    stopThread (1000);
}

void MainComponent::changeListenerCallback (ChangeBroadcaster*)
{
    for (auto pd : pluginList)
    {
        String name = pd->name;
        if (name.getIntValue() % 100 == 0)
            DBG(name);
    }
}

void MainComponent::run()
{
    int cnt = 0;
    OwnedArray<PluginDescription> found;

    auto format = formatManager.getFormat (0);

    while (! threadShouldExit())
    {
        cnt++;
        pluginList.scanAndAddFile (String (cnt), true, found, *format);
        
        for (int i = 0; i < 50; i++)
            wasteMemory();
    }
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setFont (Font (16.0f));
    g.setColour (Colours::white);
    g.drawText ("Hello World!", getLocalBounds(), Justification::centred, true);
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
