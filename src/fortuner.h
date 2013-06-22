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

#ifndef FORTUNER_H
#define FORTUNER_H

#include <vector>

#include <libnotify/notify.h>

#include "settings.h"

class Fortuner
{
public:
    Fortuner (const Settings& settings);
    ~Fortuner ();

    void send_fortune ();
    void close_notifications ();

private:
    std::string get_fortune () const;
    void send_notify (const std::string& message);

    const Settings& m_settings;

    std::vector<NotifyNotification> m_notifications;
};

#endif // FORTUNER_H
