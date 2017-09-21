/*
 * fortuner
 * Copyright (C) 2013 Juhani Numminen <juhaninumminen0@gmail.com>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "aboutdialog.h"
#include "config.h"
#include "gettext.h"

const Glib::ustring gpl3_license =
        "This program is free software; you can redistribute it and/or modify\n"
        "it under the terms of the GNU General Public License as published by\n"
        "the Free Software Foundation; either version 3 of the License, or\n"
        "(at your option) any later version.\n"
        "\n"
        "This program is distributed in the hope that it will be useful,\n"
        "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
        "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
        "GNU General Public License for more details.\n"
        "\n"
        "You should have received a copy of the GNU General Public License\n"
        "along with this program.  If not, see <http://www.gnu.org/licenses/>.";


FortunerAboutDialog::FortunerAboutDialog ()
{
    set_program_name (_("Fortuner"));
    set_version (VERSION_STRING);
    set_copyright (_("Copyright (C) 2012, 2013 Juhani Numminen"));
    set_comments (_("Shows fortunes as notifications."));
    set_license (gpl3_license);
    set_website ("https://github.com/jnumm/fortuner/wiki");
    set_logo_icon_name ("fortuner");
    set_wrap_license (false);
    set_icon_name ("fortuner");

    signal_response ().connect (sigc::mem_fun (*this,
            &FortunerAboutDialog::on_response));
}

void FortunerAboutDialog::on_response (int)
{
    hide ();
}
