#include "Controler.h"

Controler* Controler::controler = nullptr;

Controler* Controler::getInstance(std::string path)
{
    if(controler != nullptr)
        return controler;

    controler = new Controler(path);
    return controler;
}

void Controler::deleteInstance()
{
    delete controler;
}

void Controler::setInstance()
{
    // Create resource directory
    string path = Glib::get_user_data_dir();
    path += "/wallpaper-calendar/";
    Glib::RefPtr< Gio::File > directory = Gio::File::create_for_path(path);
    try {
        directory->make_directory_with_parents();
    } catch(Gio::Error e) {}

    if(controler != nullptr)
        return;

    controler = new Controler(path);
}

Controler::Controler(std::string path)
{
    db = new DB(path+"data.db");
}

Controler::~Controler()
{
    delete db;
}

void Controler::getEventsForEachDay(Day *day)
{
    int first_day_epoch = day->getDate().getEpoch();
    int last_day_epoch = day[34].getDate().getEpoch();
    std::vector<Event> events = db->getEventsFromDB("WHERE (s_date >= "+std::to_string(first_day_epoch)+" AND s_date <= "+std::to_string(last_day_epoch)+") OR (d_date >= "+std::to_string(first_day_epoch)+" AND d_date >= "+std::to_string(last_day_epoch)+") ORDER BY s_date");

    int day_numer = 0;
for(Event &e : events) {
        while(e.getStartDate() > day[day_numer].getDate()) {
            day_numer++;
        }
        if(day_numer > 34)
            break;

        day[day_numer].events.push_back(e);

    }
}

void Controler::updateEvent(const Event &e)
{
    db->updateEventInDB(e);
}

void Controler::insertEvent(Event &e, bool sync)
{
    db->addEventToDB(e);
}

void Controler::deleteEvent(Event &e)
{
    db->deleteEventFromDB(e);
}

void Controler::deleteOlderThan(Date date)
{
    db->deleteEventsFromDB("WHERE d_date < "+std::to_string(date.getEpoch()));
}

void Controler::insertCalendar(CalendarV &calendar)
{
    db->addCalendarToDB(calendar);
}

void Controler::updateCalendar(const CalendarV &calendar)
{
    db->updateCalendarInDB(calendar);
}

void Controler::deleteCalendar(CalendarV &calendar)
{
    db->deleteCalendarFromDB(calendar);
}

void Controler::getCalendars()
{
    calendars = db->getCalendarsFromDB();
}

CalendarV Controler::getCalendar(int id)
{
for(CalendarV &c : calendars)
        if(c.getId() == id) {
            return c;
        }
    throw("Calendar doesn't exist");
}
