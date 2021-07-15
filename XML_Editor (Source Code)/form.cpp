#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}

void Form::Add_Text(QString txt)
{
    ui->textEdit->setText(txt);
}

QString Form::Get_Text(){
    return ui->textEdit->toPlainText();
}
