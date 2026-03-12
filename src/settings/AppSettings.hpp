#ifndef XORENCODER_APPSETTINGS_HPP
#define XORENCODER_APPSETTINGS_HPP

#include <QString>

struct AppSettings {
    enum class FileAction {
        Overwrite,
        AddCounter,
    };

    QString input_path;
    QString output_path;
    QString file_mask;
    bool delete_input;
    FileAction action;
    bool timer_mode;
    std::size_t scaner_interval;
    quint64 key;
};


#endif //XORENCODER_APPSETTINGS_HPP