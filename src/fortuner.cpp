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

#include <iostream>

#include "fortuner.h"
#include "gettext.h"

Fortuner::Fortuner (const Settings& settings)
    : m_settings(settings)
{
}

// Get and send a fortune.
void Fortuner::send_fortune ()
{
    std::string fortune;

    try
    {
        fortune = get_fortune ();
    }
    catch (int e)
    {
        std::cerr << _("Could not get output of 'fortune'.\n"
                "Please verify you have it installed in your system.") << "\n";
        return;
    }

    send_notify (fortune);
}

// Close all notifications of the vector.
void Fortuner::close_notifications ()
{
    while (m_notifications.size () != 0)
    {
        GError *error = NULL;
        notify_notification_close (&m_notifications.back (), &error);
        m_notifications.pop_back ();
    }
}


// Get a fortune and return it as std::string.
std::string Fortuner::get_fortune () const
{
    FILE *fortune_pipe;

    std::string fortune_cmdline = "fortune -s";
    std::string fortune_string;
    char buffer[100];
    int exit_status;

    if (m_settings.getOffensive ())
    {
        /* From the fortune(6) man page:
         * -a  Choose  from all lists of maxims, both offensive and not.
         */
        fortune_cmdline += " -a";
    }

    fortune_pipe = popen (fortune_cmdline.c_str (), "r");

    // Check for NULL pipe.
    if (fortune_pipe == NULL)
    {
        std::cerr<<_("Failed to run 'fortune'.\n");
    }

    // Get data from the pipe and append it to the buffer.
    while (fgets (buffer, sizeof buffer, fortune_pipe) != NULL)
    {
        fortune_string.append (buffer);
    }

    // Close fortune_pipe
    exit_status = pclose (fortune_pipe);

    // Check exit status
    if (exit_status != 0)
    {
        throw (1);
    }

    // Strip possible trailing newline
    if (fortune_string [fortune_string.length () - 1] == '\n') {
        fortune_string.erase (fortune_string.length () - 1);
    }

    // Return
    return fortune_string;
}

void Fortuner::send_notify (const std::string& message)
{
    NotifyNotification* notification;

    // Create notification and set properties
    notification = notify_notification_new (m_settings.getTitle ().c_str (),
            message.c_str (), NULL);
    notify_notification_set_urgency (notification, NOTIFY_URGENCY_LOW);
    notify_notification_set_timeout (notification,
            m_settings.getTimeout () * 1000);

    // Show the notification.
    GError *error = NULL;
    notify_notification_show (notification, &error);

    // Add to the vector.
    m_notifications.push_back (*notification);
}
