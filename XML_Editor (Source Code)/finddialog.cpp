#include "finddialog.h"
#include "ui_finddialog.h"

FindDialog::FindDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindDialog)
{
    ui->setupUi(this);
    init();
    save();
}

FindDialog::~FindDialog()
{
    delete ui;
}

void FindDialog::on_buttonBox_accepted(){
    save();
    accept();
}

void FindDialog::on_buttonBox_rejected(){
    reject();
}

void FindDialog::go_back(){
    save();
    M_Backwords = true;
    accept();
}

bool FindDialog::getM_Backwords() const
{
    return M_Backwords;
}

bool FindDialog::getM_Whole_Text() const
{
    return M_Whole_Text;
}

bool FindDialog::getM_Case_Sensitive() const
{
    return M_Case_Sensitive;
}

QString FindDialog::getM_Text() const
{
    return M_Text;
}

void FindDialog::init(){
    QPushButton* btn_back = new QPushButton("Back", this);
    connect(btn_back, &QPushButton::clicked, this, &FindDialog::go_back);
    ui->buttonBox->addButton(btn_back, QDialogButtonBox::ActionRole);
}

void FindDialog::save(){
    M_Text = ui->lineEdit->text();
    M_Case_Sensitive = ui->Case->isChecked();
    M_Whole_Text = ui->Match->isChecked();
    M_Backwords = false;
}
