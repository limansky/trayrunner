#include "trayicon.h"

#include <QApplication>
#include <QSystemTrayIcon>
#include <QIcon>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        qWarning("No system tray available!");
        QMessageBox::critical(nullptr, QObject::tr("TrayRunner"), QObject::tr("System tray is not found!"));

        return -1;
    }

    QApplication::setWindowIcon(QIcon::fromTheme("trayrunner", QIcon(":/icons/trayrunner.png")));
    QApplication::setQuitOnLastWindowClosed(false);

    TrayIcon icon;

    return QCoreApplication::exec();
}
