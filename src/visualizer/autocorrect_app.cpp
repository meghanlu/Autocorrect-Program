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

    void AutocorrectApp::draw() {
        ci::gl::clear(ci::Color8u(255, 246, 148));

        ci::gl::draw(ci::gl::Texture2d::create( textBox.render()),
                     kTextBoxOffset);

        if (!is_edit_mode_) correction_mode_.Draw();
    }





}  // namespace visualizer

}  // namespace autocorrect
