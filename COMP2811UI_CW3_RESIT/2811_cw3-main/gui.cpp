 //
 // A really bad GUI for controlling the boiler.
 //
 // You should edit this to create a better GUI.
 //
 //

#include "gui.h"

#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <status.h>
#include <QDateTime>
#include <QTimer>
#include <QTime>
#include <QLabel>



void GUI::createWidgets()  {

    // time display and boiler on/off buttons
    timeDisplay = new QLineEdit("no time yet");
    on  = new QPushButton("on" );
    off = new QPushButton("off");
    out  = new QPushButton("out" );
    sleep = new QPushButton("sleep");
    choice = new QSlider(Qt::Horizontal);
    tartem = new QLCDNumber;
    tartem->display(15);//default number for target number.
    set = new QPushButton("Set");
    levave = new QTimeEdit;
    comeback = new QTimeEdit;
    sleepshow = new QTimeEdit;
    wake = new QTimeEdit;
    timeLabel = new QLabel;
    updateTimer= new QTimer;
}

void GUI::arrangeWidgets() {

    // super-simple layout
    QLayout  *time_tem = new QHBoxLayout();
    QLayout  *showlayout = new QVBoxLayout();
    QLayout  *turnlayout = new QHBoxLayout();
    QLayout  *tartem_layout = new QHBoxLayout();
    QLayout  *modelayout = new QVBoxLayout();
    QLayout  *mode_layout_out = new QHBoxLayout();
    QLayout  *mode_layout_sleep = new QHBoxLayout();

    //add timeline and current Time in the real word
    time_tem -> addWidget(timeDisplay);
    time_tem -> addWidget(timeLabel);

    QWidget * show_w = new QWidget();
    show_w->setLayout(time_tem);
// set mode part (out)
    QWidget * mode_widget_1 = new QWidget();
    mode_layout_out -> addWidget(levave);
    mode_layout_out -> addWidget(out);
    mode_layout_out -> addWidget(comeback);

    mode_widget_1 -> setLayout(mode_layout_out);

// set mode part (sleep)
    QWidget * mode_widget_2 = new QWidget();
    mode_layout_sleep -> addWidget(sleepshow);
    mode_layout_sleep -> addWidget(sleep);
    mode_layout_sleep -> addWidget(wake);

    mode_widget_2 -> setLayout(mode_layout_sleep);

// combine the two widget
    QWidget * mode_part = new QWidget();
    modelayout ->addWidget(mode_widget_1);
    modelayout ->addWidget(mode_widget_2);
    mode_part -> setLayout(modelayout);


// set target part
    choice->setRange(15, 35);

    tartem_layout->addWidget(tartem);
    tartem_layout->addWidget(choice);
    tartem_layout->addWidget (set);
    connect(choice, &QSlider::valueChanged, tartem, QOverload<int>::of(&QLCDNumber::display));
    QWidget * settarget = new QWidget();
    settarget -> setLayout(tartem_layout);

// turn on & off part
    turnlayout ->addWidget(off);
    turnlayout ->addWidget(on);
    QWidget * turn = new QWidget();
    turn ->setLayout(turnlayout);

    showlayout -> addWidget(show_w);
    showlayout -> addWidget(mode_part);
    showlayout -> addWidget(settarget);
    showlayout -> addWidget( turn  );
    setLayout(showlayout);

}

void GUI::setTargetTemperature(){
    QDateTime currentDateTime = QDateTime::currentDateTime();

    if (!temperatureCheckTimer) {
        temperatureCheckTimer = new QTimer(this);
        connect(temperatureCheckTimer, SIGNAL(timeout()), this, SLOT(checktem()));
        temperatureCheckTimer->start(10);  // Check 5 second, adjust as needed
    }

}

void GUI::checktem(){
    float insideTemperature = status->getInsideTemperature();
    int selectedTemperature = choice->value();
    // range of boiler can be adjust
    if (insideTemperature < selectedTemperature) {
        status->boilerOn();
    } else if (insideTemperature > selectedTemperature+2) {
        status->boilerOff();
    }
}

void GUI::makeConnections() {

    // on and off buttons control the boiler.
    // Alternately, you may chose to control the boiler using boilerOn/Off in timeChanged.
    connect(on ,  SIGNAL ( released() ), status,  SLOT ( boilerOn () ) );
    connect(off,  SIGNAL ( released() ), status,  SLOT ( boilerOff() ) );

    // out button & sleep button.
    connect(out,  SIGNAL ( released() ), this,  SLOT ( ctime() ) );
    connect(sleep,  SIGNAL ( released() ), this,  SLOT ( ctime() ) );

    connect(set,  SIGNAL(released()), this, SLOT(setTargetTemperature())); //set target tem
    connect(updateTimer, &QTimer::timeout, this, &GUI::updateTime);//show real word time
    updateTimer->start(1000);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(checkAndAdjustTemperature()));
    timer->start(100);  // Check every 5 minutes

}

void GUI::updateTime() {
    timeLabel->setText(QTime::currentTime().toString("hh:mm")); //format is hh:mm
}

void GUI::ctime() {
    //loops check time
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(outtime()));
    connect(timer, SIGNAL(timeout()), this, SLOT(sleeptime()));
    timer->start(100);

}

void GUI::outtime() {
    QString timeText = timeDisplay->text();
    QTime currentTime = QTime::fromString(timeText, "HH:mm:ss");

    QTime leaveTime = levave->time();
    QTime comebackTime = comeback->time();
    QTime preComebackTime = comebackTime.addSecs(-100);
    //adjust tem by real time
    if (currentTime >= leaveTime && currentTime <= preComebackTime) {
        // The current time is within the range but before the 10 minutes pre-comeback
        status->boilerOff();
    } else if (currentTime > preComebackTime && currentTime <= comebackTime) {
        // The current time is within the 20 minutes pre-comeback range
        if (!temperatureCheckTimer_o) {
            temperatureCheckTimer_o = new QTimer(this);
            connect(temperatureCheckTimer_o, SIGNAL(timeout()), this, SLOT(outtem()));
            temperatureCheckTimer_o->start(10);  // Check every second, adjust as needed
        }
    }
}


void GUI::outtem() {
    float insideTemperature = status->getInsideTemperature();
    int h_tem=30;
    // range of boiler can be adjust
    if (insideTemperature < h_tem) {
        status->boilerOn();
    } else if (insideTemperature > h_tem+2) {
        status->boilerOff();
    }



}

void GUI::sleeptime(){

    QTime sleept = sleepshow->time();
    QTime waket = wake->time();
    QTime wake = waket.addSecs(-20);  // 20 minutes before comeback
    QTime currentTime = QTime::currentTime();
    if (currentTime >= sleept && currentTime < wake) {
        sleeptem();
    } else if (currentTime >= wake && currentTime <= waket) {
        waketem();
    }
}

void GUI::sleeptem(){
    int c_tem=15;

    float insideTemperature = status->getInsideTemperature();
    // range of boiler can be adjust
    if (insideTemperature < c_tem) {
        status->boilerOn();
    } else if (insideTemperature > c_tem+2) {
        status->boilerOff();
    }

}

void GUI::waketem(){
    int w_tem=25;
    float insideTemperature = status->getInsideTemperature();
    if (insideTemperature < w_tem) {
        status->boilerOn();
    } else if (insideTemperature > w_tem+2) {
        status->boilerOff();
    }
}




void GUI::timeChanged(QTime* time) {
    timeDisplay->setText("time: "+time->toString());
}
