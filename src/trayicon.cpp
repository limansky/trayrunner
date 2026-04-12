#include "trayicon.h"
#include "settingsdialog.h"
#include "settingsmanager.h"

#include <QMenu>
#include <QSystemTrayIcon>
#include <QApplication>


TrayIcon::TrayIcon(QObject *parent)
    : QObject{parent}
{
    menu = new QMenu();

    runAction = new QAction(tr("&Run"), this);
    stopAction = new QAction(tr("&Stop"), this);
    logAction = new QAction(tr("Show &output"), this);
    checkAction = new QAction(tr("&Check now"));

    updateActions();

    menu->addAction(runAction);
    menu->addAction(stopAction);
    menu->addAction(logAction);
    menu->addAction(checkAction);
    menu->addSeparator();

    menu->addAction(tr("Settings"), this, SLOT(showSettings()));
    menu->addSeparator();
    menu->addAction(tr("&Quit"), this, SLOT(quit()));

    trayIcon = new QSystemTrayIcon(QApplication::windowIcon(), this);
    trayIcon->setContextMenu(menu);
    trayIcon->setVisible(true);
}

void TrayIcon::showSettings()
{
    SettingsDialog dlg(SettingsManager::instance().getSettings());

    if (dlg.exec() == QDialog::Accepted) {
        trayIcon->showMessage("Hello", "Gonna do something");
    }
}

void TrayIcon::quit()
{
    QApplication::quit();
}

void TrayIcon::updateActions() {
    auto settings = SettingsManager::instance().getSettings();

    bool canRun = !settings.toRun.isEmpty();
    bool canCheck = !settings.toCheck.isEmpty(); // TODO: && isRunning

    runAction->setEnabled(canRun);
    stopAction->setEnabled(canRun);
    logAction->setEnabled(canRun);
    checkAction->setEnabled(canCheck);
}