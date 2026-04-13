#include "settingsdialog.h"
#include "settingsmanager.h"
#include "ui_settingsdialog.h"

#include <QFileDialog>

SettingsDialog::SettingsDialog(const Settings& settings, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    ui->commandEdit->setText(settings.runCommand);
    ui->checkCmdEdit->setText(settings.checkCommand);
    ui->checkCommandRadio->setChecked(settings.checkMethod == CheckMethod::Command);
    ui->checkUrlRadio->setChecked(settings.checkMethod == CheckMethod::Http);
    ui->checkInterval->setValue(settings.interval);
    ui->urlEdit->setText(settings.checkUrl);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

Settings SettingsDialog::getSettings()
{
    Settings s;
    s.runCommand = ui->commandEdit->text();
    s.checkCommand = ui->checkCmdEdit->text();
    s.checkMethod = ui->checkCommandRadio->isChecked() ? CheckMethod::Command : CheckMethod::Http;
    s.interval = ui->checkInterval->value();
    s.checkUrl = ui->urlEdit->text();
    return s;
}

void SettingsDialog::on_commandBtn_clicked()
{
    QFileDialog fileDialog(this);

    if (fileDialog.exec() == QFileDialog::Accepted) {
        ui->commandEdit->setText(fileDialog.selectedFiles().first());
    }
}


void SettingsDialog::on_checkCmdBtn_clicked()
{
    QFileDialog fileDialog(this);

    if (fileDialog.exec() == QFileDialog::Accepted) {
        ui->checkCmdEdit->setText(fileDialog.selectedFiles().first());
    }
}

