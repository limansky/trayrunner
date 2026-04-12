#ifndef TRAYICON_H
#define TRAYICON_H

#include <QObject>

class QSystemTrayIcon;
class QMenu;
class QAction;

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

signals:

public slots:
    void showSettings();
    void quit();
};

#endif // TRAYICON_H
