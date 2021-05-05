#include <visualizer/edit_mode.h>

namespace autocorrect {

namespace visualizer {

void EditMode::HandleKeyDownEvent(ci::app::KeyEvent event) {
    switch (event.getCode()) {
        case ci::app::KeyEvent::KEY_BACKSPACE:
            if (!text_string_.empty()) {
                text_string_.erase(text_string_.size() - 1, 1);
            }
            break;
        default:
            if (event.getChar()) {
                text_string_ += event.getChar();
            }
    }
}

void EditMode::SetTextString(const string &text_string) {
    text_string_ = text_string;
}

string EditMode::GetTextString() {
    return text_string_;
}

}  // namespace visualizer
}  // namespace autocorrect
