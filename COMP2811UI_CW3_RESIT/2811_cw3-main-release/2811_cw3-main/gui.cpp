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

status = new Status();

void GUI::createWidgets()  {

    // time display and boiler on/off buttons
    timeDisplay = new QLineEdit("no time yet");

    on  = new QPushButton("on" );
    off = new QPushButton("off");
    out  = new QPushButton("out" );
    sleep = new QPushButton("sleep");
    choice = new QSlider(Qt::Horizontal);
    tartem = new QLCDNumber;
    set = new QPushButton("Set");
    levave = new QTimeEdit;
    comeback = new QTimeEdit;
    sleepshow = new QTimeEdit;
    wake = new QTimeEdit;
}

void GUI::arrangeWidgets() {

    // super-simple layout
    QLayout  *showlayout = new QVBoxLayout();
    QLayout  *turnlayout = new QHBoxLayout();
    QLayout  *tartem_layout = new QHBoxLayout();
    QLayout  *modelayout = new QVBoxLayout();
    QLayout  *mode_layout_out = new QHBoxLayout();
    QLayout  *mode_layout_sleep = new QHBoxLayout();
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

    showlayout -> addWidget(timeDisplay);
    showlayout -> addWidget(mode_part);
    showlayout -> addWidget(settarget);
    showlayout -> addWidget( turn  );
    setLayout(showlayout);

}

void GUI::makeConnections() {

    // on and off buttons control the boiler.
    // Alternately, you may chose to control the boiler using boilerOn/Off in timeChanged.
    connect(on ,  SIGNAL ( released() ), status,  SLOT ( boilerOn () ) );
    connect(off,  SIGNAL ( released() ), status,  SLOT ( boilerOff() ) );
    connect(set,  SIGNAL(released()), this, SLOT(setTargetTemperature()));

}
void GUI::makeConnections(){
    float insideTemperature = status->getInsideTemperature();
    int selectedTemperature = choice->value();

    if (insideTemperature>selectedTemperature){
        status->boilerOn();


    }
}



void GUI::timeChanged(QTime* time) {
    timeDisplay->setText("time: "+time->toString());
}
