#include <visualizer/autocorrect_app.h>

namespace autocorrect {

namespace visualizer {

AutocorrectApp::AutocorrectApp() {
    std::ifstream ifs("../../../data/saved_autocorrect");
    ifs >> autocorrect_;
    ci::app::setWindowSize((int) kXWindowSize, (int) kYWindowSize);
    textBox = TextBox().font( kFont)
            .size( vec2(kXWindowSize - 5*kMargin,
                        kYWindowSize - kMargin))
            .color(ci::Color("black"))
            .backgroundColor(ci::Color("white"));
}




}  // namespace visualizer

}  // namespace autocorrect
