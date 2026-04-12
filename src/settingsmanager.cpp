#include "settingsmanager.h"

#include <QSettings>
#include<QApplication>

static const char* APP_TO_RUN = "AppToRun";
static const char* APP_TO_CHECK = "AppToCheck";
static const char* CHECK_INTERVAL = "CheckInterval";

SettingsManager::SettingsManager() {
    readSettings();
}

SettingsManager& SettingsManager::instance() {
    static SettingsManager self;
    return self;
}

QSettings SettingsManager::qSettings() {
    auto path = QApplication::instance()->applicationDirPath();
    return QSettings(path + "/" + "trayrunner.ini", QSettings::Format::IniFormat);
}

void SettingsManager::readSettings() {
    QSettings s = qSettings();
    settings.toRun = s.value(APP_TO_RUN).toString();
    settings.toCheck= s.value(APP_TO_CHECK).toString();
    settings.interval = s.value(CHECK_INTERVAL, 60).toInt();
}

void SettingsManager::save(const Settings& newSettings) {
    settings = newSettings;
    QSettings s = qSettings();

    s.setValue(APP_TO_RUN, newSettings.toRun);
    s.setValue(APP_TO_CHECK, newSettings.toCheck);
    s.setValue(CHECK_INTERVAL, newSettings.interval);
}