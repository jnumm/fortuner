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

#include <gtk/gtk.h>

#include "main.h"
#include "status_icon.h"

static GtkWidget *menu = NULL;
static GtkStatusIcon *status_icon = NULL;

static void destroy (GtkWidget *widget, gpointer data)
{
    gtk_main_quit ();
}

static void activate (GtkStatusIcon* status_icon, gpointer user_data)
{
    send_notify ("Fortuner icon clicked!", 10);
}

static void popup_menu (GtkStatusIcon *status_icon, guint button,
    guint activate_time, gpointer user_data)
{
    if (!menu)
    {
        GtkWidget *item;
        menu = gtk_menu_new ();
        
        item = gtk_menu_item_new_with_label ("Quit");
        gtk_menu_append (menu, item);
        g_signal_connect (G_OBJECT (item), "activate",
                G_CALLBACK (destroy), 
                NULL);
    }
    
    gtk_widget_show_all (menu);

    gtk_menu_popup (GTK_MENU (menu),
            NULL,
            NULL,
            gtk_status_icon_position_menu,
            status_icon,
            button,
            activate_time);
}

void display_status_icon ()
{
    status_icon = gtk_status_icon_new_from_icon_name ("fortuner");
    gtk_status_icon_set_visible (status_icon, TRUE); 

    gtk_status_icon_set_tooltip (status_icon, "Fortuner");

    // Connect signals
    g_signal_connect (G_OBJECT (status_icon), "popup-menu",
              G_CALLBACK (popup_menu), NULL);

    g_signal_connect (G_OBJECT (status_icon), "activate",
              G_CALLBACK (activate), NULL);
}
