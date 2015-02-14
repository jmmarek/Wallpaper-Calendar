#include "CalendarV.h"

void CalendarV::addParameter(std::string key, std::string value)
{
    if(key == "name")
        setName(value);
    else if(key == "color")
        setBgColor(Gdk::Color(value));
    else if(key == "id" && id == -1)
        id = atoi(value.c_str());
}

void CalendarV::setId(int id)
{
    this->id = id;
}

int CalendarV::getId() const
{
    return id;
}

void CalendarV::setBgColor(Gdk::Color color)
{
    bg_color = color;
}

const Color CalendarV::getBgColor() const
{
    return bg_color;
}

string CalendarV::getName() const
{
    return name;
}

void CalendarV::setName(string name)
{
    this->name = name;
}
