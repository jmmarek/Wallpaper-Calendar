#pragma once
#include <gdkmm/color.h>

//Decorator
class Color
{
public:
    Color() {
        color.set_rgb_p(0.5, 0.5, 0.5);
    }
    Color(Gdk::Color color): color(color) {
    }
    Color(float r, float g, float b) {
        color.set_rgb_p(r,g,b);
    }

    Gdk::Color getColor() const {
        return color;
    }
    Gdk::Color getRevertColor() const {
        Gdk::Color color_(color);

        if(color_.get_red() > 105 && color_.get_red() < 150)
            color_.set_red(0);
        if(color_.get_green() > 105 && color_.get_green() < 150)
            color_.set_green(0);
        if(color_.get_blue() > 105 && color_.get_blue() < 150)
            color_.set_blue(0);

        color_.set_rgb_p(255 - color_.get_red(), 255 - color_.get_green(), 255 - color_.get_blue());
        return color_;
    }
private:
    Gdk::Color color;
};
