#ifndef TASKLISTWIDGET_H
#define TASKLISTWIDGET_H

#include <QWidget>

namespace Ui {
class TaskListWidget;
}

class TaskListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TaskListWidget(QWidget *parent = 0);
    ~TaskListWidget();

public slots:
    void showNewTaskListForm();
    void showModifyTaskListForm();
    void hideListForm();

private:
    Ui::TaskListWidget *ui;
};

#endif // TASKLISTWIDGET_H
