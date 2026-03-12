#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QTimer>

#include "AppSettings.hpp"
#include "Task.hpp"

QT_BEGIN_NAMESPACE
class QLineEdit;
class QPushButton;
class QProgressBar;
class QLabel;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private slots:
    void start_process();
    void update_progress(int);
    void update_status(QString);

private:
    AppSettings settings;

    QLineEdit *mask_edit;
    QLineEdit *input_path_edit;
    QLineEdit *output_path_edit;
    QLineEdit *xor_edit;

    QPushButton *start_button;

    QProgressBar *progress_bar;
    QLabel *status_label;

    QThread *thread;
};

#endif //XORENCODER_MAINWINDOW_HPP