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
    new_tab_add();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::new_tab_add(){
    QTextEdit *text=new QTextEdit();
    text_edit_list.append(text);
    active_page=ui->tabWidget->addTab(text,"Yeni dosya");
    ui->tabWidget->setCurrentIndex(active_page);
}
void MainWindow::new_tab_add(QString* file_path){
    QTextEdit *text=new QTextEdit();
    text_edit_list.append(text);
    active_page=ui->tabWidget->addTab(text,"Yeni dosya");
    ui->tabWidget->setCurrentIndex(active_page);
    file_paths.append(file_path);
}
void MainWindow::action_new_file(){
    MainWindow::new_tab_add();
}
void MainWindow::action_open_file(){
    QString file_name=QFileDialog::getOpenFileName(this,"Dosya aç","","Desteklenen Dosyalar(*.txt *.cpp *.java *.py)");
    if(file_name.isEmpty()) return;
    else{
        QFile file(file_name);
        if(file.open(QFile::ReadOnly|QFile::Text))
        {
            QTextStream stream(&file);
            QString content=stream.readAll();
            file.close();
            new_tab_add();
            text_edit_list[active_page]->setText(content);
        }
    }

}
void MainWindow::action_save(){

}
void MainWindow::file_edit(){

}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    QWidget *erase_tab=ui->tabWidget->widget(index);
    if(erase_tab){
        QTextEdit *textEdit=erase_tab->findChild<QTextEdit *>();
        if(textEdit){
            text_edit_list.removeOne(textEdit);
            delete textEdit;

        }
        file_paths.remove(index);
        ui->tabWidget->removeTab(index);
        delete erase_tab;
    }
}
