
#pragma once
#include <JuceHeader.h>

/** a class for Bubble animation, unused and undeveloped at this stage*/
class MyBubbles
{
public:
    /** Constructor, used to set bubble coordinates and speed  parameters*/
    MyBubbles(float x, float y, float sp);
    /** increments bubble position on Y axis*/
    void advance(int count);
   
    juce::Point<float> position;
    float speed;
private:
    juce::Colour background;
    
    
};
