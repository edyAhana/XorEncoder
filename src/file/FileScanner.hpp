#ifndef XORENCODER_FILESCANNER_HPP
#define XORENCODER_FILESCANNER_HPP

#include <QStringList>

class FileScanner {
public:
    static QStringList scan(const QString& path, const QString& mask);
};


#endif //XORENCODER_FILESCANNER_HPP