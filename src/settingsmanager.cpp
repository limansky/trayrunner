#include "settingsmanager.h"

#include <QSettings>
#include<QApplication>

static const char* APP_TO_RUN = "AppToRun";
static const char* APP_TO_CHECK = "AppToCheck";
static const char* URL_TO_CHECK = "UrlToCheck";
static const char* CHECK_METHOD = "CheckMethod";
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
    qDebug() << "Settings path is " << path;
    return QSettings(path + "/" + "trayrunner.ini", QSettings::Format::IniFormat);
}

void SettingsManager::readSettings() {
    QSettings s = qSettings();
    settings.runCommand = s.value(APP_TO_RUN).toString();
    settings.checkMethod = static_cast<CheckMethod>(s.value(CHECK_METHOD).toUInt());
    settings.checkCommand = s.value(APP_TO_CHECK).toString();
    settings.interval = s.value(CHECK_INTERVAL, 60).toInt();
    settings.checkUrl = s.value(URL_TO_CHECK).toString();
}

void SettingsManager::save(const Settings& newSettings) {
    settings = newSettings;
    QSettings s = qSettings();

    s.setValue(APP_TO_RUN, newSettings.runCommand);
    s.setValue(APP_TO_CHECK, newSettings.checkCommand);
    s.setValue(CHECK_METHOD, newSettings.checkMethod);
    s.setValue(CHECK_INTERVAL, newSettings.interval);
    s.setValue(URL_TO_CHECK, newSettings.checkUrl);
}