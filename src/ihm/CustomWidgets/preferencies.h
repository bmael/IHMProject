#ifndef PREFERENCIES_H
#define PREFERENCIES_H

#include <QDialog>
#include <QEvent>

namespace Ui {
class Preferencies;
}

enum LangType {EN, FR};

class Preferencies : public QDialog
{
    Q_OBJECT
    
public:
    explicit Preferencies(QWidget *parent = 0);
    ~Preferencies();
    
signals:
    void languageChanged(LangType lang);

private slots:
    void on_buttonBox_accepted();


private:
    Ui::Preferencies *ui;
};

#endif // PREFERENCIES_H
