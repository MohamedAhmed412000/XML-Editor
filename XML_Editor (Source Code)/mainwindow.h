#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QCloseEvent>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <finddialog.h>
#include <QColorDialog>
#include <QFontDialog>
#include <QDesktopServices>
#include "Headers.h"
#include "compress.h"
#include "XML_Data.h"
#include "substring.h"
#include "Tree.h"
#include "format.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionAbout_triggered();
    void on_actionAbout_Qt_triggered();
    void on_textEdit_textChanged();
    void on_actionNew_triggered();
    void on_actionExit_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSave_as_triggered();
    void on_actionCopy_triggered();
    void on_actionCut_triggered();
    void on_actionPaste_triggered();
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();
    void on_actionZoom_in_triggered();
    void on_actionZoom_out_triggered();
    void on_actionSelect_All_triggered();
    void on_actionFind_triggered();
    void on_actionForeground_Color_triggered();
    void on_actionBackground_Color_triggered();
    void on_actionFont_2_triggered();
    void on_actionClose_file_triggered();
    void on_actionSource_Code_triggered();
    void on_actionFormat_file_triggered();
    void on_actionMake_JSON_file_triggered();
    void on_actionBack_to_XML_file_triggered();
    void on_actionCompress_file_triggered();
    void on_actionDecompress_file_triggered();
    void on_actionCheck_file_triggered();
    void on_actionSolve_erorrs_triggered();
    void on_actionErase_Spaces_triggered();

    void on_actionContact_us_triggered();

private:
    Ui::MainWindow *ui;
    QString Tab_Path, Text;
    bool Changed;
    Tree x;

    void New_file();
    void Open_file();
    void Save_file(QString Path);
    void Save_as();
    void Check_save();
    void Front_Color();
    void Back_Color();

    // QWidget interface
protected:
    void closeEvent(QCloseEvent * event) override;
};

#endif // MAINWINDOW_H
