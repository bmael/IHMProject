#ifndef TASKLISTWIDGET_H
#define TASKLISTWIDGET_H

#include <QWidget>
#include <QDate>
#include <QEvent>

#include "../../Concept/Manager/taskcomponent.h"
#include "../../Concept/Manager/tasklist.h"
#include "../../Concept/Manager/task.h"

namespace Ui {
class TaskListWidget;
}

class TaskListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TaskListWidget(QWidget *parent = 0);
    ~TaskListWidget();

signals:
    void sendNewTaskList(QString, int, QDate);
    void sendRemoveTaskList();
    void askFillSubList(QList<QString> *);
    void askRetranslate();

public slots:
    void showNewTaskListForm();
    void showModifyTaskListForm();
    void hideListForm();

    void retranslate();

private:
    Ui::TaskListWidget *ui;
};

#endif // TASKLISTWIDGET_H
