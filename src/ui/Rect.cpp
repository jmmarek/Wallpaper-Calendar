#include "Rect.h"
#include <iostream>

Rect::Rect(int w, int h, string color)//TODO change void
{
    signal_draw().connect(sigc::mem_fun(*this, &Rect::on_draw), false);
    set_size_request(w, h);
    label="";
    this->w=w;
    this->h=h;
}

Rect::~Rect()
{
}

bool Rect::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    cr->set_source_rgb(0.1, 0.8, 0.1);
    cr->rectangle(0, 0, 800, 100);
    cr->fill();
    cr->save();

    cr->set_source_rgb(0, 0.1, 0.1);
    cr->scale(1.5, 1.5);
    Pango::FontDescription font;
    //cr->scale(10, 10);
    font.set_family("Monospace");
    //font.set_size(16);
    font.set_weight(Pango::WEIGHT_BOLD);

    // http://developer.gnome.org/pangomm/unstable/classPango_1_1Layout.html

    Glib::RefPtr<Pango::Layout> layout = create_pango_layout(label);

    layout->set_font_description(font);

    int text_width;
    int text_height;

    //get the text dimensions (it updates the variables -- by reference)
    layout->get_pixel_size(text_width, text_height);

    if(text_width>w)
        set_size_request(text_width, h);
    else
        set_size_request(w, h);
    // Position the text in the middle
    if(w/2-text_width>0)
        cr->move_to(w/2-text_width, -2);
    else
        cr->move_to(0, -2);

    layout->show_in_cairo_context(cr);

    return true;
}
