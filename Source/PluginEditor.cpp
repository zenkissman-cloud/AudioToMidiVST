#include "PluginProcessor.h"
#include "PluginEditor.h"

AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p) 
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    label.setText ("Audio to MIDI Active", juce::dontSendNotification);
    label.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (label);
    setSize (200, 100);
}
AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor() {}
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g) { g.fillAll (juce::Colours::darkgrey); }
void AudioPluginAudioProcessorEditor::resized() { label.setBounds (getLocalBounds()); }
