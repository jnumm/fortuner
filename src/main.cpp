/*
 * fortuner
 * Copyright (C) 2012, 2013 Juhani Numminen <juhaninumminen0@gmail.com>
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

#include <iostream>
#include <cstdlib>
#include <cstring>

#include <glibmm/miscutils.h>
#include <gtkmm/main.h>
#include <gtkmm/messagedialog.h>
#include <libnotify/notify.h>

#include "config.h"
#include "fortuner.h"
#include "gettext.h"
#include "settings.h"
#include "statusicon.h"

void display_error_dialog (const Glib::ustring& message)
{
    Gtk::MessageDialog dialog (message, false, Gtk::MESSAGE_ERROR);
    dialog.run ();
}

void print_help ()
{
    std::cout<<_(
            "Usage: fortuner [OPTION...]\n"
            "\n"
            "  -a                         choose from also offensive fortunes\n"
            "  -c, --config FILE          use a specific configuration file\n"
            "  -h, --help                 show this help message\n"
            "  -n, --no-icon              don't display status icon\n"
            "  -v, --version              print program version\n");
}

int main (int argc, char *argv[])
{
    setlocale (LC_ALL, "");
    bindtextdomain ("fortuner", LOCALEDIR);
    textdomain ("fortuner");
    
    bool no_icon_mode = false;
    bool offensive = false;
    std::string settings_file = Glib::get_user_config_dir () +
            "/fortuner/fortuner.conf";

    // Parse arguments
    if (argc >= 1)
    {
    for (int i = 1; i < argc; i++)
        {
            if (strcmp (argv [i], "--help") == 0 ||
					strcmp (argv [i], "-h") == 0)
            {
                print_help ();
                return 0;
            }
            else if (strcmp (argv [i], "--version") == 0 ||
					strcmp (argv [i], "-v") == 0)
            {
                std::cout << PROJECT_NAME " " VERSION_STRING " ";
                printf (_("(compiled on %s)\n"), __DATE__);
                return 0;
            }
            else if (strcmp (argv[i], "--config") == 0 ||
					strcmp (argv[i], "-c") == 0)
            {
                settings_file = argv[i+1];
                i++;
            }
            else if (strcmp (argv[i], "--no-icon") == 0 ||
                    strcmp (argv[i], "-n") == 0)
            {
                no_icon_mode = true;
            }
            else if (strcmp (argv[i], "-a") == 0)
            {
				offensive = true;
			}
            else
            {
                printf (_("Invalid option '%s'.\n"), argv [i]);
                return 1;
            }
        }
    }

    Settings settings (settings_file);

    if (offensive)
    {
        settings.setOffensive (true);
    }

    // Initialize notification library
    if (!notify_init (PROJECT_NAME)) {
        std::cerr << _("Could not initialize the notification library.\n");
        return 1;
    }

    Fortuner fortuner (settings);

    if (!no_icon_mode)
    {
        Gtk::Main kit (argc, argv);
        FortunerStatusIcon icon (fortuner);
        Gtk::Main::run ();

        // Close notifications if settings say so.
        if (settings.getCloseNotificationsOnQuit ())
        {
            fortuner.close_notifications ();
        }
    }
    else
    {
        // No icon mode, so let's just send one fortune notification.
        fortuner.send_fortune ();
    }

    notify_uninit ();

    return 0;
}
