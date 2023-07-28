//
// Created by twak on 14/10/2019.
//

#include "responsive_window.h"
#include "implememt_layout.h"
#include "responsive_layout.h"
#include "screenshot.h"
#include <iostream>
#include <QApplication>
#include "SetGrid_Layout.h"
#include "Simple_layout.h"
#include "implememt_layout.h"


ResponsiveWindow::ResponsiveWindow() {

    setWindowTitle("2811: Coursework 1");
//    setMinimumSize(320, 320);
//    setMaximumSize(1280, 720);

    createWidgets();
}

void ResponsiveWindow::createWidgets() {
        ResponsiveLayout * fl = new ResponsiveLayout();

        // add all the widgets we need to demonstrate all layouts
        fl->addWidget(new ResponsiveLabel(kNavArea));
        fl->addWidget(new ResponsiveLabel(KProfilePicture));
        fl->addWidget(new ResponsiveLabel(kHomeLink));
        fl->addWidget(new ResponsiveLabel(kMyProfile));
        fl->addWidget(new ResponsiveLabel(kFavoriteTrack));
        fl->addWidget(new ResponsiveLabel(kEvents));
        fl->addWidget(new ResponsiveLabel(kHistory));
        fl->addWidget(new ResponsiveLabel(kExit));
        firstw =new QWidget();
        firstw ->setLayout(fl);

       Simple_layout *horinav = new Simple_layout();
        //nav area for horzion
        horinav->addWidget(new ResponsiveLabel(kNavArea));
       navw =new QWidget();
        navw->setLayout(horinav);

     //show the songs
     s_scol = new QScrollArea(this);
     secondw = new QWidget();
     SetGrid_Layout *song_display = new SetGrid_Layout();
     for(int i=0;i<17;i++){//
         song_display->addWidget(new ResponsiveLabel(kSongArt));
         song_display->addWidget(new ResponsiveLabel(kSongText));
     }
     secondw->setLayout(song_display);
     s_scol->setWidget(secondw);
     s_scol->setWidgetResizable(true);
     s_scol->setMinimumHeight(60);


     Simple_layout *ward = new Simple_layout;
     thirdw=new QWidget();//backward&forward area
     ward->addWidget(new ResponsiveLabel(kSongsBackward));
     ward->addWidget(new ResponsiveLabel(kSongsForward));
     thirdw->setLayout(ward);

    implememt_layout *show = new implememt_layout;
     show->addWidget(firstw);
     show->addWidget(navw);
     show->addWidget(s_scol);
     show->addWidget(thirdw);
    setLayout(show);

}


