#include "PluginEditor.h"

SkiAudioProcessorEditor::SkiAudioProcessorEditor(SkiAudioProcessor& processor)
    : AudioProcessorEditor(&processor), audioProcessor(processor)
{
    setSize(560, 340);

    auto setupSlider = [](juce::Slider& slider)
    {
        slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
        slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 90, 22);
        slider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colour(0xffc7ff4d));
        slider.setColour(juce::Slider::thumbColourId, juce::Colour(0xfff1f1eb));
        slider.setColour(juce::Slider::textBoxTextColourId, juce::Colour(0xfff1f1eb));
        slider.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colour(0xff20211f));
        slider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    };

    setupSlider(inputGainSlider);
    setupSlider(outputGainSlider);

    inputGainLabel.setText("INPUT", juce::dontSendNotification);
    outputGainLabel.setText("OUTPUT", juce::dontSendNotification);

    for (auto* label : { &inputGainLabel, &outputGainLabel })
    {
        label->setJustificationType(juce::Justification::centred);
        label->setColour(juce::Label::textColourId, juce::Colour(0xffa6a89f));
        addAndMakeVisible(*label);
    }

    addAndMakeVisible(inputGainSlider);
    addAndMakeVisible(outputGainSlider);

    inputGainAttachment = std::make_unique<SliderAttachment>(
        audioProcessor.parameters, "inputGain", inputGainSlider);
    outputGainAttachment = std::make_unique<SliderAttachment>(
        audioProcessor.parameters, "outputGain", outputGainSlider);
}

void SkiAudioProcessorEditor::paint(juce::Graphics& graphics)
{
    graphics.fillAll(juce::Colour(0xff151613));

    graphics.setColour(juce::Colour(0xfff1f1eb));
    graphics.setFont(juce::Font(juce::FontOptions(34.0f, juce::Font::bold)));
    graphics.drawText("ski", 28, 20, 180, 44, juce::Justification::left);

    graphics.setColour(juce::Colour(0xffa6a89f));
    graphics.setFont(juce::Font(juce::FontOptions(10.0f)));
    graphics.drawText("GRANULAR AUDIO EFFECT", 31, 65, 220, 18, juce::Justification::left);

    graphics.setColour(juce::Colour(0xff34372f));
    graphics.drawRoundedRectangle(24.0f, 105.0f, 512.0f, 205.0f, 12.0f, 1.0f);

    graphics.setColour(juce::Colour(0xffc7ff4d));
    graphics.fillRoundedRectangle(42.0f, 124.0f, 5.0f, 16.0f, 2.0f);

    graphics.setColour(juce::Colour(0xffa6a89f));
    graphics.setFont(juce::Font(juce::FontOptions(10.0f)));
    graphics.drawText("ENGINE INITIALIZING", 56, 124, 180, 16, juce::Justification::left);
}

void SkiAudioProcessorEditor::resized()
{
    inputGainLabel.setBounds(105, 145, 130, 24);
    inputGainSlider.setBounds(105, 165, 130, 120);

    outputGainLabel.setBounds(325, 145, 130, 24);
    outputGainSlider.setBounds(325, 165, 130, 120);
}
