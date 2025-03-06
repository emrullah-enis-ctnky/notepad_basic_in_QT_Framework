#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QTextStream"
#include "QFileDialog"
#include "QList"
#include "QTextEdit"
#include "QMessageBox"
#include "QFileInfo"
#include "QDebug"
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void new_tab_add();
    void new_tab_add(QString file_path);
    void action_save();
    void action_open_file();
    void action_new_file();
    QList<QTextEdit *> text_edit_list;
    QList<QString > file_paths,clear_file_paths;
    void file_control(QString file_path,QString not_saved_text);
    void blank_file_save(QString not_saved_file_text,int index);
    void all_file_save_func();
    void closeEvent(QCloseEvent *event)override;
    ~MainWindow();
private slots:

    void on_tabWidget_tabCloseRequested(int index);


private:
    Ui::MainWindow *ui;

    int active_page=0,clear_file_index=0;
    QString file_name;
    void current_tab();
};
#endif // MAINWINDOW_H
