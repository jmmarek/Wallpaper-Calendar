#include <string>
#include <sqlite3.h>
#include <vector>
#include <map>
#include "Event.h"
#include "CalendarV.h"

using namespace std;

#ifndef DB_H
#define DB_H

//Class which manages DataBase for Events
class DB
{
public:
    DB(std::string file_path);
    ~DB();
    std::vector<Event> getEventsFromDB(std::string additional_sql = "");///<Get vector of events from database \param additional_sql SQL expression like 'WHERE summary = "my summary"'
    std::vector<CalendarV> getCalendarsFromDB(std::string where = "");

    //Handling Events
    void addEventToDB(Event &e);
    void updateEventInDB(const Event &e);
    void createTable();
    void deleteEventFromDB(const Event &e);
    void deleteEventsFromDB(string where);

    //Handling Calendars
    void addCalendarToDB(CalendarV &calendar);
    void updateCalendarInDB(const CalendarV &calendar);
    void deleteCalendarFromDB(const CalendarV &calendar);
private:
    sqlite3 *db;
    typedef int (*callback)(void *data, int argc, char **argv, char **azColName);
    void execute(string SQLstatement, callback function = NULL, void *data = NULL);
};

#endif
