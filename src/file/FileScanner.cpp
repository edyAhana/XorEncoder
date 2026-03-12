#include "FileScanner.hpp"
#include <QDir>

QStringList FileScanner::scan(const QString& path, const QString& mask) {
    QDir dir(path);

    QStringList filters;
    filters << mask;

    QFileInfoList info = dir.entryInfoList(filters, QDir::Files);

    QStringList file_list;

    for (const auto& file : info) {
        file_list << file.absoluteFilePath();
    }

    return file_list;
}
