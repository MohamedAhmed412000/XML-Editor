#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <xmlsyntaxhighlighter.h>
#include <QTextEdit>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    x.setRoot(nullptr);
    ui->setupUi(this);
    New_file();
    QTextEdit* editor = ui->textEdit;
    BasicXMLSyntaxHighlighter * highlighter = new BasicXMLSyntaxHighlighter(editor);
    Q_UNUSED(highlighter);
    ui->textEdit->setText(ui->textEdit->toPlainText());
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_actionAbout_triggered(){
    QMessageBox::information(this, "About us", "-- Team Number # --\n 1) Mohamed Fathy\n 2) Mohamed Ahmed\n 3) Mohamed Ali\n 4) Mostafa Mohsen");
}

void MainWindow::on_actionAbout_Qt_triggered(){
    QApplication::aboutQt();
}

void MainWindow::on_textEdit_textChanged(){
    Changed = true;
}

void MainWindow::on_actionNew_triggered(){
    Check_save();
    New_file();
}

void MainWindow::on_actionOpen_triggered(){
    Check_save();
    Open_file();
}

void MainWindow::on_actionSave_triggered(){
    Save_file(Tab_Path);
}

void MainWindow::on_actionSave_as_triggered(){
    Save_as();
}

void MainWindow::New_file(){
    ui->textEdit->clear();
    ui->statusBar->showMessage("New File");
    Tab_Path = "";
    Text = "";
    Changed = false;
    ui->actionBack_to_XML_file->setEnabled(false);
    ui->actionMake_JSON_file->setEnabled(true);
}

void MainWindow::Open_file(){
    QString Path = QFileDialog::getOpenFileName(this, tr("Open File"));
    if(Path.isEmpty()) return;

    QFile File(Path);
    if(!File.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::critical(this, "Error", File.errorString());
        return;
    }

    QTextStream in(&File);
    Text = in.readAll();

    int index;
    for(int i = 0; i < Path.length(); i++){
        if(Path[i] == '/')
            index = i;
    }
    QString Name = Path.mid(index+1, Path.length()-index-1);
    QFileInfo fi(Path);                     // get the data of file
    QString Extension = fi.suffix();        // get the extension of the file
    if(Extension == "xml"){
        ui->textEdit->setText(Text);
        ui->statusBar->showMessage("Open File - " + Name);
    }
    else
        QMessageBox::critical(this, "Erorr", "File Type must be XML");

    File.close();
    Tab_Path = Path;
    Changed = false;
    ui->actionBack_to_XML_file->setEnabled(false);
    ui->actionMake_JSON_file->setEnabled(true);
}

void MainWindow::Save_file(QString Path){
    if(Path.isEmpty()){
        Save_as();
        return;
    }

    QFile File(Path);
    if(!File.open(QIODevice::WriteOnly | QFile::Text)){
        QMessageBox::critical(this, "Error", File.errorString());
        ui->statusBar->showMessage("Error, can't save the file.");
        Save_as();
        return;
    }

    QTextStream out(&File);
    out << ui->textEdit->toPlainText();
    File.close();

    Tab_Path = Path;
    ui->statusBar->showMessage("Saved at" + Path);
}

void MainWindow::Save_as(){
    if(ui->actionMake_JSON_file->isEnabled() == true){
        QString Path = QFileDialog::getSaveFileName(this, tr("Save File as"), "Untitled.xml",
                                                    tr("XML File (*.xml);;All Files (*)"));
        if(Path.isEmpty()) return;
        if(!Path.endsWith(".xml"))
            Path.append(".xml");
        Save_file(Path);
    }
    else{
        QString Path = QFileDialog::getSaveFileName(this, tr("Save File as"), "Untitled.json",
                                                    tr("JSON File (*.json);;All Files (*)"));
        if(Path.isEmpty()) return;
        if(!Path.endsWith(".json"))
            Path.append(".json");
        Save_file(Path);
    }
}

void MainWindow::Check_save(){
    if(!Changed) return;
    QMessageBox::StandardButton value = QMessageBox::question(this, "Save File",
                               "Do you want to save the file before closing it?");
    if(value != QMessageBox::StandardButton::Yes) return;
    if(Tab_Path.isEmpty())
        Save_as();
    else
        Save_file(Tab_Path);
}

void MainWindow::Front_Color(){
    QColor current = ui->textEdit->currentCharFormat().foreground().color();
    QColor color = QColorDialog::getColor(current, this, "Select a color");
    ui->textEdit->setTextColor(color);
    Changed = true;
}

void MainWindow::Back_Color()
{
    QColor current = ui->textEdit->currentCharFormat().background().color();
    QColor color = QColorDialog::getColor(current, this, "Select a color");
    ui->textEdit->setTextBackgroundColor(color);
    Changed = true;
}

void MainWindow::closeEvent(QCloseEvent * event){
    event->accept();
}

