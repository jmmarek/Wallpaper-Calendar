#include <iostream>
#include <string>
#include <libical/ical.h>
#include <boost/date_time.hpp>
#include "ui/Color.h"
#include "Date.h"

#ifndef EVENT_H
#define EVENT_H

using namespace std;

///Represents Event. It allows to easy moving informations about event through DB, Servers etc.
class Event
{
public:
    Event() {
        id = -1;
        calendar_id = -1;
        uid = "";
    };
    Event(const Event &e) {
        id = e.id;
        calendar_id = e.calendar_id;
        uid = e.uid;
        summary = e.summary;
        description = e.description;
        start_date = e.start_date;
        due_date = e.due_date;
    };

    void addParameter(std::string key, std::string value);///<Adds parameters when parsing from DB
    void setDescription(std::string summary);
    void setSummary(std::string summary);
    const string getSummary() const;
    const string getDescription() const;
    int getCalendarId() const;///<Gets id of Calendar in which this event exits
    void setCalendarId(int id);///<Set id of Calendar in which exists

    void setStartDate(Date d);
    void setDueDate(Date d);
    Date getStartDate();
    Date getDueDate();
    icaltimetype getStartDate() const;

    void addModDate(icaltimetype time);
    void addStartDate(icaltimetype time);///<Adds start date when parsing from iCal
    void addDueDate(icaltimetype time);///<Adds start date when parsing from iCal

    void print();
    void setId(int id);
    const int getId() const;

    void setUId(string id);///<Sets UID to identify events coming from server
    const string getUId() const;///<Gets unique UID to synchronize events

    const Color getBgColor() const;///<Gets background for Calendar group

    bool isUpToDate(const Event &e);///< Checks whether this Event is up to date
private:
    int id; ///< Event id in database
    string uid; ///<For sync only
    int calendar_id; ///<Id of calendar that event belongs to
    string summary; ///<Summary of event
    string description; ///<Description of event
    Date start_date;
    Date due_date;

    long long updated_time;///<Time of last modification on server or database
};

#endif
