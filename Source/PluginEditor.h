#pragma once
#include "PluginProcessor.h"

class AudioPluginAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor&);
    ~AudioPluginAudioProcessorEditor() override;
    void paint (juce::Graphics&) override;
    void resized() override;
private:
    juce::Label label;
    AudioPluginAudioProcessor& audioProcessor;
};
