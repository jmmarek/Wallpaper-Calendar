#include "Image.h"
#include <iostream>

Image::Image(int w, int h, string fn, string la)
{
    set_size_request(w, h);
    filename=fn;
    label=la;
    this->w=w;
    this->h=h;
}

Image::~Image()
{
}

bool Image::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    Glib::RefPtr<Gdk::Pixbuf> image = Gdk::Pixbuf::create_from_file(filename);
    // Draw the image at 110, 90, except for the outermost 10 pixels.
    Gdk::Cairo::set_source_pixbuf(cr, image, 0, 0);
    cr->rectangle(0, 0, image->get_width(), image->get_height());
    cr->fill();
    cr->save();

    cr->set_source_rgb(0, 0.1, 0.1);
    cr->scale(1.5, 1.5);
    Pango::FontDescription font;
    font.set_family("Monospace");
    font.set_weight(Pango::WEIGHT_BOLD);

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
