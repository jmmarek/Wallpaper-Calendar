#pragma once
#include <sys/param.h>
#include <gtkmm.h>
#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <sstream>

#include "Settings.h"
#include "Image.h"
#include "Rect.h"
#include "Day_view.h"
#include "Settings.h"
#include "Day.h"
#include "../Date.h"
#include "../Controler.h"

using namespace std;

///The main Class of the application. There is defined layout of our calendar and functions, which we need to use
class Calendar: public Gtk::Window
{
public:
    Calendar();///<Constructor. The parameter we'll need to know path of program file and loading graphics
    virtual ~Calendar();
    void drawMonth();///<Draws ui for month and calls drawMonthDays

    //Day_view *day_view;///<The pointer exists to create Day View window which is defined in day_view.h
    static bool smaller_images;///<If the pictures are to big, we can set there true. This is static, for easier acces by other class

private:
    //Methods:
    void updateControls();///<Updates buttons display
    void drawMonthDays(Date &month_day);///<Draw given month days
    void displayChangeMonth();///<Redraw content witch change of month.
    gboolean time_handler();///<We check if redraw is necessary

    bool on_button_clicked(GdkEventButton* event, int day);
    bool showSettings(GdkEventButton* event);///<The function shows settings window which is defined in settings.h file
    bool changeMonth(GdkEventButton* event, int step);///<Changes month view
    void setDaysValues();///<Updates days content
    void drawControls();///<Draws buttons

    //Objects
    Gtk::Grid month_days_grid;///<Container of Calendar days. In the container there are for example days to choose
    Gtk::Box month_control_grid;///<Contains controls for month view
    Gtk::Box month_grid;///<Main container for month view
    Day day[35];///<The table of days graphic representation. While Month is change, there are cleaned and redrawed, but object are the same
    Day label[7];///<The labels inages of day of week
    Date today_date;///<Object contains current date

    bool actual;///<If changes was made, then false
    Date t;///<Time object. Used for getting time
    Rect settings_b;///<The button for settings
    Rect bar;///<The main bar which name of current month
    Rect bar_l;///<Left image with name of last month
    Rect bar_r;///<Right image with name of next month

    int delta_month;///<Months from current month. (If we are moving in future on in past on our Calendar). If 0, then current month else month + delta_month

    Settings *settings = nullptr;///<Settings window
};
