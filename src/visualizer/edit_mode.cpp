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

}  // namespace visualizer
}  // namespace autocorrect
