#include "Day.h"
#include <iostream>
#define BLOCK_SIZE 130
#define BLOCK_H_SIZE 20

Day::Day()
{
    signal_draw().connect(sigc::mem_fun(*this, &Day::on_draw), false);
    today=false;
    label=false;
    update=false;
}

Day::~Day()
{
}

bool Day::draw_text(const Cairo::RefPtr<Cairo::Context>& cr, Glib::RefPtr<Pango::Layout> layout)
{
    Pango::FontDescription font;
    font.set_family("Monospace");
    font.set_weight(Pango::WEIGHT_BOLD);

    layout->set_font_description(font);
    layout->update_from_cairo_context(cr);

    return 0;
}

bool Day::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    if(!label) {
        //Draw background (the nice block)
        if(today)
            cr->set_source_rgb(0.5, 0.4, 0.1);
        else if(!this_month)
            cr->set_source_rgb(0.8, 0.8, 0.8);
        else if(day_week==0 || day_week==6)
            cr->set_source_rgb(0.2, 0.3, 0.1);
        else
            cr->set_source_rgb(0.2, 0.6, 0.1);

        cr->rectangle(0, 0, BLOCK_SIZE, BLOCK_SIZE);
        cr->set_line_join(Cairo::LINE_JOIN_BEVEL);
        cr->fill();
        cr->save();

        //Print day number
        cr->set_source_rgb(1, 1, 1);
        cr->scale(1.7, 1.7);

        string _str = std::to_string(day_number);
        int text_width, text_height;
        Glib::RefPtr<Pango::Layout> lyo=create_pango_layout(_str);
        draw_text(cr, lyo);

        cr->move_to(5, 2);

        lyo->get_pixel_size(text_width, text_height);
        lyo->show_in_cairo_context(cr);
        cr->save();

        text_width*=2;

        text_height*=2;//5/2;

        text_height+=2;

        cr->scale(0.5, 0.5);
        int w=BLOCK_SIZE;

        for(unsigned int i=0; i<events.size(); i++) {
            Glib::RefPtr<Pango::Layout> lyo1=create_pango_layout(events[i].getSummary().c_str());

            draw_text(cr, lyo1);
            text_height+=2;
            int text_width1, text_height1;
            lyo1->get_pixel_size(text_width1, text_height1);
            cr->set_source_rgb(events[i].getBgColor().getColor().get_red_p(), events[i].getBgColor().getColor().get_green_p(), events[i].getBgColor().getColor().get_blue_p());

            if(!today)
                cr->rectangle(2, text_height, w-2, text_height1);
            else
                cr->rectangle(5, text_height, w-4, text_height1);

            cr->fill();
            cr->save();
            cr->move_to(5, text_height);
            cr->set_source_rgb(events[i].getBgColor().getRevertColor().get_red_p(), events[i].getBgColor().getRevertColor().get_green_p(), events[i].getBgColor().getRevertColor().get_blue_p());
            lyo1->show_in_cairo_context(cr);
            text_height+=text_height1;
        }
    } else {
        string day_of_week;
        switch (day_week) {
        case 1:
            day_of_week=_("Mon");
            break;
        case 2:
            day_of_week=_("Tue");
            break;
        case 3:
            day_of_week=_("Wed");
            break;
        case 4:
            day_of_week=_("Thu");
            break;
        case 5:
            day_of_week=_("Fri");
            break;
        case 6:
            day_of_week=_("Sat");
            break;
        case 0:
            day_of_week=_("Sun");
            break;
        }
        cr->set_source_rgb(0.3, 0.4, 0.3);
        cr->rectangle(0, 0, BLOCK_SIZE, BLOCK_H_SIZE);
        cr->fill();
        cr->save();

        cr->scale(1.5, 1.5);
        cr->set_source_rgb(0.1, 0.1, 0.1);

        Glib::RefPtr<Pango::Layout> layout = create_pango_layout(day_of_week);
        draw_text(cr, layout);

        cr->move_to(5, -1);

        layout->show_in_cairo_context(cr);
    }
    return true;
}

void Day::setSize(bool t)
{
    if(t) {
        set_size_request(BLOCK_SIZE, BLOCK_SIZE);
    } else {
        set_size_request(BLOCK_SIZE, BLOCK_H_SIZE);
    }

}
