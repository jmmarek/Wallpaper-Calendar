#include "DB.h"

DB::DB(std::string file_path)
{
    int rc = sqlite3_open(file_path.c_str(), &db);
    if( rc ) {
        throw string("Can't open database: %s\n");
    } else {
        createTable();
    }
}

DB::~DB()
{
    sqlite3_close(db);
}

void DB::createTable()
{
    try {
        execute("CREATE TABLE EVENTS("  \
                "id             INTEGER PRIMARY KEY AUTOINCREMENT," \
                "uid            CHAR(50)," \
                "calendar       INT     NOT NULL," \
                "summary        CHAR(50)," \
                "s_date         REAL, "\
                "d_date         REAL, "\
                "updated_time   REAL, "\
                "description    CHAR(50)" \
                " );");

        execute("CREATE TABLE CALENDARS("  \
                "id             INTEGER PRIMARY KEY AUTOINCREMENT," \
                "name           CHAR(50)," \
                "color          CHAR(50)," \
                " );");
        CalendarV calendarV;
        calendarV.setName("Domyślny");
        addCalendarToDB(calendarV);
    } catch(...) {

    }
}

void DB::execute(std::string statement, callback function, void *data)
{
    char *zErrMsg;
    int rc = sqlite3_exec(db, statement.c_str(), function, data, &zErrMsg);
    if( rc != SQLITE_OK ) {
        sqlite3_free(zErrMsg);
        throw string("DB already exists");
    }
}

int recordsCallback(void *data, int argc, char **argv, char **azColName)
{
    int i;
    std::vector<std::map<std::string, std::string>> *list = (std::vector<std::map<std::string, std::string>>*)data;
    for(i=0; i<argc; i++) {
        std::map<std::string, std::string> map_;
        map_[azColName[i]] = argv[i];
        list->push_back(map_);
    }
    printf("\n");
    return 0;
}

int eventsCallback(void *data, int argc, char **argv, char **azColName)
{
    int i;
    std::vector<Event> *list = (std::vector<Event>*)data;
    Event e;
    for(i=0; i<argc; i++)
        e.addParameter(azColName[i], argv[i]);
    list->push_back(e);
    return 0;
}

std::vector<Event> DB::getEventsFromDB(std::string where)
{
    std::vector<Event> events;
    execute("SELECT * FROM EVENTS "+where, eventsCallback, &events);
    return events;
}

int callbackCreate(void *data, int argc, char **argv, char **azColName)
{
    string *id = (string*)data;
    *id = argv[0];
    return 0;
}

void DB::addEventToDB(Event &e)
{
    string id;
    execute("INSERT INTO EVENTS (uid, calendar, summary, s_date, d_date, updated_time, description) "  \
            "VALUES ('"+e.getUId()+"', '"+std::to_string(e.getCalendarId())+"', '"+e.getSummary()+"', "+std::to_string(e.getStartDate().getEpoch())+", "+std::to_string(e.getDueDate().getEpoch())+", "+to_string(time(NULL))+", '"+e.getDescription()+"' );", callbackCreate, (void*)&id);

    execute("SELECT id from EVENTS ORDER BY id DESC LIMIT 1;", callbackCreate, (void*)&id);
    e.setId(atoi(id.c_str()));
}

void DB::updateEventInDB(const Event &e)
{
    execute("UPDATE EVENTS set calendar = '"+std::to_string(e.getCalendarId())+"',summary = '"+e.getSummary()+"', updated_time = "+to_string(time(NULL))+" where id = "+to_string(e.getId())+";");
}

void DB::deleteEventsFromDB(string where)
{
    execute("DELETE from EVENTS "+where+";");
}

void DB::deleteEventFromDB(const Event &e)
{
    execute("DELETE from EVENTS where id = "+to_string(e.getId())+";");
}

void DB::addCalendarToDB(CalendarV &calendar)
{
    string id;
    execute("INSERT INTO CALENDARS (name, color) "  \
            "VALUES ('"+calendar.getName()+"', '"+calendar.getBgColor().getColor().to_string()+"' );", callbackCreate, (void*)&id);

    execute("SELECT id from CALENDARS ORDER BY id DESC LIMIT 1;", callbackCreate, (void*)&id);
    calendar.setId(atoi(id.c_str()));
}

void DB::updateCalendarInDB(const CalendarV &calendar)
{
    execute("UPDATE CALENDARS set name = '"+calendar.getName()+"', color = '"+calendar.getBgColor().getColor().to_string()+"' where id = "+to_string(calendar.getId())+";");
}

void DB::deleteCalendarFromDB(const CalendarV &calendar)
{
    execute("DELETE from CALENDARS where id = "+to_string(calendar.getId())+";");
}

int calendarsCallback(void *data, int argc, char **argv, char **azColName)
{
    int i;
    std::vector<CalendarV> *list = (std::vector<CalendarV>*)data;
    CalendarV e;
    for(i=0; i<argc; i++)
        e.addParameter(azColName[i], argv[i]);
    list->push_back(e);
    return 0;
}

std::vector<CalendarV> DB::getCalendarsFromDB(std::string where)
{
    std::vector<CalendarV> calendars;
    execute("SELECT * FROM CALENDARS "+where, calendarsCallback, &calendars);
    return calendars;
}
