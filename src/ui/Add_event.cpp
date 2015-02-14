#include "Add_event.h"
#include <iostream>

Add_event::Add_event(Day *day, Day_view *parent)
{
    this->parent=parent;

    this->day=day;

    set_opacity(0.9);
    set_default_size(200, 100);
    set_title("Dodaj nowe wydarzenie");

    this->container = new Gtk::Grid;
    set_border_width(5);

    e = new Gtk::Entry;
    e->set_valign(Gtk::ALIGN_START);

    this->container->set_column_homogeneous(false);
    o_button.set_label("Dodaj");
    o_button.signal_clicked().connect(sigc::mem_fun(*this, &Add_event::addEvent));

    addCalendarCombo();

    draw();
}

Add_event::Add_event(Day *day, Day_view *parent, int event)
{
    this->parent=parent;
    event_id=event;
    this->day=day;

    set_opacity(0.9);
    set_default_size(200, 100);
    set_title("Edytuj wydarzenie");

    this->container = new Gtk::Grid;
    set_border_width(5);

    e = new Gtk::Entry;
    e->set_text(day->events[event].getSummary());
    e->set_valign(Gtk::ALIGN_START);

    this->container->set_column_homogeneous(false);
    o_button.set_label("Zatwierdź zmianę");
    o_button.signal_clicked().connect(sigc::mem_fun(*this, &Add_event::editEvent));

    addCalendarCombo();

    draw();
}

void Add_event::addCalendarCombo()
{
    m_refTreeModel = Gtk::ListStore::create(m_Columns);
    calendar_for_event.set_model(m_refTreeModel);
    Gtk::TreeModel::Row row;
    int cal_id = 0;
    for(CalendarV &c : Controler::getInstance()->calendars) {
        row = *(m_refTreeModel->append());
        row[m_Columns.m_col_id] = ++cal_id;
        row[m_Columns.m_col_name] = c.getName();
        calendar_for_event.set_active(row);
    }

    calendar_for_event.pack_start(m_Columns.m_col_id);
    calendar_for_event.pack_start(m_Columns.m_col_name);
}

Add_event::~Add_event()
{
    delete e;
}

void Add_event::getCal()
{
    Gtk::TreeModel::iterator iter = calendar_for_event.get_active();
    if(iter) {
        Gtk::TreeModel::Row row = *iter;
        if(row) {
            int id = row[m_Columns.m_col_id];
            Glib::ustring name = row[m_Columns.m_col_name];
            sel_calendar = id;
        }
    }
}

void Add_event::addEvent()
{
    getCal();
    parent->attachBy();
}

void Add_event::editEvent()
{
    getCal();
    parent->changeBy();
}

void Add_event::draw()
{
    this->container->attach(*e, 0, 0, 1, 1);
    this->container->attach(calendar_for_event, 1, 0, 1, 1);
    this->container->attach(o_button, 1, 2, 1, 1);
    add(*container);
    show_all_children();
}
