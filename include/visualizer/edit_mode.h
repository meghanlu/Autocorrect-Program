#pragma once

#include "cinder/app/App.h"
#include "cinder/gl/gl.h"

namespace autocorrect {
using std::string;

namespace visualizer {

/**
 * When using EditMode, text in the textbox can be changed by user key input.
 */
class EditMode {
public:

    /**
     * Updates text string by user key input.
     */
    void HandleKeyDownEvent(ci::app::KeyEvent event);

    /**
     * Sets text string (usually used when switching back to edit mode).
     */
    void SetTextString(string const& text_string);

    /**
     * Gets last edited text string.
     */
    string GetTextString();

private:
    string text_string_;

};

}  // namespace autocorrect

}  // namespace naivebayes
