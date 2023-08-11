#ifndef GUI_H
#define GUI_H

#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <status.h>

public:
    GUI(Status *status) : status(status) {

        // register to get time and temperature udpates in timeChanged function below
        connect(status, SIGNAL(update(QTime*) ), this, SLOT (timeChanged(QTime*)) );
        createWidgets();
        arrangeWidgets();
        makeConnections();
        setWindowTitle("Boiler GUI");
    }


private:
    void work_time();
    void choice_tem();

