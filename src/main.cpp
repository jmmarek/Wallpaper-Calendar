#include <gtkmm.h>
#include "ui/Calendar.h"
#include "Controler.h"

int main(int argc, char* argv[])
{
    Gtk::Main kit(argc, argv);

    Controler::setInstance(argv[0]);

    Calendar calendar;

    kit.run(calendar);

    Controler::deleteInstance();
}
