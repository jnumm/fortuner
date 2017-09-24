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

#include <QApplication>
#include <QIcon>
#include <QIODevice>
#include <QMessageBox>
#include <QProcess>

Fortuner::TrayIcon::TrayIcon(QStringList&& fortuneArgs, QWidget* parent)
    : QSystemTrayIcon(qApp->windowIcon(), parent)
    , fortuneArguments(fortuneArgs)
    , contextMenu()
{
    setToolTip(tr("Fortuner"));

    connect(this, &QSystemTrayIcon::activated,
            this, &Fortuner::TrayIcon::showFortune);

    contextMenu.addAction(QIcon::fromTheme("help-about"), tr("About Fortuner…"), []() {
        QMessageBox::about(nullptr, tr("About Fortuner"),
                tr("<p>Fortuner shows fortunes as notifications.</p> "
                   "<p>Copyright © Juhani Numminen 2017.<br> "
                   "Distributed under the terms of GPLv3+.</p> "
                   "<p><a href='https://github.com/jnumm/fortuner'>Homepage</a></p>"));
    });
    contextMenu.addAction(QIcon::fromTheme("application-exit"), tr("Quit"), qApp, &QApplication::quit);

    setContextMenu(&contextMenu);

    show();
}

void Fortuner::TrayIcon::showFortune(QSystemTrayIcon::ActivationReason reason) {
    if (reason == QSystemTrayIcon::ActivationReason::Context)
        return;

    QProcess fortune;
    fortune.start("fortune", fortuneArguments, QIODevice::ReadOnly);
    if (fortune.waitForFinished())

#if (QT_VERSION >= QT_VERSION_CHECK(5, 9, 0))
#   define FORTUNER_QICON_OR_ENUM icon()
#else
#   define FORTUNER_QICON_OR_ENUM QSystemTrayIcon::NoIcon
#endif
        showMessage(tr("Fortuner"),
                fortune.readAll().replace('<', "&lt;") + "–––",
                FORTUNER_QICON_OR_ENUM);
#undef FORTUNER_QICON_OR_ENUM

    else
        QMessageBox::critical(nullptr, tr("Fortuner: fortune failed"),
                tr("<p>Could not execute <tt>fortune</tt>.<br> Try to install "
                   "package <tt>fortune</tt> or <tt>fortune-mod</tt>.</p> "
                   "<p>Error output:</p>") + fortune.errorString());
}
