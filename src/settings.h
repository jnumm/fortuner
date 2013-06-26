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

#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

class Settings
{
public:
    Settings (const std::string& filename);
    ~Settings ();

    // The getters.
    bool getCloseNotificationsOnQuit () const;
    bool getOffensive () const;
    int getTimeout () const;
    std::string getTitle () const;

    // The setters.
    void setCloseNotificationsOnQuit (bool value);
    void setOffensive (bool value);
    void setTimeout (int value);
    void setTitle (const std::string& value);

private:
    bool m_closeNotificationsOnQuit;
    bool m_offensive;
    int m_timeout;
    std::string m_title;
};

#endif // SETTINGS_H
