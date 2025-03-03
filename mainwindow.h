#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QTextStream"
#include "QFileDialog"
#include "QList"
#include "QTextEdit"
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
    void new_tab_add(QString *file_path);
    void action_save();
    void action_open_file();
    void action_new_file();

    ~MainWindow();
private slots:
    void file_edit();
    void on_tabWidget_tabCloseRequested(int index);

private:
    Ui::MainWindow *ui;
    QList<QTextEdit *> text_edit_list;
    QList<QString *> file_paths;
    int active_page=0;
    QString file_name;
};
#endif // MAINWINDOW_H
