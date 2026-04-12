#include "settingsdialog.h"
#include "settingsmanager.h"
#include "ui_settingsdialog.h"

#include <QFileDialog>

SettingsDialog::SettingsDialog(const Settings& settings, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    ui->commandEdit->setText(settings.toRun);
    ui->checkCmdEdit->setText(settings.toRun);
    ui->checkInterval->setValue(settings.interval);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

Settings SettingsDialog::getSettings()
{
    Settings s;
    s.toRun = ui->commandEdit->text();
    s.toCheck = ui->checkCmdEdit->text();
    s.interval = ui->checkInterval->value();
    return s;
}

void SettingsDialog::on_commandBtn_clicked()
{
    QFileDialog fileDialog(this);

    if (fileDialog.exec() == QFileDialog::Accepted) {
        ui->commandEdit->setText(fileDialog.selectedFiles().first());
    }
}

