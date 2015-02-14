#include "Event.h"
#include "Controler.h"

void Event::addParameter(std::string key, std::string value)
{
    if(key == "summary")
        setSummary(value);
    else if(key == "description")
        setDescription(value);
    else if(key == "calendar")
        setCalendarId(atoi(value.c_str()));
    else if(key == "id" && id == -1)
        id = atoi(value.c_str());
    else if(key == "s_date")
        start_date.createFromEpoch(atol(value.c_str()));
    else if(key == "d_date")
        due_date.createFromEpoch(atol(value.c_str()));
    else if(key == "uid")
        setUId(value);
    else if(key == "updated_time")
        updated_time = atol(value.c_str());

}

void Event::setDescription(std::string summary)
{
    this->description = description;
}

void Event::setSummary(std::string summary)
{
    this->summary = summary;
}

const string Event::getSummary() const
{
    return summary;
}

const string Event::getDescription() const
{
    return description;
}

void Event::setStartDate(Date d)
{
    start_date = d;
}

void Event::setDueDate(Date d)
{
    start_date = d;
}

Date Event::getStartDate()
{
    return start_date;
}

Date Event::getDueDate()
{
    return start_date;
}

icaltimetype Event::getStartDate() const
{
    return start_date.createicaltime();
}

void Event::addStartDate(icaltimetype time)
{
    start_date.createFromicaltime(time);
}

void Event::addDueDate(icaltimetype time)
{
    due_date.createFromicaltime(time);
}

void Event::addModDate(icaltimetype time)
{
    Date tmp;
    tmp.createFromicaltime(time);
    updated_time = tmp.getEpoch();
}

void Event::setUId(string uid)
{
    this->uid = uid;
}

const string Event::getUId() const
{
    return uid;
}

void Event::setId(int id)
{
    this->id = id;
}

const int Event::getId() const
{
    return id;
}

const Color Event::getBgColor() const
{
    try {
        return Controler::getInstance()->getCalendar(calendar_id).getBgColor();
    } catch(...) {
        cout<<"Bad point"<<endl;
        return Gdk::Color();
    }
}

int Event::getCalendarId() const
{
    return calendar_id;
}

void Event::setCalendarId(int id)
{
    calendar_id = id;
}

bool Event::isUpToDate(const Event &e)
{
    return updated_time >= e.updated_time;
}
