
#pragma once

#include <JuceHeader.h>
#include "FilePlayer.hpp"

/** Gui for the FilePlayer class */
class FilePlayerGui :   public Component,
                        private Button::Listener,
                        private FilenameComponentListener
{
public:
    /** constructor - receives a reference to a FilePlayer object to control */
    FilePlayerGui();
    
    /** Destructor */
    ~FilePlayerGui();
    
    /** sets the file player that this gui controls */
    void setFilePlayer (FilePlayer* fp);
    
    //Component
    void resized() override;
    void paint (Graphics& g) override;
    void paintOverChildren (Graphics& g) override;

private:
    //Button Listener
    void buttonClicked (Button* button) override;
    
    //FilenameComponentListener
    void filenameComponentChanged (FilenameComponent* fileComponentThatHasChanged) override;
    
    TextButton playButton   { ">" };
    std::unique_ptr<FilenameComponent> fileChooser;
    
    FilePlayer* filePlayer  { nullptr };
};
