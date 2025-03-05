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
    active_page=ui->tabWidget->addTab(text,"Yeni dosya");
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

}
void MainWindow::file_edit(){

}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    QWidget *erase_tab=ui->tabWidget->widget(index);
    qDebug()<<erase_tab->objectName();
    if(erase_tab){

        file_paths.removeOne(erase_tab->objectName());
        text_edit_list.removeOne(erase_tab);
        delete erase_tab;
        //ui->tabWidget->removeTab(index);
        qDebug()<<"Çalıştı";

    }
}
void MainWindow::current_tab(){
    //int index = ui->tabWidget->currentIndex();
}
