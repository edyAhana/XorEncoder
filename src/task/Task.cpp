#include "Task.hpp"
#include "FileScanner.hpp"
#include "FileEncoder.hpp"

#include <QFileInfo>
#include <QDir>
#include <QFile>
#include <QDebug>

Task::Task(const AppSettings& s)
    : settings(s) {}

void Task::process() {
    if (settings.timer_mode) {
        timer = new QTimer(this);

        connect(timer, &QTimer::timeout, this, &Task::run_once);

        timer->start(settings.scaner_interval * 1000);

        status("Timer started");
    }
    else {
        run_once();
        emit finished();
    }
}

void Task::run_once() {
    status("Scanning files...");

    auto files = FileScanner::scan(settings.input_path, settings.file_mask);

    for (auto& file : files) {
        QFileInfo info(file);

        QString output = resolve_output(info.fileName());

        emit status("Encoding " + info.fileName());

        FileEncoder::encode(
                file,
                output,
                settings.key,
                [this](int p)
                {
                    emit progress(p);
                });

        if (settings.delete_input) {
            QFile::remove(file);
        }
    }

    emit status("Done");
}

QString Task::resolve_output(const QString& name) {
    QString base = settings.output_path + "/" + name;

    if (settings.action == AppSettings::FileAction::Overwrite)
        return base;

    QFileInfo info(base);

    QString file = info.completeBaseName();
    QString ext = info.suffix();

    int counter = 1;

    QString new_name;

    do {
        new_name = settings.output_path + "/" +
                   file + "_" + QString::number(counter) +
                   "." + ext;

        counter++;

    } while (QFile::exists(new_name));

    return new_name;
}