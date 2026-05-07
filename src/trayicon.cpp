#include "trayicon.h"
#include "settingsdialog.h"
#include "settingsmanager.h"
#include "watchdog.h"
#include "logview.h"

#include <QMenu>
#include <QSystemTrayIcon>
#include <QApplication>


TrayIcon::TrayIcon(QObject *parent)
    : QObject(parent),
    watchdog(nullptr)
{
    menu = new QMenu();

    runAction = new QAction(tr("&Run"), this);
    stopAction = new QAction(tr("&Stop"), this);
    logAction = new QAction(tr("Show &output"), this);
    checkAction = new QAction(tr("&Check now"));

    QObject::connect(runAction, &QAction::triggered, this, &TrayIcon::start);
    QObject::connect(stopAction, &QAction::triggered, this, &TrayIcon::stop);
    QObject::connect(logAction, &QAction::triggered, this, &TrayIcon::showLogs);

    updateActions();

    menu->addAction(runAction);
    menu->addAction(stopAction);
    menu->addAction(logAction);
    menu->addAction(checkAction);
    menu->addSeparator();

    menu->addAction(tr("Settings"), this, &TrayIcon::showSettings);
    menu->addSeparator();
    menu->addAction(tr("&Quit"), this, &TrayIcon::quit);

    trayIcon = new QSystemTrayIcon(QApplication::windowIcon(), this);
    trayIcon->setContextMenu(menu);
    trayIcon->setVisible(true);
}

void TrayIcon::showSettings()
{
    SettingsDialog dlg(SettingsManager::instance().getSettings());

    if (dlg.exec() == QDialog::Accepted) {
        SettingsManager::instance().save(dlg.getSettings());
        updateActions();
        trayIcon->showMessage("Hello", "Gonna do something");
    }
}

void TrayIcon::quit()
{
    QApplication::quit();
}

void TrayIcon::updateActions() {
    auto settings = SettingsManager::instance().getSettings();

    bool canRun = !settings.runCommand.isEmpty() && (watchdog == nullptr || !watchdog->isRunning());
    bool canCheck = ((settings.checkMethod == CheckMethod::Command && !settings.checkCommand.isEmpty()) ||
                    (settings.checkMethod == CheckMethod::Http && !settings.checkUrl.isEmpty())) &&
                    watchdog && watchdog->isRunning();

    bool canStop = watchdog != nullptr && watchdog->isRunning();

    runAction->setEnabled(canRun);
    stopAction->setEnabled(canStop);
    logAction->setEnabled(watchdog != nullptr);
    checkAction->setEnabled(canCheck);
}

void TrayIcon::start() {
    Q_ASSERT(watchdog == nullptr);

    auto settings = SettingsManager::instance().getSettings();
    Q_ASSERT(!settings.runCommand.isEmpty());

    watchdog = new Watchdog(settings.runCommand, this);

    watchdog->start();
    updateActions();
}

void TrayIcon::stop() {
    Q_ASSERT(watchdog);

    watchdog->stop();
    delete watchdog;
    watchdog = nullptr;
    updateActions();
}

void TrayIcon::showLogs() {
    Q_ASSERT(watchdog);

    QString logs = watchdog->logs();

    LogView logView = LogView(logs);

    logView.exec();
}