#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
    class SettingsDialog;
}
QT_END_NAMESPACE

class Settings;

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(const Settings& settings, QWidget *parent = nullptr);
    ~SettingsDialog() override;

    Settings getSettings();

private slots:
    void on_commandBtn_clicked();

    void on_checkCmdBtn_clicked();

private:
    Ui::SettingsDialog *ui;
};
#endif // SETTINGSDIALOG_H
