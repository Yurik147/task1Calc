#include "calculator.h"
#include "ui_calculator.h"

Calculator::Calculator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Calculator)
{
    ui->setupUi(this);
    connect(ui->radioButton, SIGNAL(clicked()), SLOT(btnSelect1()));
    connect(ui->radioButton_2, SIGNAL(clicked()), SLOT(btnSelect2()));
    connect(ui->radioButton_3, SIGNAL(clicked()), SLOT(btnSelect3()));
    connect(ui->pushButton_2, SIGNAL(clicked()), SLOT(btnResult()));
    connect(ui->pushButton, SIGNAL(clicked()), SLOT(btnClear()));
    connect(ui->pushButton_3, SIGNAL(clicked()), SLOT(btnFloatPoint()));
    connect(ui->pushButton_4, SIGNAL(clicked()), SLOT(btnNull()));
    ui->lineEdit->installEventFilter(this);
    ui->lineEdit_2->installEventFilter(this);
    ui->lineEdit_3->installEventFilter(this);
    editHasEvent = false;
    type = 0;
    QString btnNames[3][3] = {
        {"1", "2", "3"},
        {"4", "5", "6"},
        {"7", "8", "9"},
    };
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            ui->gridLayout->addWidget(createButton(btnNames[i][j]),i ,j);
        }
    }
}

void Calculator::btnSelect1()
{
    type = 0;
    ui->label_2->setText("A = ");
    ui->label_3->setText("L = ");
    ui->label_3->show();
    ui->lineEdit_2->show();
    ui->label_4->setText("H = ");
    btnClear();
}

void Calculator::btnSelect2()
{
    type = 1;
    ui->label_2->setText("R = ");
    ui->label_3->hide();
    ui->lineEdit_2->hide();
    ui->label_4->setText("H = ");
    btnClear();
}

void Calculator::btnSelect3()
{
    type = 2;
    ui->label_2->setText("R = ");
    ui->label_3->setText("L = ");
    ui->label_3->show();
    ui->lineEdit_2->show();
    ui->label_4->setText("H = ");
    btnClear();
}

void Calculator::btnResult()
{
    bool isNoGood = false;
    switch (type) {
    case 0:
        A = ui->lineEdit->text().toDouble(&isNoGood);
        checkData(isNoGood);
        H = ui->lineEdit_3->text().toDouble(&isNoGood);
        checkData(isNoGood);
        L = ui->lineEdit_2->text().toDouble(&isNoGood);
        checkData(isNoGood);
        break;
    case 1:
        R = ui->lineEdit->text().toDouble(&isNoGood);
        checkData(isNoGood);
        H = ui->lineEdit_3->text().toDouble(&isNoGood);
        checkData(isNoGood);
        break;
    case 2:
        R = ui->lineEdit->text().toDouble(&isNoGood);
        checkData(isNoGood);
        H = ui->lineEdit_3->text().toDouble(&isNoGood);
        checkData(isNoGood);
        L = ui->lineEdit_2->text().toDouble(&isNoGood);
        checkData(isNoGood);
        break;
    default:
        break;
    }
    if(isNoGood){
        QString s;
        Sb = frSquare(type);
        S = frAllSquare(type);
        V = frVolume(type);
        s.append("Sb = " + QString::number(Sb) + "; ");
        s.append("S = " + QString::number(S) + "; ");
        s.append("V = " + QString::number(V) + "; ");
        ui->lineEdit_4->setText(s);
    }
}

void Calculator::btnNull()
{
    if(editHasEvent){
        QString s = edit->text();
        edit->setText(s.append("0"));
    }else{
        int ret = QMessageBox::warning(this, "Warning", "Please select edit field.");
    }
}

Calculator::~Calculator()
{
    delete ui;
}

double Calculator::frSquare(int type)
{
    switch (type) {
    case 0:
        return (A * L * 4) / 2.0;
        break;
    case 1:
        return 2 * 3.14 * R * H;
        break;
    case 2:
        return 3.14 * R * L;
        break;
    default:
        break;
    }
    return -1;
}

double Calculator::frAllSquare(int type)
{
    switch (type) {
    case 0:
        return (A * L * 4) / 2.0 + A * A;
        break;
    case 1:
        return 2 * 3.14 * R * H + 3.14 * R * R;
        break;
    case 2:
        return 3.14 * R * L + 3.14 * R * R;
        break;
    default:
        break;
    }
    return -1;
}

double Calculator::frVolume(int type)
{
    switch (type) {
    case 0:
        return (A * A * H) / 3.0;
        break;
    case 1:
        return 3.14 * R * R * H;
        break;
    case 2:
        return (1 / 3.0) * (3.14 * R * R * H);
        break;
    default:
        break;
    }
    return -1;
}

void Calculator::checkData(bool isNoGood)
{
    if(!isNoGood)
        int ret = QMessageBox::warning(this, "Warning", "Please check data.\nInput only 0-9 and symbol \'.\'.");
}

QPushButton *Calculator::createButton(QString name)
{
    QPushButton *btn = new QPushButton(name);
    connect(btn, SIGNAL(clicked()), SLOT(btnKeyBoard()));
    return btn;
}

void Calculator::btnKeyBoard()
{
    if(editHasEvent){
        QString btnStr = ((QPushButton*)sender())->text();
        QString s = edit->text();
        edit->setText(s.append(btnStr));
    }else{
        int ret = QMessageBox::warning(this, "Warning", "Please select edit field.");
    }
}


void Calculator::btnClear()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
}

void Calculator::btnFloatPoint()
{
    if(editHasEvent){
        QString s = edit->text();
        edit->setText(s.append("."));
    }else{
        int ret = QMessageBox::warning(this, "Warning", "Please select edit field.");
    }
}

bool Calculator::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn)
        {
            edit = (QLineEdit*)obj;
            editHasEvent = true;
        }
        return false;
}
