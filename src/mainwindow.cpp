#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QProgressBar>
#include <QLabel>

#include "mainwindow.hpp"

MainWindow::MainWindow()
{
    QWidget *w = new QWidget;
    setCentralWidget(w);

    QVBoxLayout *layout = new QVBoxLayout;

    input_path_edit = new QLineEdit;
    input_path_edit->setPlaceholderText("Input folder");

    output_path_edit = new QLineEdit;
    output_path_edit->setPlaceholderText("Output folder");

    mask_edit = new QLineEdit;
    mask_edit->setPlaceholderText("File mask ");

    xor_edit = new QLineEdit;
    xor_edit->setPlaceholderText("XOR key (uint64)");

    start_button = new QPushButton("Start");

    progress_bar = new QProgressBar;
    status_label = new QLabel("Ready");

    delete_checkbox = new QCheckBox("Delete input files");

    timer_checkbox = new QCheckBox("Timer mode");

    interval_spin = new QSpinBox;
    interval_spin->setRange(1, 3600);
    interval_spin->setValue(5);
    interval_spin->setSuffix(" sec");

    action_combo = new QComboBox;
    action_combo->addItem("Overwrite");
    action_combo->addItem("Add counter");

    layout->addWidget(input_path_edit);
    layout->addWidget(output_path_edit);
    layout->addWidget(mask_edit);
    layout->addWidget(xor_edit);
    layout->addWidget(start_button);
    layout->addWidget(progress_bar);
    layout->addWidget(status_label);
    layout->addWidget(delete_checkbox);
    layout->addWidget(timer_checkbox);
    layout->addWidget(interval_spin);
    layout->addWidget(action_combo);

    w->setLayout(layout);

    connect(start_button,&QPushButton::clicked,
            this,&MainWindow::start_process);
}

void MainWindow::start_process()
{
    settings.input_path = input_path_edit->text();
    settings.output_path = output_path_edit->text();
    settings.file_mask = mask_edit->text();
    settings.key = xor_edit->text().toULongLong();

    settings.delete_input = delete_checkbox->isChecked();

    settings.timer_mode = timer_checkbox->isChecked();
    settings.scaner_interval = interval_spin->value();

    if (action_combo->currentIndex() == 0)
        settings.action = AppSettings::FileAction::Overwrite;
    else
        settings.action = AppSettings::FileAction::AddCounter;

    thread = new QThread;

    Task *task = new Task(settings);
    task->moveToThread(thread);

    connect(thread,&QThread::started,
            task,&Task::process);

    connect(task,&Task::progress,
            this,&MainWindow::update_progress);

    connect(task,&Task::status,
            this,&MainWindow::update_status);

    connect(task,&Task::finished,
            thread,&QThread::quit);

    thread->start();
}


void MainWindow::update_progress(int p)
{
    progress_bar->setValue(p);
}

void MainWindow::update_status(QString s)
{
    status_label->setText(s);
}