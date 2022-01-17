
#include "FilePlayerGui.hpp"

FilePlayerGui::FilePlayerGui()
{
    playButton.addListener (this);
    addAndMakeVisible (playButton);
    
    AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    fileChooser = std::make_unique<FilenameComponent> ("audiofile",
                                                       File(),
                                                       true, false, false,
                                                       formatManager.getWildcardForAllFormats(),
                                                       String(),
                                                       "(select an audio file)");
    fileChooser->addListener (this);
    addAndMakeVisible (fileChooser.get());
    
    playButton.setColour(TextButton::buttonColourId, Colours::orange);
    playButton.setColour(TextButton::textColourOnId, Colours::goldenrod);
    
}

FilePlayerGui::~FilePlayerGui()
{
    
}

// Component
void FilePlayerGui::paint(Graphics& g)
{

}

void FilePlayerGui::paintOverChildren(Graphics& g)
{
    g.setColour(Colours::orange);
}


void FilePlayerGui::resized()
{
    Rectangle<int> r (getLocalBounds());
    playButton.setBounds (r.removeFromLeft (getHeight()));
    fileChooser->setBounds (r);
}

// Button Listener
void FilePlayerGui::buttonClicked (Button* button)
{
    if (filePlayer != nullptr && button == &playButton)
    {
        filePlayer->setPlaying( ! filePlayer->isPlaying());
    }
}

void FilePlayerGui::setFilePlayer (FilePlayer* fp)
{
    filePlayer = fp;
}

// FilenameComponentListener
void FilePlayerGui::filenameComponentChanged (FilenameComponent* fileComponentThatHasChanged)
{
    if (fileComponentThatHasChanged == fileChooser.get())
    {
        File audioFile (fileChooser->getCurrentFile().getFullPathName());
        
        if(filePlayer != nullptr && audioFile.existsAsFile())
        {
            filePlayer->loadFile(audioFile);
        }

    }
}
