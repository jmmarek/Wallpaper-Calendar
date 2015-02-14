#include <gtkmm.h>
#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <sstream>
#include "Image.h"
#include "../Event.h"
#include "../Controler.h"
#include "Day.h"
#include "Color_label.h"
using namespace std;

#include "Add_event.h"

#ifndef DAY_VIEW_H
#define DAY_VIEW_H

///The class contain window which is used to add/delete and edit events for each day
class Day_view: public Gtk::Window
{
public:
    Day_view();
    virtual ~Day_view();
    void setDay(Day *d, bool *actual);

    void drawTable();///<Drawind table
    void redrawTable();///<Calling redraw

    void attachBy();///<This method will be called by Add_event when it works in add mode
    void changeBy();///<This method will be called by Add_event when it works in edit mode


protected:
    bool removeEvent(GdkEventButton* event, unsigned int id);
    bool Destroy(GdkEventAny* event);
    void addEvent();
    void setEventParameters(Event *e, int event_id = -1);
    bool editEvent(GdkEventButton* event, int id);
    vector <Event> *events;///<Pointer to vector stored in day class

    vector <Gtk::Widget*> widgets;

    Day *day;///<Pointer to current day
    bool *actual;///<Pointer to Calendar::actual to call refresh after changes
    Add_event *add_event;
    Gtk::Grid *container;///<Container for all graphic object in Day View Window
    Gtk::Button add_button;///<Button to add new event
};
#endif
