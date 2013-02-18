#ifndef PROJECTWIDGET_H
#define PROJECTWIDGET_H

#include <QDialog>
#include <QDate>

namespace Ui {
class ProjectWidget;
}

class ProjectWidget : public QDialog
{
    Q_OBJECT
    
public:
    explicit ProjectWidget(QWidget *parent = 0);
    ~ProjectWidget();
    
signals:
    void transmitConfiguration(QString, int, QDate);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ProjectWidget *ui;
};

#endif // PROJECTWIDGET_H
