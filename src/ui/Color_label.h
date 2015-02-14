#pragma once
#include <stdlib.h>
#include <string.h>
#include <gtkmm.h>
#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <cairo.h>
#include <gtkmm/drawingarea.h>
using namespace std;
///The class draws label with defined background and text color
class ColorLabel: public Gtk::DrawingArea
{
public:
    ColorLabel(int w, int h, string label, Gdk::Color text_color, Gdk::Color background_color);///<Constructor with custom colors. \param w width of image \param h height of image \param label label \param text_color color of the text \param background_color background color
    ColorLabel(int w, int h, string label);///<Constructor with default colors. \param w width of image \param h height of image \param label label
    virtual ~ColorLabel();
protected:
    string label;///<Label with text
    Gdk::Color c_text, c_back;///<Colors
    bool draw_text(const Cairo::RefPtr<Cairo::Context>& cr, Glib::RefPtr<Pango::Layout> layout);
    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
private:
    int w, h;
    ColorLabel();
};
