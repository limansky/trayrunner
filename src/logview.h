#ifndef LOGVIEW_H
#define LOGVIEW_H

#include <QDialog>

namespace Ui {
class LogView;
}

class LogView : public QDialog
{
    Q_OBJECT

public:
    explicit LogView(QString logs, QWidget *parent = nullptr);
    ~LogView();

private:
    Ui::LogView *ui;
};

#endif // LOGVIEW_H
