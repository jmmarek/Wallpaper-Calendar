#include "Parser.h"

Parser::Parser()
{
    parser = icalparser_new();
}

Parser::~Parser()
{
    icalparser_free(parser);
}

Event Parser::getEventFromString(std::string stream)
{
    icalcomponent *c;
    Event event;

    std::istringstream iss(stream);

    std::string line;
    while (std::getline(iss, line)) {
        c = icalparser_add_line(parser,&(line[0]));

        if (c != 0) {
            event.setSummary(icalcomponent_get_summary(c));
            event.addStartDate(icalcomponent_get_dtstart(c));
            event.addDueDate(icalcomponent_get_dtend(c));
            event.setUId(icalcomponent_get_uid(c));
            cout<<icalcomponent_get_uid(c)<<endl;
            icalcomponent_free(c);
        }
    }

    icalparser_free(parser);

    return event;
}

std::vector<Event> Parser::getEventsFromString(std::string stream)
{
    icalcomponent *c;
    std::vector<Event> events;

    std::istringstream iss(stream);

    std::string line;

    c = icalparser_add_line(parser,&(line[0]));
    while (std::getline(iss, line)) {
        c = icalparser_add_line(parser,&(line[0]));
    }

    icalcomponent *cx = icalcomponent_get_first_component(c, ICAL_VEVENT_COMPONENT);

    while(cx != NULL ) {
        Event event;
        event.setSummary(icalcomponent_get_summary(cx));
        event.addStartDate(icalcomponent_get_dtstart(cx));
        event.addDueDate(icalcomponent_get_dtend(cx));

        events.push_back(event);

        cx = icalcomponent_get_next_component(c, ICAL_VEVENT_COMPONENT);
    }
    icalcomponent_free(cx);

    return events;
}

std::string Parser::getStringFromEvent(const Event &e)
{
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    icalcomponent_set_summary(component, e.getSummary().c_str());
    icalcomponent_set_dtstart(component, e.getStartDate());
    icalcomponent_set_dtend(component, e.getStartDate());

    return std::string(icalcomponent_as_ical_string(component));
}

