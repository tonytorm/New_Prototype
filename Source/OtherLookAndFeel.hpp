
#pragma once

#include <JuceHeader.h>
/** a class to change the look and feel of the slider */
class OtherLookAndFeel : public LookAndFeel_V4
{
    

public:
    /** constructor*/
    OtherLookAndFeel();
    virtual void drawRotarySlider (Graphics &, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider &) override;
    /** Simply takes and return an integer value, used to change RGBA values in colors */
    int colourChanger(int changer);
private:
    int colourInt = 0;
    std::unique_ptr<Drawable> cogImage;
    Path cogPath;
    
};
