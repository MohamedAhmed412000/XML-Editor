#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class FindDialog;
}

class FindDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindDialog(QWidget *parent = 0);
    ~FindDialog();

    QString getM_Text() const;
    bool getM_Case_Sensitive() const;
    bool getM_Whole_Text() const;
    bool getM_Backwords() const;

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void go_back();

private:
    Ui::FindDialog *ui;

    QString M_Text;
    bool M_Case_Sensitive;
    bool M_Whole_Text;
    bool M_Backwords;

    void init();
    void save();
};

#endif // FINDDIALOG_H
