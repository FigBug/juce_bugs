#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 400);
	setOpaque ( true );
	//setBufferedToImage ( true );
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
	//g.fillAll ( juce::Colours::orange );

	constexpr auto	cornerRadius = 5.0f;
	constexpr auto	shadowSize = 12;

	const auto	b = getLocalBounds ().toFloat ().withTrimmedLeft ( 162.0f ).reduced ( 6.0f );

	// Silver background
	{
		juce::RectangleList<float>	rl;

		rl.add ( getLocalBounds ().toFloat () );
		rl.subtract ( b.reduced ( cornerRadius ) );

		g.setColour ( juce::Colours::silver );
		g.fillRectList ( rl );
	}

	// Simulate shadow by drawing transparent outlines
	{
		const auto	sr = b.withTrimmedTop ( 13.0f );
		for ( auto i = 0; i < shadowSize; ++i )
		{
			const auto	shadowAlpha = 1.0f - i / float ( shadowSize - 1 );

			g.setColour ( juce::Colours::black.withAlpha ( shadowAlpha * shadowAlpha * 0.25f ) );
			g.drawRoundedRectangle ( sr.expanded ( float ( i ) ), cornerRadius + i, 1.0f );
		}
	}

	g.saveState ();

	// Set clip region
	{
		juce::Path	p;

		p.addRoundedRectangle ( b, cornerRadius );
		g.reduceClipRegion ( p );

		//g.reduceClipRegion ( b.toNearestInt () );
	}

	// Blueish background gradient
	{
		auto	gradRect = juce::Rectangle<float> { b.getTopLeft (), b.getTopLeft () + juce::Point<float> ( 331.5f * 1.41f, 331.5f * 1.41f ) };

		const auto	col1 = juce::Colours::green.overlaidWith ( juce::Colours::red.withAlpha ( 0.64f ) );
		const auto	col2 = juce::Colours::green.overlaidWith ( juce::Colours::yellow.withAlpha ( 0.0f ) );

		const auto	grad = juce::ColourGradient ( col1, b.getTopLeft (),
												  col2, b.getTopLeft () + juce::Point<float> ( 331.5f, 331.5f ),
												  true );
		g.setGradientFill ( grad );
		g.fillRect ( gradRect.expanded ( 1.0f ) );

		// Non-gradient part
		{
			juce::RectangleList<float>	rl;

			rl.add ( getLocalBounds ().toFloat () );
			rl.subtract ( gradRect.reduced ( 1.0f ) );

			g.setColour ( col2 );
			g.fillRectList ( rl );
		}
	}

	g.restoreState ();
}

void MainComponent::resized()
{

}
