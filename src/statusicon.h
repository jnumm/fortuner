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

#ifndef STATUSICON_H
#define STATUSICON_H

#include <gtkmm/actiongroup.h>
#include <gtkmm/statusicon.h>
#include <gtkmm/uimanager.h>

#include "aboutdialog.h"
#include "fortuner.h"

class FortunerStatusIcon
{
public:
    FortunerStatusIcon (Fortuner& fortuner);

private:
    void on_popup_menu (guint button, guint32 activate_time);
    void on_about_activate ();
    void on_quit_activate ();

    Glib::RefPtr<Gtk::StatusIcon> m_refStatusIcon;

    Glib::RefPtr<Gtk::UIManager> m_refUIManager;
    Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup;

    Gtk::Menu* m_pMenuPopup;

    FortunerAboutDialog m_aboutDialog;
};

#endif /* STATUSICON_H */
