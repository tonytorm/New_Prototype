
#include "MyMeter.hpp"

MyMeter::MyMeter() 
{

}



void MyMeter::paint(Graphics& g)
{
    // create background rectangles
    auto bounds = getLocalBounds().toFloat();
    g.setColour(juce::Colour(250, 250 - colourChanger * 8, 210 - colourChanger*10).withBrightness(0.4));
    g.fillRect(bounds);
    // create actual meters rectangles
    g.setColour(juce::Colour(250, 250 - colourChanger * 8, 210 - colourChanger*10));
    const auto scaledX = jmap(myLevel, -60.f, 6.f, 0.f, static_cast<float>(getHeight()));
    g.fillRoundedRectangle(bounds.removeFromBottom(scaledX), 3.f);
    // create bubbles
    g.setColour(juce::Colour(250, 250 - colourChanger * 8, 210 - colourChanger*10).withBrightness(0.4));
    int radius = 150;
    int random = juce::Random::getSystemRandom().nextInt(getWidth()-60);
    float randomRadius = (juce::Random::getSystemRandom().nextInt(30));
    float randomSpeed = (juce::Random::getSystemRandom().nextFloat()* 0.02)+ 0.02;
    
    if (frameCount == 1)  // only pass the random values once every frame 'loop'
    {
        myRadius = randomRadius;
        pX = random;
        mySpeed = randomSpeed;
    }
    
    juce::Point<float> p ((float) pX,
                                 (float) getHeight() - (2.0f + 1.0f * (float) radius * (frameCount * mySpeed)));
    
    if (SliderisDragged) // only paint bubbles if slider is being dragged
    {
        g.drawEllipse (p.x, p.y, myRadius, myRadius, 1.0f);
        g.drawEllipse (p.x + (myRadius * 4.0f), p.y - myRadius*5.f, myRadius+5, myRadius+5, 1.0f);
        g.drawEllipse (p.x - (myRadius * 4.0f), p.y + myRadius*5.f, myRadius+2, myRadius+2, 1.0f);
    }
    g.setColour(Colours::black);
    g.drawLine(0, getHeight()-1, getWidth(), getHeight()-1, 2.0f);
}

void MyMeter::setLevel(const float value)
{
    myLevel = value;
}

int MyMeter::changeColour(int value)
{
    colourChanger = value;
    return colourChanger;
}

void MyMeter::setFrameCount(float frames)
{
    frameCount = frames;
}

void MyMeter::timerCallback()
{
    
}

void MyMeter::isSliderDragging(bool checker)
{
    SliderisDragged = checker;
}
