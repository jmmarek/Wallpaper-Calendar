bin_PROGRAMS=wallpaper-calendar
AM_CXXFLAGS = -std=c++11 -DPROGRAMNAME_LOCALEDIR=\"${PROGRAMNAME_LOCALEDIR}\"
LIBS = $(GTKMM_LIBS) $(SQLITE_LIBS) $(ICAL_LIBS)
INCLUDES = $(GTKMM_CFLAGS) $(SQLITE_CFLAGS) $(ICAL_CFLAGS)
wallpaper_calendar_SOURCES=main.cpp CalendarV.cpp Controler.cpp Event.cpp Parser.cpp Date.cpp DB.cpp ui/Calendar.cpp ui/Day.cpp ui/Image.cpp ui/Rect.cpp ui/Day_view.cpp ui/Add_event.cpp ui/Color_label.cpp ui/Settings.cpp

