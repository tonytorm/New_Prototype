
#include "OtherLookAndFeel.hpp"
OtherLookAndFeel::OtherLookAndFeel()
{
   // grab SVG image from resources
    cogImage = juce::Drawable::createFromSVG( *std::unique_ptr<juce::XmlElement>(
                                                                 juce::XmlDocument::parse (BinaryData::rightsize_svg)));
    // get the image as a path
    cogPath = cogImage->getOutlineAsPath();
    
    
}

void OtherLookAndFeel::drawRotarySlider (Graphics &g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider &)
{
    float centreX = x + width/2;
    float centreY = y + height/2;
    float angle = rotaryStartAngle + (sliderPosProportional * (rotaryEndAngle - rotaryStartAngle));
    
    Rectangle<float> boundingBox(centreX, centreY, 100, 100);
    cogImage->setTransformToFit(boundingBox, RectanglePlacement::stretchToFit);
    g.setColour(Colour(255, 165-colourInt, 0));
   
    // assign rotation and pivotal point to image
    cogImage->setTransform(AffineTransform::rotation((angle), cogImage->getBounds().getCentreX(), cogImage->getBounds().getCentreY()).scaled(2.0f, 2.0f
        ,cogImage->getBounds().getCentreX(), cogImage->getBounds().getCentreY()));

    cogImage->drawAt(g, centreX, centreY, 0.8f);
   

}

int OtherLookAndFeel::colourChanger(int changer)
{
    colourInt = changer;
    return colourInt;
}
