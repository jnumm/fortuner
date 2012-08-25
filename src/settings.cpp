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

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "settings.h"

/* Load settings from a config file.
 * This implementation looks a bit clumsy, it'll be fixed some day. */
void Settings::load_settings (std::string filename)
{
    std::ifstream fin (filename.c_str ());
    if (fin.is_open ())
    {
        std::string line;
        while (getline (fin, line))
        {
            std::istringstream sin (line.substr (
                    line.find ("=") + 1));
            if (line.find ("closeNotificationsOnQuit") != -1)
            {
                sin >> closeNotificationsOnQuit;
            }
            else if (line.find ("offensive") != -1)
            {
                sin >> offensive;
            }
            else if (line.find ("timeout") != -1)
            {
                sin >> timeout;
            }
            else if (line.find ("title") != -1)
            {
                sin >> title;
            }
        }
    }
    else
    {
        std::cout<<"Not able to open configuration file. "
                "Using defaults.\n";

        closeNotificationsOnQuit = true;
        offensive = false;
        timeout = 10;
        title = "Today's fortune";
    }
}
