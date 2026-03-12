#ifndef XORENCODER_FILEENCODER_HPP
#define XORENCODER_FILEENCODER_HPP

#include <QString>
#include <functional>

class FileEncoder {
    public:
    static bool encode( const QString& input
                      , const QString& output
                      , quint64 key
                      , std::function<void(int)> porgress);
};


#endif //XORENCODER_FILEENCODER_HPP