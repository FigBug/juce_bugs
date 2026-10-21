cmake_minimum_required(VERSION 3.22)
project(JSFunctionLifetime VERSION 1.0.0)

add_subdirectory(../JUCE JUCE)

juce_add_console_app(JSFunctionLifetime PRODUCT_NAME "JSFunctionLifetime")

target_sources(JSFunctionLifetime PRIVATE Source/Main.cpp)

target_compile_definitions(JSFunctionLifetime PRIVATE
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0)

target_link_libraries(JSFunctionLifetime PRIVATE
    juce::juce_javascript
    juce::juce_core
    juce::juce_recommended_config_flags
    juce::juce_recommended_warning_flags)
