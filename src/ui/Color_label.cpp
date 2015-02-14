#include "Color_label.h"
#include <iostream>

ColorLabel::ColorLabel(int w, int h, string la):label(la)
{
    c_text.set_rgb_p(1, 1, 1);
    c_back.set_grey(0);
    this->w=w;
    this->h=h;
}

ColorLabel::ColorLabel(int w, int h, string la, Gdk::Color color, Gdk::Color background_color):label(la), c_text(color), c_back(background_color)
{
    this->h=h;
    this->w=w;
}

ColorLabel::~ColorLabel()
{
}

bool ColorLabel::draw_text(const Cairo::RefPtr<Cairo::Context>& cr, Glib::RefPtr<Pango::Layout> layout)
{
    Pango::FontDescription font;
    font.set_family("Monospace");
    font.set_weight(Pango::WEIGHT_BOLD);
    layout->set_font_description(font);

    layout->update_from_cairo_context(cr);

    return 0;
}

bool ColorLabel::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    Glib::RefPtr<Pango::Layout> lyo1=create_pango_layout(label);

    draw_text(cr, lyo1);
    int text_width1, text_height1;
    lyo1->get_pixel_size(text_width1, text_height1);

    if(text_width1>w)
        set_size_request(text_width1, text_height1);
    else
        set_size_request(w, text_height1);

    cr->set_source_rgb(c_back.get_red_p(), c_back.get_green_p(), c_back.get_blue_p());

    cr->rectangle(2, 2, text_width1, text_height1);
    cr->fill();
    cr->save();
    cr->move_to(2, 2);
    cr->set_source_rgb(c_text.get_red_p(), c_text.get_green_p(), c_text.get_blue_p());
    lyo1->show_in_cairo_context(cr);

    return true;
}
