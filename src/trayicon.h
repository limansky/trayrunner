#ifndef TRAYICON_H
#define TRAYICON_H

#include <QObject>

class QSystemTrayIcon;
class QMenu;
class QAction;
class Watchdog;

class TrayIcon : public QObject
{
    Q_OBJECT
public:
    explicit TrayIcon(QObject *parent = nullptr);

private:
    void updateActions();

private:
    QMenu* menu;
    QSystemTrayIcon* trayIcon;
    QAction* runAction;
    QAction* stopAction;
    QAction* checkAction;
    QAction* logAction;
    Watchdog* watchdog;

signals:

public slots:
    void showSettings();
    void quit();
    void start();
    void stop();
    void showLogs();
};

#endif // TRAYICON_H
