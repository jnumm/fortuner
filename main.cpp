/*
 * fortuner
 * Copyright (C) 2017 Juhani Numminen <juhaninumminen0@gmail.com>
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

#include <QApplication>
#include <QIcon>
#include <QLocale>
#include <QTranslator>

#include "config.h"
#include "trayicon.h"

int main(int argc, char* argv[]) {
    QApplication app{argc, argv};

    QTranslator translator;
    translator.load(QLocale{}, "fortuner", "_", TRANSLATION_DIR);
    app.installTranslator(&translator);

    app.setOrganizationName("jnumm");
    app.setApplicationName("fortuner");
    app.setApplicationDisplayName(Fortuner::TrayIcon::tr("Fortuner"));
    app.setApplicationVersion(FORTUNER_VERSION);
    app.setQuitOnLastWindowClosed(false);

#ifdef FORTUNER_QRESOURCE_ICON
    app.setWindowIcon(QIcon{":/icon.png"});
#else
    app.setWindowIcon(QIcon::fromTheme("fortuner"));
#endif

    auto tail = [](auto list) { list.pop_front(); return list; };

    // We don't want the argument list to fortune to contain our program name
    Fortuner::TrayIcon trayIcon{tail(app.arguments())};
    trayIcon.show();

    return app.exec();
}
