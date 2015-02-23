#include <gtkmm.h>
#include "ui/Calendar.h"
#include "Controler.h"

int main(int argc, char* argv[])
{
    // Initialize translation
    bindtextdomain(GETTEXT_PACKAGE, PROGRAMNAME_LOCALEDIR);
    bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
    textdomain(GETTEXT_PACKAGE);

    // Setup gtkmm
    Gtk::Main kit(argc, argv);

    Controler::setInstance();

    Calendar calendar;

    // Draw calendars window
    kit.run(calendar);

    Controler::deleteInstance();
}
