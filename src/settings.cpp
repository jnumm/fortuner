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

#include <fstream>
#include <iostream>
#include <sstream>

#include "gettext.h"
#include "settings.h"

Settings::Settings (const std::string& filename)
{
    m_closeNotificationsOnQuit = true;
    m_offensive = false;
    m_timeout = 10;
    m_title = _("Today's fortune");

    std::ifstream fin (filename);
    if (fin.is_open ())
    {
        std::string line;
        while (getline (fin, line))
        {
            std::istringstream sin (line.substr (line.find ('=') + 1));
            if (line.find ("closeNotificationsOnQuit") != std::string::npos)
            {
                sin >> m_closeNotificationsOnQuit;
            }
            else if (line.find ("offensive") != std::string::npos)
            {
                sin >> m_offensive;
            }
            else if (line.find ("timeout") != std::string::npos)
            {
                sin >> m_timeout;
            }
            else if (line.find ("title") != std::string::npos)
            {
                sin >> m_title;
            }
        }
    }
}

Settings::~Settings()
{
}

// The getters.
bool Settings::getCloseNotificationsOnQuit () const
{
    return m_closeNotificationsOnQuit;
}

bool Settings::getOffensive () const
{
    return m_offensive;
}

int Settings::getTimeout () const
{
    return m_timeout;
}

std::string Settings::getTitle () const
{
    return m_title;
}

// The setters.
void Settings::setCloseNotificationsOnQuit (bool value)
{
    m_closeNotificationsOnQuit = value;
}

void Settings::setOffensive (bool value)
{
    m_offensive = value;
}

void Settings::setTimeout (int value)
{
    m_timeout = value;
}

void Settings::setTitle (const std::string& value)
{
    m_title = value;
}
