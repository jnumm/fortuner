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

#include <gtkmm/main.h>
#include <gtkmm/stock.h>

#include "gettext.h"
#include "statusicon.h"

FortunerStatusIcon::FortunerStatusIcon (Fortuner& fortuner)
    : m_pMenuPopup(0)
{
    m_refStatusIcon = Gtk::StatusIcon::create ("fortuner");
    m_refStatusIcon->set_tooltip_text (_("Fortuner"));

    m_refStatusIcon->signal_activate ().connect (sigc::mem_fun (fortuner,
            &Fortuner::send_fortune));
    m_refStatusIcon->signal_popup_menu ().connect (sigc::mem_fun (*this,
            &FortunerStatusIcon::on_popup_menu));

    m_refActionGroup = Gtk::ActionGroup::create ();

    m_refActionGroup->add (Gtk::Action::create ("PopupMenu", "Popup Menu"));

    m_refActionGroup->add (Gtk::Action::create ("CloseFortunes",
            _("_Close Fortunes")), sigc::mem_fun (fortuner,
            &Fortuner::close_notifications));

    m_refActionGroup->add (Gtk::Action::create ("About", Gtk::Stock::ABOUT),
            sigc::mem_fun (*this, &FortunerStatusIcon::on_about_activate));

    m_refActionGroup->add (Gtk::Action::create ("Quit", Gtk::Stock::QUIT),
          sigc::mem_fun (*this, &FortunerStatusIcon::on_quit_activate));

    m_refUIManager = Gtk::UIManager::create ();
    m_refUIManager->insert_action_group (m_refActionGroup);

    const Glib::ustring ui_info =
            "<ui>"
            "   <popup name='PopupMenu'>"
            "       <menuitem action='CloseFortunes'/>"
            "       <menuitem action='About'/>"
            "       <menuitem action='Quit'/>"
            "   </popup>"
            "</ui>";

    try
    {
        m_refUIManager->add_ui_from_string (ui_info);
    }
    catch (const Glib::Error& ex)
    {
        std::cerr << "building menus failed: " <<  ex.what ();
    }

    m_pMenuPopup = dynamic_cast<Gtk::Menu*> (
            m_refUIManager->get_widget ("/PopupMenu")); 
    if (!m_pMenuPopup)
        g_warning ("menu not found");

    m_refStatusIcon->set_visible ();
}

void FortunerStatusIcon::on_popup_menu (guint button, guint32 activate_time)
{
    if (m_pMenuPopup) {
        m_pMenuPopup->popup (button, activate_time);
    }
}

void FortunerStatusIcon::on_about_activate ()
{
    m_aboutDialog.show ();
}

void FortunerStatusIcon::on_quit_activate ()
{
    Gtk::Main::quit ();
}
