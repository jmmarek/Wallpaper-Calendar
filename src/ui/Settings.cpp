#include "Settings.h"

Settings::Settings(bool *actual)
{
    signal_delete_event().connect(sigc::mem_fun(*this, &Settings::Destroy));
    this->actual=actual;
    set_opacity(0.9);
    set_default_size(300, 80);
    set_title("Ustawienia");

    switching_view.append_page(container, "Główne");
    switching_view.append_page(calendars_view, "Kalendarze");

    set_border_width(5);

    remove_button.signal_clicked().connect( sigc::mem_fun(*this,
                                            &Settings::removeOlder) );
    remove_button.set_label("Usuń starsze niż");

    container.set_column_homogeneous(false);
    drawTable();
    drawCalendars();

    add(switching_view);
    show_all();
}

Settings::~Settings()
{
}

bool Settings::Destroy(GdkEventAny* event)
{
    hide();
    return true;
}

void Settings::manageCalendarsEvent(int id)
{
    string name = calendar_entry[id + 1].get_text();
    Gdk::Color color = calendar_colors[id + 1].get_color();
    calendar_entry[id + 1].set_text("");
    if(id == -1) {
        CalendarV new_calendar;
        new_calendar.setName(name);
        new_calendar.setBgColor(color);

        Controler::getInstance()->insertCalendar(new_calendar);
        Controler::getInstance()->calendars.push_back(new_calendar);

        calendars_view.attach(calendar_entry[Controler::getInstance()->calendars.size()], 0, Controler::getInstance()->calendars.size()+1, 1, 1);
        calendars_view.attach(calendar_button[Controler::getInstance()->calendars.size()], 2, Controler::getInstance()->calendars.size()+1, 1, 1);
    } else {
        CalendarV *changed_calendar = &(Controler::getInstance()->calendars[id]);
        changed_calendar->setName(name);
        changed_calendar->setBgColor(color);
        Controler::getInstance()->updateCalendar(*changed_calendar);
        hide();
    }
    calendars_view.hide();
    calendars_view.show();
}

void Settings::removeCalendar(int id)
{
    CalendarV *changed_calendar = &(Controler::getInstance()->calendars[id]);
    Controler::getInstance()->deleteCalendar(*changed_calendar);
    hide();

    calendars_view.hide();
    calendars_view.show();
}

void Settings::importFromFile(int id)
{
    Gtk::FileChooserDialog dialog("Wybierz plik iCalendar",
                                  Gtk::FILE_CHOOSER_ACTION_OPEN);
    dialog.set_transient_for(*this);


    dialog.add_button("_Anuluj", Gtk::RESPONSE_CANCEL);
    dialog.add_button("Wybierz", Gtk::RESPONSE_OK);

    int result = dialog.run();
    switch(result) {
    case(Gtk::RESPONSE_OK): {
        Parser p;
        std::ifstream t(dialog.get_filename());
        std::stringstream buffer;
        buffer << t.rdbuf();
        string buffer_s = buffer.str();
        std::vector<Event> parsed_events = p.getEventsFromString(buffer_s);

        CalendarV *cal = &(Controler::getInstance()->calendars[id]);
for(Event &e : parsed_events) {
            e.setCalendarId(cal->getId());
            Controler::getInstance()->insertEvent(e);
        }

        break;
    }
    case(Gtk::RESPONSE_CANCEL): {
        break;
    }
    default: {
        break;
    }
    }
}

void Settings::drawCalendars()
{
    name_label.set_label("Nazwa");
    calendars_view.attach(name_label, 0, 0, 1, 1);

    for(unsigned int i = 0; i < Controler::getInstance()->calendars.size() + 1;  i++) {
        if(i == 0) calendar_button[i].set_label("Dodaj");
        else {
            calendar_button[i].set_label("Zmień");
            calendar_remove[i].set_label("Usuń");
            calendar_button_import[i].set_label("Importuj");
            calendar_entry[i].set_text(Controler::getInstance()->calendars[i-1].getName());
            calendar_colors[i].set_color(Controler::getInstance()->calendars[i-1].getBgColor().getColor());
            calendar_remove[i].signal_clicked().connect(sigc::bind<unsigned int>( sigc::mem_fun(*this, &Settings::removeCalendar), (i-1)));

            calendars_view.attach(calendar_remove[i], 4, i+1, 1, 1);
            calendar_button_import[i].signal_clicked().connect(sigc::bind<unsigned int>( sigc::mem_fun(*this, &Settings::importFromFile), (i-1)));
            calendars_view.attach(calendar_button_import[i], 5, i+1, 1, 1);
        }

        calendar_button[i].signal_clicked().connect(sigc::bind<unsigned int>( sigc::mem_fun(*this, &Settings::manageCalendarsEvent), (i-1)));

        calendars_view.attach(calendar_entry[i], 0, i+1, 1, 1);
        calendars_view.attach(calendar_colors[i], 2, i+1, 1, 1);
        calendars_view.attach(calendar_button[i], 3, i+1, 1, 1);
    }

    show_all_children();
}

void Settings::drawTable()
{
    container.attach(remove_button, 0, 0, 1, 1);
    container.attach(days_value, 1, 0, 1, 1);
    container.attach(label, 2, 0, 1, 1);

    days_value.set_text("30");
    days_value.set_max_length(3);
    label.set_text("dni");

    show_all_children();
}

void Settings::deleteOlderThan(int days)
{
    Date today;
    days*=1;
    today.setDayAgo(days);// minus 2 miesiące
    Controler::getInstance()->deleteOlderThan(today);
};

void Settings::removeOlder()
{
    //Alert "Remove all events older than (Gtk::Entry.get_text()) days"?

    string days_string_value=days_value.get_text();
    try {
        int since_which_day=stoi(days_string_value);//how many days back to remove to

        Gtk::MessageDialog dialog(*this, "Usunąć wydarzenia starsze, niż "+days_string_value+" dni?",
                                  false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_OK_CANCEL);
        int result = dialog.run();

        if(result==Gtk::RESPONSE_OK)
            deleteOlderThan(since_which_day);//If OK pressed, remove events
    } catch(...) {
        Gtk::MessageDialog dialog(*this, "Napisz poprawną cyfrę?",
                                  false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_OK);
        dialog.run();
    }

};

