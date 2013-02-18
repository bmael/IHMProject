#ifndef TASKFORM_H
#define TASKFORM_H

#include <QWidget>
#include <QEvent>

namespace Ui {
class TaskForm;
}

class TaskForm : public QWidget
{
    Q_OBJECT

public:
    explicit TaskForm(QWidget *parent = 0);
    ~TaskForm();

public slots:
    void showAbsoluteTimeLimit();
    void showRelativeTimeLimit();
    void retranslate();

signals:
    void hideThis();

private:
    Ui::TaskForm *ui;
};

#endif // TASKFORM_H
