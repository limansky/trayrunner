#include "watchdog.h"

#include <QProcess>
#include <QDebug>

Watchdog::Watchdog(QString path, QObject* parent): QObject(parent), process(nullptr), path(path) {}


void Watchdog::start()
{
    if (process) {
        process->kill();
        delete process;
        process = nullptr;
    }

    log.clear();

    process = new QProcess(this);
    connect(process, &QProcess::errorOccurred, this, &Watchdog::onStartFailed);
    connect(process, &QProcess::finished, this, &Watchdog::onProgramStopped);
    connect(process, &QProcess::readyReadStandardError, this, &Watchdog::onErr);
    connect(process, &QProcess::readyReadStandardOutput, this, &Watchdog::onStdout);

    qDebug() << "Starting process";
    process->startCommand(path);
    qDebug() << "Started process";
}

bool Watchdog::isRunning() const {
    qDebug() << "IS RUNNUNG";
    return process != nullptr && process->state() != QProcess::NotRunning;
}

void Watchdog::stop()
{
    if (process) {
        process->kill();
    }
}

QString Watchdog::logs() {
    return log.join("\n");
}

void Watchdog::onProgramStarted() {
    qDebug() << "Process started";
}

void Watchdog::onStartFailed() {
    auto err = process->errorString();
    qDebug() << "Start failed" << process->errorString();
    process->deleteLater();
    process = nullptr;
    emit startError(err);
}

void Watchdog::onProgramStopped(int exitCode) {
    qDebug() << "Process stopped with code " << exitCode;
}

void Watchdog::onStdout() {
    log.push_back(QString(process->readAllStandardOutput()));
}

void Watchdog::onErr() {
    log.push_back(QString(process->readAllStandardError()));
}
