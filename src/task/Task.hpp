#ifndef XORENCODER_TASK_HPP
#define XORENCODER_TASK_HPP

#include <QObject>

#include "AppSettings.hpp"

class Task : public QObject {
    Q_OBJECT
private:
    AppSettings settings;
    QString generate_output_name(QString name);
public:
    Task(AppSettings settings);
public slots:
    void process();
signals:
    void progress(int);
    void status(QString);
    void finished();
};


#endif //XORENCODER_TASK_HPP