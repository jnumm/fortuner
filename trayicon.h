#ifndef FORTUNER_TRAYICON_H
#define FORTUNER_TRAYICON_H

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

#include <QMenu>
#include <QStringList>
#include <QSystemTrayIcon>

namespace Fortuner {

class TrayIcon : public QSystemTrayIcon {
    Q_OBJECT

public:
    TrayIcon(QStringList&& fortuneArgs, QWidget* parent = nullptr);

private:
    void showFortune();

    const QStringList fortuneArguments;
    QMenu contextMenu;
};

}

#endif // FORTUNER_TRAYICON_H
