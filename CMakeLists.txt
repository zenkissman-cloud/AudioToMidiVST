cmake_minimum_required(VERSION 3.15)
project(AudioToMidiVST VERSION 0.0.1)

include(FetchContent)
FetchContent_Declare(
  juce
  GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
  GIT_TAG 7.0.5
)
FetchContent_MakeAvailable(juce)

juce_add_plugin(AudioToMidiVST)

target_sources(AudioToMidiVST
    PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginEditor.cpp
)

target_link_libraries(AudioToMidiVST PRIVATE
    juce::juce_audio_utils
    juce::juce_audio_processors
    juce::juce_audio_devices
    juce::juce_gui_basics
)

juce_set_plugin_gui_framework(AudioToMidiVST JUCE_GUI_BASICS)
