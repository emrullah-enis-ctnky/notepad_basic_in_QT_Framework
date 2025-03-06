#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->removeTab(1);
    ui->tabWidget->removeTab(0);
    connect(ui->actionNewFile,&QAction::triggered,this,&MainWindow::action_new_file);
    connect(ui->actionOpenFile,&QAction::triggered,this,&MainWindow::action_open_file);
    connect(ui->actionSave,&QAction::triggered,this,&MainWindow::action_save);
    connect(ui->tabWidget,&QTabWidget::currentChanged,this,&MainWindow::current_tab);
    connect(ui->actionAllFileSave,&QAction::triggered,this,&MainWindow::all_file_save_func);
    new_tab_add();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::new_tab_add(){
    clear_file_index++;
    QTextEdit *text=new QTextEdit(this);
    text_edit_list.append(text);
    text->setObjectName("new_file"+QString::number(clear_file_index));
    active_page=ui->tabWidget->addTab(text,"Yeni dosya"+QString::number(clear_file_index));
    ui->tabWidget->setCurrentIndex(active_page);
    file_paths.append(text->objectName());

}
void MainWindow::new_tab_add(QString file_path){
    if(file_paths.contains(file_path)){
        QMessageBox::warning(this,"Uyarı","Dosya zaten açık");
        return;
    }

    QTextEdit *text=new QTextEdit(this);
    text_edit_list.append(text);
    file_paths.append(file_path);
    active_page=ui->tabWidget->addTab(text,file_path);
    ui->tabWidget->setCurrentIndex(active_page);
    QFileInfo file_info(file_path);
    QString file_name=file_info.fileName();
    ui->tabWidget->setTabText(active_page,file_name);
    QFile file(file_path);
    if(file.open(QFile::ReadOnly|QFile::Text))
    {
        QTextStream stream(&file);
        QString content=stream.readAll();
        file.close();
        text->setText(content);
        text->setObjectName(file_path);

    }
}
void MainWindow::action_new_file(){
    MainWindow::new_tab_add();
}
void MainWindow::action_open_file(){
    QString file_name=QFileDialog::getOpenFileName(this,"Dosya aç","","Desteklenen Dosyalar(*.txt *.cpp *.java *.py)");
    if(file_name.isEmpty()) return;
    else{
        if (file_paths.contains(file_name)) {
            QMessageBox::warning(this, "Uyarı", "Bu dosya zaten açık!");
            return;
        }
        new_tab_add(file_name);
    }

}
void MainWindow::action_save(){
    QString not_save_text=text_edit_list[ui->tabWidget->currentIndex()]->toPlainText();
    QString file_path=text_edit_list[ui->tabWidget->currentIndex()]->objectName();
    if(QFile::exists(file_path)){
        file_control(file_path,not_save_text);
    }
    else {
        blank_file_save(not_save_text,ui->tabWidget->currentIndex());
    }
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    QWidget *erase_tab=ui->tabWidget->widget(index);
    qDebug()<<erase_tab->objectName();
    if(erase_tab){

        file_paths.removeOne(erase_tab->objectName());
        text_edit_list.removeOne(erase_tab);
        delete erase_tab;
        qDebug()<<"Çalıştı";

    }
}
void MainWindow::current_tab(){
    //int index = ui->tabWidget->currentIndex();
}
void MainWindow::file_control(QString file_path,QString not_saved_text){
    QFile file(file_path);
    if(file.open(QFile::ReadWrite|QFile::Text))
    {

        QTextStream stream(&file);
        QString content=stream.readAll();
        file.resize(0);
        if(content==not_saved_text){
            ui->statusbar->showMessage("Dosya değiştirilmedi!",5000);
        }
        else{
            stream<<not_saved_text;
            ui->statusbar->showMessage("Dosya kaydedildi!",5000);
        }
        file.close();
    }
}
void MainWindow::blank_file_save(QString not_saved_file_text,int index){
    QString file_name=QFileDialog::getSaveFileName(this,"Dosya kaydet","blank.txt");
    if(file_name.isEmpty()){
        QMessageBox::critical(this,"Hata","Hiçbir dosya seçilmedi!");
        return;
    }
    QFile file(file_name);
    if(file.open(QIODevice::WriteOnly|QIODevice::Text)){
        QTextStream out(&file);
        out<<not_saved_file_text;
        file.close();
        ui->statusbar->showMessage("Dosya Kaydedildi!",5000);
        text_edit_list[index]->setObjectName(file_name);
        file_paths[index]=file_name;
        QFileInfo file_info(file_name);
        QString file_base_name=file_info.fileName();
        ui->tabWidget->setTabText(active_page,file_base_name);
    }
    else{
        QMessageBox::critical(this,"Hata","Dosya Kaydedilemedi!");
    }
}
void MainWindow::all_file_save_func(){
    for (int i = 0; i < text_edit_list.size(); i++) {
        QString not_save_text=text_edit_list[i]->toPlainText();
        QString file_path=text_edit_list[i]->objectName();
        if(QFile::exists(file_path)){
            file_control(file_path,not_save_text);
        }
        else {
            blank_file_save(not_save_text,i);
        }
    }


}

void MainWindow::closeEvent(QCloseEvent *event)
{
    all_file_save_func();
}

