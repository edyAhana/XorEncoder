#include <QFile>
#include <QFileInfo>

#include "Task.hpp"
#include "FileScanner.hpp"
#include "FileEncoder.hpp"

Task::Task(AppSettings settings) : settings(settings) {}

QString Task::generate_output_name(QString name) {
    QString output_name = settings.output_path + "/" + name;

    if (settings.action == AppSettings::FileAction::Overwrite) {
        return output_name;
    }

    std::size_t cnt = 0;
    QString base = output_name;

    while (QFile::exists(output_name)) {
        output_name = base + "_" + QString::number(cnt++);
    }

    return output_name;
}

void Task::process() {
    emit status("Scanning files...");

    QStringList files =
        FileScanner::scan(settings.input_path, settings.file_mask);

    for (QString file : files)
    {
        QFileInfo info(file);

        QString output =
            generate_output_name(info.fileName());

        emit status("Processing " + info.fileName());

        FileEncoder::encode(
            file,
            output,
            settings.key,
            [this](int p)
            {
                emit progress(p);
            }
        );

        if (settings.delete_input)
            QFile::remove(file);
    }

    emit status("Finished");
    emit finished();
}


