#include "Calendar.h"
#include <iostream>

Calendar::Calendar(): bar(675, 20, ""), bar_l(50, 20, ""), bar_r(50, 20, ""), settings_b(20, 20, "")
{

    delta_month=0;//set current month

    //Set to be below - on wallpaper
    set_keep_below(true);
    set_decorated(false);
    set_skip_taskbar_hint(true);

    set_skip_pager_hint(true);
    set_opacity(0.7);
    Gdk::RGBA cool;
    cool.set_rgba(1, 1, 1);
    override_background_color(cool);

    set_title("Wallpaper Calendar");

    actual=true;
    t.setTime();

    //Draw all month's days
    for(int cday=0; cday<5*6; cday++) {
        day[cday].setSize(true);
        day[cday].set_events(Gdk::BUTTON_PRESS_MASK);
        day[cday].signal_button_press_event().connect(sigc::bind<int>( sigc::mem_fun(*this, &Calendar::on_button_clicked), cday));
    }

    drawControls();
    drawMonth();

    Glib::signal_timeout().connect( sigc::mem_fun(*this, &Calendar::time_handler), 1000 );//we call timer to call function, which will check if redraw is neccesary
}

Calendar::~Calendar()
{
    delete settings;
}

void Calendar::updateControls()
{
    bar.setLabel(t.monthName()+" "+std::to_string(t.getYear()));
    bar_l.setLabel("<");
    bar_r.setLabel(">");
    settings_b.setLabel("Ustaw");

    month_control_grid.show_all_children();
    month_control_grid.show();
}

void Calendar::drawControls()
{
    //define parameters of main month container
    month_grid.set_orientation(Gtk::ORIENTATION_VERTICAL);

    ///Display Top bar/buttons
    updateControls();

    month_control_grid.pack_start(bar_l, false, true, 1);
    month_control_grid.pack_start(bar, true, true, 0);
    month_control_grid.pack_start(settings_b, true, true, 0);
    month_control_grid.pack_end(bar_r, false, true, 1);

    settings_b.set_events(Gdk::BUTTON_PRESS_MASK);
    settings_b.signal_button_press_event().connect(sigc::mem_fun(*this, &Calendar::showSettings));

    bar_l.set_events(Gdk::BUTTON_PRESS_MASK);
    bar_l.signal_button_press_event().connect(sigc::bind<int>( sigc::mem_fun(*this, &Calendar::changeMonth), -1));
    bar_r.set_events(Gdk::BUTTON_PRESS_MASK);
    bar_r.signal_button_press_event().connect(sigc::bind<int>( sigc::mem_fun(*this, &Calendar::changeMonth), 1));

    month_grid.pack_start(month_control_grid, false, true, 0);
    month_grid.pack_end(month_days_grid, false, true, 0);
    add(month_grid);
}

void Calendar::drawMonthDays(Date &month_day)
{
    //Add days to month' grid and display
    int first_day=month_day.getFirstDayWeekOfTheMonth();
    bool started_this_month=false;
    bool finish=false;

    int cday=0;
    int end_day=month_day.getLastDayOfTheMonth();
    int r_day=month_day.getLastDayOfWeekEnd()-first_day+1;///to get first day on month calendar (probably the days from last month)

    for(int week=1; week<6; week++) {
        for(int dayweek=0; dayweek<7; dayweek++) {
            if(first_day==dayweek && !started_this_month) {
                started_this_month=true;
                r_day=1;
            }

            month_days_grid.attach(day[cday], dayweek, week+1, 1, 1);
            cday++;

            if(r_day==end_day) {
                finish=true;
                r_day=1;
            } else r_day++;
            if(dayweek==6 && finish) {
                break;
            }
        }

        if(finish && week!=4)break;
    }
}

void Calendar::drawMonth()
{
    month_days_grid.set_row_spacing(3);
    month_days_grid.set_column_spacing(3);
    t.setTime(delta_month);
    setDaysValues();

    //Draw Week day's label
    for(int dayweek=0; dayweek<7; dayweek++) {
        label[dayweek].setSize(false);
        label[dayweek].setDay(0, dayweek, false);
        label[dayweek].onlyLabel();

        month_days_grid.attach(label[dayweek], dayweek, 1, 1, 1);
    }

    //Draw days
    drawMonthDays(t);

    displayChangeMonth();
    show_all_children();
}

void Calendar::displayChangeMonth()
{
    //Set labels
    t.setTime(delta_month);

    setDaysValues();
    //drawMonthDays(t);
    show_all_children();
}

void Calendar::setDaysValues()
{
    int cday=0;
    //Calculate month days
    int today=t.getTodayDayNum();
    int first_day=t.getFirstDayWeekOfTheMonth();

    bool started_this_month=false;
    bool finish=false;

    int end_day=t.getLastDayOfTheMonth();

    int r_day=t.getLastDayOfWeekEnd()-first_day+1;//to get first day on month calendar (probably the dayis from last month)

    int current_month=t.getMonth();

    int current_year=t.getYear();
    Date date;
    for(int week=1; week<6; week++) {
        for(int dayweek=0; dayweek<7; dayweek++) {
            if(first_day==dayweek && !started_this_month) {
                started_this_month=true;
                r_day=1;
            }
            int year=current_year;
            int month=current_month;

            day[cday].unsetToday();
            if(finish) {
                if(current_month==12) {
                    year++;
                    month=0;
                }
                date.setDate(r_day, month+1, year);
                day[cday].setDay(date, r_day, dayweek, false);
            } else if(!started_this_month) {
                if(current_month==1) {
                    year--;
                    month=13;
                }
                date.setDate(r_day, month-1, year);
                day[cday].setDay(date, r_day, dayweek, false);
            } else {
                date.setDate(r_day, current_month, current_year);
                day[cday].setDay(date, r_day, dayweek, started_this_month);
                if(r_day == today)
                    day[cday].setToday();
            }

            day[cday].events.clear();
            day[cday].show();

            cday++;
            if(r_day==end_day && started_this_month) {
                finish=true;
                r_day=1;
            } else r_day++;
            if(dayweek==6 && finish) {
                break;
            } else {
                continue;
            }

            if(finish && week!=4)break;
        }
    }


    //Make request for update events
    Controler::getInstance()->getCalendars();
    Controler::getInstance()->getEventsForEachDay(day);
}

bool Calendar::on_button_clicked(GdkEventButton* event, int day)
{
    Day_view *day_view=new Day_view();
    if(day_view!=nullptr) {
        day_view->setDay(&(this->day[day]), &actual);
        day_view->show();
        day_view->show_all_children();
    }
    return true;
}

bool Calendar::changeMonth(GdkEventButton* event, int step)
{
    //Clear outdated days
    delta_month+=step;
    displayChangeMonth();
    month_days_grid.hide();

    updateControls();

    month_days_grid.show();//redraw table

    return true;
}

gboolean Calendar::time_handler()
{
    //We check if redraw is necessary
    if(!actual) { //check boolean value. If not "actual"...
        actual=true;
        month_days_grid.hide();
        month_days_grid.show();//redraw table
    }
    return true;
}

bool Calendar::showSettings(GdkEventButton* event)
{
    settings = new Settings(&actual);
    settings->show();
    return true;
};