void MainWindow::on_actionExit_triggered(){
    QApplication::quit();
}

void MainWindow::on_actionCopy_triggered(){
    ui->textEdit->copy();
}

void MainWindow::on_actionCut_triggered(){
    ui->textEdit->cut();
}

void MainWindow::on_actionPaste_triggered(){
    ui->textEdit->paste();
}

void MainWindow::on_actionUndo_triggered(){
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered(){
    ui->textEdit->redo();
}

void MainWindow::on_actionZoom_in_triggered(){
    ui->textEdit->zoomIn(1);
}

void MainWindow::on_actionZoom_out_triggered(){
    ui->textEdit->zoomOut(1);
}

void MainWindow::on_actionSelect_All_triggered(){
    ui->textEdit->selectAll();
}

void MainWindow::on_actionFind_triggered(){
    FindDialog* dlg = new FindDialog(this);
    if(!dlg->exec()) return;

    QTextDocument::FindFlags flags;
    if(dlg->getM_Case_Sensitive()) flags = flags | QTextDocument::FindFlag::FindCaseSensitively;
    if(dlg->getM_Whole_Text()) flags = flags | QTextDocument::FindFlag::FindWholeWords;
    if(dlg->getM_Backwords()) flags = flags | QTextDocument::FindFlag::FindBackward;

    bool value = ui->textEdit->find(dlg->getM_Text(), flags);
    if(!value) QMessageBox::information(this, "Not Found", "Not able to find: "+dlg->getM_Text());

}

void MainWindow::on_actionForeground_Color_triggered(){
    Front_Color();
}

void MainWindow::on_actionBackground_Color_triggered(){
    Back_Color();
}

void MainWindow::on_actionFont_2_triggered(){
    bool ok;
    QFont font = QFontDialog::getFont(&ok, ui->textEdit->currentFont(), this, "Choose a Font");
    if(ok) ui->textEdit->setCurrentFont(font);

}

void MainWindow::on_actionClose_file_triggered(){
    Check_save();
    New_file();
}

void MainWindow::on_actionSource_Code_triggered()
{
    QString link = "https://github.com/mohamedali1252/XML-Editor/tree/XML-Editor";
    QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::on_actionFormat_file_triggered(){
    //editor->setPlainText(ui->textEdit->toPlainText());
    vector<string> XML_Strings, Right_XML;
    vector<int> Errors;
    string str ="";
    QString str1 = ui->textEdit->toPlainText();
    if (str1 != ""){
        string text = str1.toUtf8().constData();
        XML_Strings = XML_Parsing_Data(text);
        checking_errors(XML_Strings, Right_XML, Errors);
        str = formatting(Right_XML);
        ui->textEdit->setPlainText(QString::fromStdString(str));
    }
    else    ui->statusBar->showMessage("The file is empty");
}

void MainWindow::on_actionMake_JSON_file_triggered(){
    ui->actionBack_to_XML_file->setEnabled(true);
    ui->actionMake_JSON_file->setEnabled(false);

    vector<string> XML_Strings, Right_XML;
    vector<int> Errors;
    Tree x;
    QString str1 = ui->textEdit->toPlainText();
    if (str1 != ""){
        string text = str1.toUtf8().constData();
        XML_Strings = XML_Parsing_Data(text);
        checking_errors(XML_Strings, Right_XML, Errors);
        string str = "";
        // Errors Position in Screen
        x.insert(Right_XML, Errors);
        this->x = x;
        str = x.xml2json();
        ui->textEdit->setPlainText(QString::fromStdString(str));
    }
    else
        ui->statusBar->showMessage("The file is empty");
}

void MainWindow::on_actionBack_to_XML_file_triggered()
{
    ui->actionBack_to_XML_file->setEnabled(false);
    ui->actionMake_JSON_file->setEnabled(true);
    string str = x.Pre_Order();
    ui->textEdit->setPlainText(QString::fromStdString(str));
}

void MainWindow::on_actionCompress_file_triggered(){
    QString Path = QFileDialog::getOpenFileName(this, tr("Open XML File to compress"));
    if(Path.isEmpty()) return;

    QFile File(Path);
    if(!File.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::critical(this, "Error", File.errorString());
        return;
    }

    QTextStream in(&File);
    Text = in.readAll();

    int index;
    for(int i = 0; i < Path.length(); i++){
        if(Path[i] == '/')
            index = i;
    }
    QString Name = Path.mid(index+1, Path.length()-index-1);
    QString Path1 = Path.mid(0, index+1);
    QFileInfo fi(Path);                     // get the data of file
    QString Extension = fi.suffix();        // get the extension of the file
    if(Extension == "xml"){
        string str = Text.toUtf8().constData();
        string File_Name = Name.toUtf8().constData();
        string File_Path = Path1.toUtf8().constData();
        vector<int> a = encoding(str);
        writeFile(File_Path+File_Name.substr(0, File_Name.length()-4)+".dat", a);
    }
    else
        QMessageBox::critical(this, "Erorr", "File Type must be XML");

    File.close();
}

void MainWindow::on_actionDecompress_file_triggered()
{
    QString Path = QFileDialog::getOpenFileName(this, tr("Open Compressed File"));
    if(Path.isEmpty()) return;

    QFile File(Path);
    if(!File.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::critical(this, "Error", File.errorString());
        return;
    }

    QTextStream in(&File);
    Text = in.readAll();

    int index;
    for(int i = 0; i < Path.length(); i++){
        if(Path[i] == '/')
            index = i;
    }
    string File_Path = Path.toUtf8().constData();;
    QFileInfo fi(Path);                     // get the data of file
    QString Extension = fi.suffix();        // get the extension of the file
    if(Extension == "dat"){
        vector<int>b;
        b = readFile(File_Path);			//read encoded numbers from .dat file to decode
        b.pop_back();						//delete end of file
        string str = decoding(b);				//decode to original file
        QString qstr = QString::fromStdString(str);
        Check_save();
        New_file();
        ui->textEdit->setText(qstr);
    }
    else
        QMessageBox::critical(this, "Erorr", "File Type must be dat");

    File.close();
}

void MainWindow::on_actionCheck_file_triggered()
{
    vector<string> XML_Strings, Right_XML;
    vector<int> Errors;
    QString str = ui->textEdit->toPlainText();
    if (str != ""){
        string text = str.toUtf8().constData();
        XML_Strings = XML_Parsing_Data(text);
        string error = "\t<<==== ERROR\t";
        int e = checking_errors(XML_Strings, Right_XML, Errors);
        if (e){
            // Errors Position in Screen
            QString str = "";
            string New = "";
            for(unsigned int i = 0; i < Errors.size(); i++){
                str += QString::fromStdString(to_string(Errors[i])) + ", ";
            }
            ui->statusBar->showMessage("     Number of errors = " +
                                       QString::fromStdString(to_string(e))+ ", Their Posistions: " + str);
            int count = 0;
            for(unsigned int i = 0; i < XML_Strings.size(); i++){
                if(Get_Type(XML_Strings[i]) == 'O'){
                    New=New+XML_Strings[i];
                    if(i == Errors[count]){
                        count++;
                        New=New+error;
                    }
                    New=New+"\n";
                }
                else if(Get_Type(XML_Strings[i]) == 'V'){
                    New=New+XML_Strings[i];
                    if(i == Errors[count]){
                        count++;
                        New=New+error;
                    }
                    New=New+"\n";
                }
                else if(Get_Type(XML_Strings[i]) == 'C'){
                    New=New+XML_Strings[i];
                    if(i == Errors[count]){
                        count++;
                        New=New+error;
                    }
                    New=New+"\n";
                }
            }
            ui->textEdit->setText(QString::fromStdString(New));
        }
        else
            ui->statusBar->showMessage("No errors exist in the file");
    }
    else
        ui->statusBar->showMessage("The file is empty");
}

void MainWindow::on_actionSolve_erorrs_triggered()
{
    vector<string> XML_Strings, Right_XML;
    vector<int> Errors;
    Tree x;
    QString str = ui->textEdit->toPlainText();
    if (str != ""){
        string text = str.toUtf8().constData();
        XML_Strings = XML_Parsing_Data(text);
        int e = checking_errors(XML_Strings, Right_XML, Errors);
        if (e){
            string str = "";
            // Errors Position in Screen
            x.insert(Right_XML, Errors);
            // Pre-Order Traverse
            str = x.Pre_Order();
            ui->textEdit->setPlainText(QString::fromStdString(str));
        }
        else
            ui->statusBar->showMessage("No errors exist in the file");
    }
    else{
        ui->statusBar->showMessage("The file is empty");
    }

}

void MainWindow::on_actionErase_Spaces_triggered()
{
    QString str = ui->textEdit->toPlainText();
    string text = str.toUtf8().constData();
    if (str != ""){
        string str1 = "";
        for(unsigned int i = 0; i < text.length(); i++){
            if(text[i] == '<'){
                while(text[i] != '>'){
                    str1 += text[i];
                    i++;
                }
                str1 += text[i];
            }
            else if((isData(text[i+1]) || isData(text[i-1]))&&(text[i] != '\n' && text[i] != '\t')) str1 += text[i];
            else if(text[i] != ' ' && text[i] != '\n' && text[i] != '\t')
                str1 += text[i];
        }
        ui->textEdit->setPlainText(QString::fromStdString(str1));
    }
    else    ui->statusBar->showMessage("The file is empty");
}

void MainWindow::on_actionContact_us_triggered()
{
    QString link = "https://drive.google.com/drive/folders/1KBASEWOv9CdzBVsHznHrrL8zxu0qq3_u?usp=sharing";
    QDesktopServices::openUrl(QUrl(link));
}
