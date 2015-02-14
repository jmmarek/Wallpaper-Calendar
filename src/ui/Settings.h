#include <gtkmm.h>
#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <sstream>

#include "../Controler.h"
#include "../Date.h"
#include "../Parser.h"

using namespace std;

#ifndef SETTINGS_H
#define SETTINGS_H

///The window contain settings parametrs
class Settings: public Gtk::Window
{
public:
    Settings(bool *actual);
    virtual ~Settings();

private:
    void drawTable();
    void drawCalendars();

    void saveConfig();///<Save config to file
    virtual void manageCalendarsEvent(int id);
    virtual void removeCalendar(int id);
    virtual void importFromFile(int id);

    bool removeEvent(GdkEventButton* event, int id);
    bool Destroy(GdkEventAny* event);
    void deleteOlderThan(int days);
    void removeOlder();
    bool *actual;
    Gtk::Grid container;
    Gtk::Button remove_button;
    Gtk::Entry days_value;
    Gtk::Label label;
    Gtk::Notebook switching_view;

    Gtk::Grid calendars_view;
    Gtk::Entry calendar_entry[10];
    Gtk::Button calendar_button[10];
    Gtk::Button calendar_remove[10];
    Gtk::Button calendar_button_import[10];
    Gtk::ColorButton calendar_colors[10];

    Gtk::Label name_label;
};
#endif
