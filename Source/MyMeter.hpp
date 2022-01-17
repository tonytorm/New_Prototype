
#pragma once
#include <JuceHeader.h>
#include "MyBubbles.h"
/** A class used to draw meters on the GUI*/
class MyMeter : public juce::Component,
                       juce::Timer
{
public:
    /** Constructor */
    MyMeter();
    // Component
    void paint(Graphics& g) override;
    // Timer
    void timerCallback() override;
    /** Simply takes and return an integer value, used to change RGBA values in colors */
    int changeColour(int value);
    /** sets the level on which the meter will be based */
    void setLevel(const float value);
    /**  sets the framerate at which thiis component is being painted*/
    void setFrameCount(float frameCount);
    /** sets the sliderIsDragged value which is used to trigger animations*/
    void isSliderDragging(bool checker);
private:
    float frameCount;
    float myLevel = -60.f;
    int colourChanger = 0;
    int pX = 0;
    float myRadius = 0;
    float mySpeed= 0;
    std::list<MyBubbles> bubbles;
    MyBubbles* yo;
    bool SliderisDragged = false;
};
