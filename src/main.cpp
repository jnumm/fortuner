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
#include <libnotify/notify.h>

using namespace std;

// Get a fortune and return it as std::string.
string get_fortune ()
{
    FILE *fortune_pipe;
    
    string fortune_string;
    char buffer[100];
    
    fortune_pipe = popen ("fortune -s", "r");
    
    // Check for NULL pipe
    if (fortune_pipe == NULL)
    {
        cout<<"Failed to run 'fortune'"<<endl;
    }

    // Get data
    while (fgets (buffer, sizeof buffer, fortune_pipe) != NULL)
    {
        fortune_string.append(buffer);
    }

    // Close fortune_pipe
    pclose (fortune_pipe);
    
    // Strip possible trailing newline
    if (fortune_string[fortune_string.length()-1] == '\n') {
        fortune_string.erase(fortune_string.length()-1);
    }

    // Return
    return fortune_string;
}

void send_notify (string message)
{
    NotifyNotification *notification;
    
    // Create notification and set properties
    notification = notify_notification_new ("Todays Fortune",
            message.c_str (), NULL);
    notify_notification_set_urgency (notification, NOTIFY_URGENCY_LOW);
    notify_notification_set_timeout (notification, 10000);
    
    // Show it
    GError *error = NULL;
    notify_notification_show(notification, &error);
}

int main (int argc, char *argv[])
{
    string fortune;
    
    // Initialize notification library
    notify_init("fortuner");
    
    // Get a fortune and send it
    fortune = get_fortune ();
    send_notify (fortune);
    
    return 0;
}
