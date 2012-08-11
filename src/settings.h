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

#ifndef SETTINGS_H
#define SETTINGS_H

class Settings
{
    public:
        void load_settings (std::string filename);

        bool getCloseNotificationsOnQuit () const { return
                closeNotificationsOnQuit; }
        bool getOffensive () const { return offensive; }
        int getTimeout () const { return timeout; }
        std::string getTitle () const { return title; }

    private:
        bool closeNotificationsOnQuit;
        bool offensive;
        int timeout;
        std::string title;
};

#endif /* SETTINGS_H */
