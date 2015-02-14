#include <libical/ical.h>
#include "Event.h"
#include <string>
#include <sstream>
#include <vector>

#ifndef PARSER_H
#define PARSER_H

using namespace std;

class Parser
{
public:
    Parser();
    ~Parser();
    Event getEventFromString(string stream);///< Gets Event class from iCalendar string
    std::vector<Event> getEventsFromString(string stream);///<Gets Events vector from iCalendar string

    std::string getStringFromEvent(const Event &e);///<Makes string from event
private:
    icalparser *parser;
};

#endif
