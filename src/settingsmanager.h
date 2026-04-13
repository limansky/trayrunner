#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QString>
#include <QSettings>

enum CheckMethod {
    Command,
    Http
};

struct Settings {
    QString runCommand;
    CheckMethod checkMethod;
    QString checkCommand;
    QString checkUrl;
    int interval;
};


class SettingsManager
{
public:
    static SettingsManager& instance();

    const Settings& getSettings() const { return settings; }
    void save(const Settings& newSettings);

private:
    SettingsManager();
    void readSettings();
    QSettings qSettings();

private:
    Settings settings;
};

#endif // SETTINGSMANAGER_H
