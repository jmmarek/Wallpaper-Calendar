#pragma once
#include <stdlib.h>
#include <string.h>
#include <gtkmm.h>
#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <cairo.h>
#include <gtkmm/drawingarea.h>
using namespace std;
///The class help to display images and text on it
class Rect: public Gtk::DrawingArea
{
public:
    Rect(int w, int h, string color);///<Constructor. \param w width of image \param h height of image \param filename filename \param label label
    virtual ~Rect();

    void setLabel(string s) {
        label=s;
    }

protected:
    int w, h;
    string filename;///<Filename of image
    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);///<Function called by cairo
    string label;///<Label (text on image)
private:
    Rect();
};
