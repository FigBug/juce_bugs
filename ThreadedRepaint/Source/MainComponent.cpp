/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() : Thread ("MyThread")
{
    setSize (600, 400);
    startTimerHz (20);
}

MainComponent::~MainComponent()
{
    stopThread (1000);
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    jassert(MessageManager::getInstance()->isThisTheMessageThread());
    
    auto& r = Random::getSystemRandom();
    g.fillAll (Colour (r.nextInt (255),
                       r.nextInt (255),
                       r.nextInt (255)));
}

void MainComponent::resized()
{
}

void MainComponent::run()
{
    MessageManagerLock mml (Thread::getCurrentThread());
    
    if (! mml.lockWasGained())
        return;
    
    repaint();
}

void MainComponent::timerCallback()
{
    startThread();
}
