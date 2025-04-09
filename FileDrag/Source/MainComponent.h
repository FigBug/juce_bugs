#pragma once

#include <JuceHeader.h>

//==============================================================================
class Target : public juce::Component, public juce::FileDragAndDropTarget
{
public:
	Target()
	{
	}

	void paint (juce::Graphics& g) override
	{
		g.fillAll (dragOver ? juce::Colours::green : juce::Colours::yellow);
	}

	bool isInterestedInFileDrag ( const juce::StringArray& files ) override
	{
		return true;
	}

	void fileDragEnter ( const juce::StringArray& files, int x, int y ) override
	{
		dragOver = true;
		repaint();
	}

	void fileDragExit ( const juce::StringArray& files ) override
	{
		dragOver = false;
		repaint();
	}

	void filesDropped ( const juce::StringArray& files, int x, int y ) override
	{
		dragOver = false;
		repaint();
	}

	bool dragOver = false;
};

//==============================================================================
class Frame : public juce::Component
{
public:
	Frame()
	{
		juce::Desktop::getInstance().addGlobalMouseListener(this);

		setSize (1000, 1000);

		addAndMakeVisible (target);
		target.setBounds (200, 200, 100, 100);
	}

	~Frame() override
	{
		juce::Desktop::getInstance().removeGlobalMouseListener(this);
	}

	Target target;
};

//==============================================================================
class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //==============================================================================
	juce::Viewport viewport;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
