#ifndef LISTFORM_H
#define LISTFORM_H

#include <QWidget>
#include <QDate>
#include <QEvent>

#include "../../Concept/Manager/taskcomponent.h"
#include "../../Concept/Manager/tasklist.h"
#include "../../Concept/Manager/task.h"

namespace Ui {
class ListForm;
}

class ListForm : public QWidget
{
    Q_OBJECT

public:
    explicit ListForm(QWidget *parent = 0);
    ~ListForm();

public slots:
    void showAbsoluteTimeLimit();
    void showRelativeTimeLimit();

    void fillSubList(QList<QString> *);

    void prepareNewTaskList();

    void retranslate();

signals:
    void hideThis();
    void sendNewTaskList(QString, int, QDate);

private:
    Ui::ListForm *ui;
};

#endif // LISTFORM_H
