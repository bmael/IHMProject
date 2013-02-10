#ifndef LISTFORM_H
#define LISTFORM_H

#include <QWidget>

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

signals:
    void hideThis();

private:
    Ui::ListForm *ui;
};

#endif // LISTFORM_H
