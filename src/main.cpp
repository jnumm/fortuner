/*
 * fortuner
 * Copyright (C) 2012 Juhani Numminen <juhaninumminen0@gmail.com>
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
#include <vector>
#include <libnotify/notify.h>

#include "config.h"
#include "gtk_ui.h"
#include "main.h"
#include "settings.h"

// Static variable makes it possible to use this anywhere in the program
Settings settings;

// A vector to hold the notifications.
std::vector<NotifyNotification> notifications;

// Get a fortune and return it as std::string.
std::string get_fortune ()
{
    FILE *fortune_pipe;
    
    std::string fortune_cmdline = "fortune -s";
    std::string fortune_string;
    char buffer[100];
    int exit_status;
    
    if (settings.getOffensive () == true)
    {
        /* From the fortune(6) man page:
         * -a  Choose  from all lists of maxims, both offensive and not.
         */
        fortune_cmdline += " -a";
    }

    fortune_pipe = popen (fortune_cmdline.c_str (), "r");
    
    // Check for NULL pipe
    if (fortune_pipe == NULL)
    {
        std::cout<<"Failed to run 'fortune'\n";
    }

    // Get data
    while (fgets (buffer, sizeof buffer, fortune_pipe) != NULL)
    {
        fortune_string.append(buffer);
    }

    // Close fortune_pipe
    exit_status = pclose (fortune_pipe);

    // Check exit status
    if (exit_status != 0)
    {
        throw (1);
    }
    
    // Strip possible trailing newline
    if (fortune_string[fortune_string.length()-1] == '\n') {
        fortune_string.erase(fortune_string.length()-1);
    }

    // Return
    return fortune_string;
}

void send_notify (std::string message, int timeout)
{
    NotifyNotification *notification;
    
    // Create notification and set properties
    notification = notify_notification_new (settings.getTitle().c_str(),
            message.c_str (), NULL);
    notify_notification_set_urgency (notification, NOTIFY_URGENCY_LOW);
    notify_notification_set_timeout (notification, timeout * 1000);
    
    // Show it
    GError *error = NULL;
    notify_notification_show (notification, &error);
    
    // Add to the vector.
    notifications.push_back (*notification);
}

void close_notifications ()
{
    while (notifications.size () != 0)
    {
        GError *error = NULL;
        notify_notification_close (&notifications.back (), &error);
        notifications.pop_back ();
        std::cout << "Closed :: " << notifications.size () << "  ";
    }
}

// Get and send a fortune
void send_fortune ()
{
    std::string fortune;

    try
    {
        fortune = get_fortune ();
    }
    catch (int e)
    {
        display_error_dialog ("Could not get output of 'fortune'.\n"
		        "Please verify you have it installed in your system.");
		return;
	}

	send_notify (fortune, settings.getTimeout ());
}

void print_help ()
{
    std::cout<<
            "Usage: fortuner [OPTION...]\n"
            "\n"
            "  -n, --no-icon              don't display status icon\n"
            "  -c, --config FILE          use a specific configuration file\n"
            "  -h, --help                 show this help message\n"
            "  -v, --version              print program version\n";
}

int main (int argc, char *argv[])
{
    bool no_icon_mode = false;
    std::string settings_file = std::string (getenv ("HOME")) +
            "/.config/fortuner/fortuner.conf";

    // Parse arguments
    if (argc >= 1)
    {
    for (int i=1; i<argc; i++)
        {
            if (strcmp (argv[i], "--help") == 0 ||
					strcmp (argv[i], "-h") == 0)
            {
                print_help ();
                return 0;
            }
            else if (strcmp (argv[i], "--version") == 0 ||
					strcmp (argv[i], "-v") == 0)
            {
                std::cout<<PROJECT_NAME<<" "<<VERSION_STRING<<
                        " (built on "<<__DATE__<<")\n";
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
            else
            {
                std::cout<<"Invalid option '"<<argv[i]<<"'.\n";
                return 1;
            }
        }
    }
    
    if (!no_icon_mode) {
        // Initialize GTK+ library
        gtk_init (&argc, &argv);

        // The status icon
        display_status_icon ();
    }

    settings.load_settings (settings_file);
    
    // Initialize notification library
    notify_init (PROJECT_NAME);
    
    if (!no_icon_mode)
    {
        // GTK+ main loop (for status icon)
        gtk_main ();
        
        // Close notifications if settings say so.
        if (settings.getCloseNotificationsOnQuit ())
        {
            close_notifications ();
        }
    }
    else
    {
        send_fortune ();
    }

    return 0;
}
