#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class Calculator;
}

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = 0);
    ~Calculator();

private:
    Ui::Calculator *ui;
    QLineEdit *edit;
    bool editHasEvent;
    int type;
    double Sb;
    double So;
    double S;
    double V;
    double R;
    double H;
    double L;
    double A;
    double frSquare(int type);
    double frAllSquare(int type);
    double frVolume(int type);
    void checkData(bool isNoGood);
    QPushButton *createButton(QString name);

public slots:
    void btnKeyBoard();
    void btnSelect1();
    void btnSelect2();
    void btnSelect3();
    void btnClear();
    void btnResult();
    void btnNull();
    void btnFloatPoint();

protected:
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // CALCULATOR_H
