#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <QObject>

class QProcess;

class Watchdog: public QObject
{
    Q_OBJECT
public:
    explicit Watchdog(QString path, QObject* parent = nullptr);

    void start();
    void stop();
    bool isRunning() const;
    QString logs();

signals:
    void startError(const QString message);

public slots:
    void onProgramStarted();
    void onStartFailed();
    void onProgramStopped(int exitCode);
    void onStdout();
    void onErr();

private:
    QProcess* process;
    QString path;
    QStringList log;
};

#endif // WATCHDOG_H
