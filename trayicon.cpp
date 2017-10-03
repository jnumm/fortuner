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

#include "trayicon.h"

#include <utility> // for std::move

#include <QApplication>
#include <QIcon>
#include <QIODevice>
#include <QMessageBox>
#include <QProcess>

#include "config.h"

Fortuner::TrayIcon::TrayIcon(QStringList fortuneArguments, QWidget* parent)
    : QSystemTrayIcon{qApp->windowIcon(), parent}
    , fortuneArgs{std::move(fortuneArguments)}
{
    setToolTip(tr("Fortuner"));

#ifndef Q_OS_MACOS
    // On macOS, left and right clicking a system tray icon have the same effect
    connect(this, &QSystemTrayIcon::activated,
            this, &Fortuner::TrayIcon::showFortune);
#endif

    contextMenu.addAction(icon(), tr("Show a fortune"), [this]() {
        showFortune(QSystemTrayIcon::ActivationReason::Unknown);
    });
    contextMenu.addSeparator();
    contextMenu.addAction(QIcon::fromTheme("help-about"), tr("About Fortuner…"), []() {
        QMessageBox::about(nullptr, tr("About Fortuner"),
                tr("<div style='text-align:center'>"
                   "<p><span style='font-size:35pt'>Fortuner</span><br>"
                   "Version %1</p>"
                   "<p>Fortuner shows fortunes as notifications.</p>"
                   "<p><a href='https://github.com/jnumm/fortuner'>Homepage</a></p>"
                   "<p style='font-size:small'>Copyright © Juhani Numminen 2017.<br>"
                   "Distributed under the terms of GPLv3+.</p>"
                   "</div>").arg(FORTUNER_VERSION));
    });
    contextMenu.addAction(QIcon::fromTheme("application-exit"), tr("Quit"), qApp, &QApplication::quit);
    setContextMenu(&contextMenu);
}

void Fortuner::TrayIcon::showFortune(QSystemTrayIcon::ActivationReason reason) {
    if (reason == QSystemTrayIcon::ActivationReason::Context)
        return;

    QProcess fortune;
    fortune.start("fortune", fortuneArgs, QIODevice::ReadOnly);
    if (fortune.waitForFinished()) {
        showMessage(tr("Fortuner"),
                fortune.readAll().replace('<', "&lt;").append("–––"),
                QSystemTrayIcon::MessageIcon::NoIcon);
    } else {
        QMessageBox::critical(nullptr, tr("Fortuner: fortune failed"),
                tr("<p>Could not execute <tt>fortune</tt>.<br> Try to install "
                   "package <tt>fortune</tt> or <tt>fortune-mod</tt>.</p> "
                   "<p>Error output:</p>") + fortune.errorString());
    }
}
