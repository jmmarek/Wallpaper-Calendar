#include <gtkmm.h>
#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <sstream>
#include "Image.h"
#include "../Event.h"
#include "Day.h"
using namespace std;
#ifndef ADD_EVENT_H
#define ADD_EVENT_H
class Day_view;

///The clas contains Window with form which is used by Day_view class to add or edit events
class Add_event: public Gtk::Window
{
public:
    Add_event(Day *day, Day_view *parent);
    Add_event(Day *day, Day_view *parent, int event);///<If we want to edit
    virtual ~Add_event();
    void draw();
    Gtk::ComboBox calendar_for_event;
    Gtk::Entry *e;

    int sel_calendar;
    int event_id;//
protected:
    void getCal();
    void addEvent();
    void editEvent();

    Day *day;
    bool *actual;

    Gtk::Grid *container;
    Gtk::Button o_button;

    Glib::RefPtr<Gtk::ListStore> m_refTreeModel;

    void addCalendarCombo();
    class ModelColumns : public Gtk::TreeModel::ColumnRecord
    {
    public:

        ModelColumns() {
            add(m_col_id);
            add(m_col_name);
        }

        Gtk::TreeModelColumn<int> m_col_id;
        Gtk::TreeModelColumn<Glib::ustring> m_col_name;
    };

    ModelColumns m_Columns;
    Day_view *parent;
};
#include "Day_view.h"
#endif
