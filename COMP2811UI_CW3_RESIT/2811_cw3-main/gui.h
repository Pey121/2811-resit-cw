//
// A really bad GUI for controlling the boiler.
//
// You should edit this to create a better GUI.
//
//

#ifndef GUI_H
#define GUI_H

#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QSpinBox>
#include <QSlider>
#include <QLCDNumber>
#include <QTimeEdit>
#include <status.h>
#include <QTimer>
#include <QTime>
#include <QLabel>


class GUI : public QWidget {

    Q_OBJECT

    Status *status;

    QLineEdit* timeDisplay;
    QPushButton*  on;
    QPushButton* off;
    QPushButton* out;
    QPushButton* sleep;
    QPushButton* set;
    QSpinBox* a;
    QSlider* choice;
    QLCDNumber* tartem;
    QTimeEdit* levave;
    QTimeEdit* comeback;
    QTimeEdit* sleepshow;
    QTimeEdit* wake;
    QLabel* timeLabel;
    QTimer* updateTimer;




public:
    GUI(Status *status) : status(status) {

        // register to get time and temperature udpates in timeChanged function below
        connect(status, SIGNAL(update(QTime*) ), this, SLOT (timeChanged(QTime*)) );
        createWidgets();
        arrangeWidgets();
        makeConnections();
        setWindowTitle("Boiler GUI");

    }
    QTimer *temperatureCheckTimer;

    QTimer *temperatureCheckTimer_o;

    QTimer *temperatureCheckTimer_s;


    float targetTemperature;


    bool boilerManuallyOff;

public slots:
    void setTargetTemperature();

    void updateTime();

    void checktem();

    void outtime();

    void outtem();

    void sleeptime();

    void sleeptem();

    void waketem();

    void ctime();


private:

    void createWidgets();

    void arrangeWidgets();

    void makeConnections();




private slots:

    void timeChanged(QTime* time);
};

#endif // GUI_H
