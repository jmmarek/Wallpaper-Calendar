#include <stdlib.h>
#include <string.h>
#include <gtkmm.h>
#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <cairo.h>
#include <gtkmm/drawingarea.h>
#include "Calendar.h"
#include <vector>
#include "../Event.h"
#include "../Date.h"

using namespace std;

#ifndef DAY_H
#define DAY_H

///This class draws day rectangle on calendar and handle methods to manipulate content of the day
class Day: public Gtk::DrawingArea//, public Gtk::Button
{
public:
    Day();
    virtual ~Day();
    void setDay(int day, int day_w, bool this_m) { //For labels only
        day_number=day;
        day_week=day_w;
        this_month=this_m;
    }
    void setDay(Date date, int day, int day_w, bool this_m) {
        day_number=day;
        day_date=date;
        day_week=day_w;
        this_month=this_m;
    }
    void setToday() {
        today=true;
    }
    void unsetToday() {
        today=false;
    }
    void onlyLabel() {
        label=true;
    }
    Date getDate() {
        return day_date;
    }

    void setSize(bool t);

    vector <Event> events;///<vector of events which belongs to specified day
    bool update;
    static string global_path;
protected:
    Date day_date;
    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
    bool draw_text(const Cairo::RefPtr<Cairo::Context>& cr, Glib::RefPtr<Pango::Layout> layout);
    int day_number, day_week;
    bool label;
    bool today, this_month;
};
#endif
