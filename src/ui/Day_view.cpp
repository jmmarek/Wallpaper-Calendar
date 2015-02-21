#include "Day_view.h"
#include <iostream>

Day_view::Day_view()
{
    signal_delete_event().connect(sigc::mem_fun(*this, &Day_view::Destroy));
    add_event=nullptr;
    set_opacity(0.9);
    set_default_size(200, 400);
    set_title("");

    container = new Gtk::Grid;
    set_border_width(5);
    add_button.signal_clicked().connect(sigc::mem_fun(*this, &Day_view::addEvent));

    add_button.set_label(_("Add"));
    container->set_column_homogeneous(false);

}

Day_view::~Day_view()
{
    delete add_event;
}

void Day_view::drawTable()
{
    container->attach(add_button, 0, 0, 2, 1);

    for(unsigned int i=0; i<events->size(); i++) {
        ColorLabel *d = new ColorLabel(0, 0, events->at(i).getSummary(), events->at(i).getBgColor().getRevertColor(), events->at(i).getBgColor().getColor());
        ColorLabel *ddel = new ColorLabel(0, 0, _("Delete"));

        d->set_events(Gdk::BUTTON_PRESS_MASK);
        d->signal_button_press_event().connect(sigc::bind<int>( sigc::mem_fun(*this, &Day_view::editEvent), i));

        ddel->set_events(Gdk::BUTTON_PRESS_MASK);
        ddel->signal_button_press_event().connect(sigc::bind<int>( sigc::mem_fun(*this, &Day_view::removeEvent), i));

        widgets.push_back(d);
        widgets.push_back(ddel);

        int id = i*2;
        container->attach(*(widgets[id]), 0, i+1, 1, 1);
        container->attach(*(widgets[id+1]), 1, i+1, 1, 1);
    }

    add(*container);
    show_all_children();
}

bool Day_view::removeEvent(GdkEventButton* event, unsigned int id)
{
    for(unsigned int i=0; i<events->size(); i++) { //remove graphic content
        if(widgets[2*i]!=nullptr && widgets[2*i+1]!=nullptr) {
            container->remove(*widgets[2*i]);
            container->remove(*widgets[2*i+1]);

            Event *edited_event = &events->at(id);
            Controler::getInstance()->deleteEvent(*edited_event);

            delete widgets[2*i];
            delete widgets[2*i+1];
            widgets[2*i]=nullptr;
            widgets[2*i+1]=nullptr;

        }
    }


    Controler::getInstance()->deleteEvent(events->at(id));

    if(widgets.size()>id*2) {
        std::vector<Event>::iterator it = events->begin()+id;
        events->erase(it);
    }

    for(unsigned int i=0; i<(events->size()+1); i++) {
        widgets.pop_back();
        widgets.pop_back();
    }

    redrawTable();
    *actual=false;///set calendar to refresh
    return true;
}

bool Day_view::Destroy(GdkEventAny* event)
{
    hide();
    for(int i=widgets.size()-1; i>=0; i--) {
        delete (widgets[i]);
        widgets.pop_back();
    }
    delete container;

    return true;
}

void Day_view::redrawTable()
{
    drawTable();
}

void Day_view::setDay(Day *d, bool *actual)
{
    this->actual=actual;
    set_title(d->getDate().printString());
    day=d;
    events=&(d->events);

    drawTable();
    show_all_children();

}

void Day_view::attachBy()
{
    if(add_event!=nullptr) {

        if(add_event->e->get_text()!="") {
            Event *new_event = new Event();

            setEventParameters(new_event);
            ColorLabel *ddel = new ColorLabel(0, 0, _("Delete"));

            ddel->set_size_request(50, 20);

            ddel->set_events(Gdk::BUTTON_PRESS_MASK);
            ddel->signal_button_press_event().connect(sigc::bind<int>( sigc::mem_fun(*this, &Day_view::removeEvent), events->size()));

            widgets.push_back(ddel);

            container->attach(*(widgets[widgets.size()-2]), 0, widgets.size(), 1, 1);
            container->attach(*(widgets[widgets.size()-1]), 1, widgets.size(), 1, 1);
            events->push_back(*new_event);

            add_event->hide();
            delete add_event;
            *actual=false;
            show_all_children();
        }
    }
}

void Day_view::setEventParameters(Event *event, int event_id)
{
    int selected_calendar = add_event->sel_calendar;
    event->setSummary(add_event->e->get_text());
    event->setCalendarId(selected_calendar);
    event->setStartDate(day->getDate());

    Color color = Controler::getInstance()->getCalendar(selected_calendar).getBgColor();
    ///Redisplay element with id = event_id
    ColorLabel *d = new ColorLabel(220, 0, event->getSummary(), color.getRevertColor(), color.getColor());
    d->set_size_request(50, 20);
    d->set_events(Gdk::BUTTON_PRESS_MASK);

    if(event_id > -1) {
        Controler::getInstance()->updateEvent(*event);
        d->signal_button_press_event().connect(sigc::bind<int>( sigc::mem_fun(*this, &Day_view::editEvent), event_id));
        container->remove(*widgets[2*event_id]);
        delete widgets[2*event_id];
        widgets[2*event_id]=d;
        container->attach(*(widgets[2*event_id]), 0, event_id+1, 1, 1);
    } else {
        d->signal_button_press_event().connect(sigc::bind<int>( sigc::mem_fun(*this, &Day_view::editEvent), events->size()-1));
        Controler::getInstance()->insertEvent(*event);
        widgets.push_back(d);
    }
}

void Day_view::changeBy()
{
    if(add_event!=nullptr) {
        if(add_event->e->get_text()!="") {
            int id_to_edit=add_event->event_id;
            Event *edited_event = &events->at(id_to_edit);
            setEventParameters(edited_event, id_to_edit);

            add_event->hide();
            delete add_event;

            *actual=false;
            show_all_children();
        }
    }
}

void Day_view::addEvent()
{
    add_event = new Add_event(day, this);
    add_event->show();
}

bool Day_view::editEvent(GdkEventButton* event, int id)
{
    add_event = new Add_event(day, this, id);
    add_event->show();
    return true;
}
