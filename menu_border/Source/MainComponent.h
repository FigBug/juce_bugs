#pragma once

#include <JuceHeader.h>

//==============================================================================
class WackyLookAndFeel : public juce::LookAndFeel_V4
{
public:

    int getPopupMenuBorderSize ()
    {
        return 10;
    }
};

class WackyComboBox : public juce::ComboBox
{
public:
	void showPopup() override
	{
		auto& curMenu = *getRootMenu();
		const auto	hasItems = curMenu.getNumItems() > 0;

		int columns = 4;

		juce::PopupMenu& menuToShow = curMenu;
		menuToShow.setLookAndFeel(&getLookAndFeel());
		menuToShow.showMenuAsync(juce::PopupMenu::Options()
			.withTargetComponent(this)
			.withDeletionCheck(*this)
			.withItemThatMustBeVisible(getSelectedId())
			.withMinimumWidth(getWidth())
			.withMinimumNumColumns(columns)
			.withMaximumNumColumns(columns == 1 ? 0 : columns),

			[this](int result)
			{
				hidePopup();

				if (result != 0)
				{
					setSelectedId(result);
				}
			}
		);
	}
};

class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void mouseDown (const juce::MouseEvent&) override;

private:
    //==============================================================================
    WackyLookAndFeel lf;
    WackyComboBox box;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
