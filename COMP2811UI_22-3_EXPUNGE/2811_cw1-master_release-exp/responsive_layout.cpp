//
// Created by twak on 07/10/2019.
//

#include "responsive_layout.h"
#include "responsive_label.h"
#include <iostream>

//using namespace std;

// you should probably make extensive changes to this function
void ResponsiveLayout::setGeometry(const QRect &r /* our layout should always fit inside r */ ) {

    QLayout::setGeometry(r);

    // for all the Widgets added in ResponsiveWindow.cpp
    for (int i = 0; i < list_.size(); i++) {

        QLayoutItem *o = list_.at(i);
        try {
            // cast the widget to one of our responsive labels
            ResponsiveLabel *label = static_cast<ResponsiveLabel *>(o->widget());

            if (label == NULL) // null: cast failed on pointer
                std::cout << "warning, unknown widget class in layout" << std::endl;

            if( r.width()<r.height()){
                //horizonal layout
                v_len=r.width()/5;
                v_height=r.height()/10;
                if (label -> text() == kNavArea ) // headers go at the top
                    label -> setGeometry(0+v_len,0+r.y(),4*r.width(), 0);

                if (label -> text() == KProfilePicture )
                    label -> setGeometry(0+r.x(),0+r.y(),r.width(), v_height*4);

                if (label -> text() == kHomeLink )
                    label -> setGeometry(0+r.x(),0+v_height*4,r.width(), v_height);


                if (label -> text() == kMyProfile )
                    label -> setGeometry(0+r.x(),0+v_height*5,r.width(), v_height);

                if (label -> text() == kFavoriteTrack )
                    label -> setGeometry(0+r.x(),0+v_height*6,r.width(), v_height);

                if (label -> text() == kEvents )
                    label -> setGeometry(0+r.x(),0+v_height*7,r.width(), v_height);
                if (label -> text() == kHistory )
                    label -> setGeometry(0+r.x(),0+v_height*8,r.width(), v_height);
                if (label -> text() == kExit )
                    label -> setGeometry(0+r.x(),0+v_height*9,r.width(), v_height);


            }else if (r.width()>3*r.height()){
                //vertical layout (large)
                h_len=r.width()/7;
                h_height=r.height()/2;

                if (label -> text() == kNavArea ) // headers go at the top
                    label -> setGeometry(0,0+r.y(),r.width(), 40);

                if (label -> text() == kHomeLink )
                    label -> setGeometry(0+r.x(),0+40,h_len, h_height);

                if (label -> text() == KProfilePicture )
                    label -> setGeometry(0+h_len,0+40,h_len, h_height);

                if (label -> text() == kMyProfile )
                    label -> setGeometry(0+h_len*2,0+40,h_len, h_height);

                if (label -> text() == kFavoriteTrack )
                    label -> setGeometry(0+h_len*3,0+40,h_len, h_height);

                if (label -> text() == kEvents )
                    label -> setGeometry(0+h_len*4,0+40,h_len, h_height);
                if (label -> text() == kHistory )
                    label -> setGeometry(0+h_len*5,0+40,h_len, h_height);
                if (label -> text() == kExit )
                    label -> setGeometry(0+h_len*6,0+40,h_len, h_height);

            }
            else {
                //vertical layout (small)
                h_len=r.width()/7;
                h_height=r.height()/2;

                if (label -> text() == kMyProfile )
                    label -> setGeometry(0,0,h_len*2, 40);

                if (label -> text() == KProfilePicture )
                    label -> setGeometry(0+h_len*2,0,h_len*3, 40);

                if (label -> text() == kFavoriteTrack )
                    label -> setGeometry(0+h_len*5,0,h_len*2, 40);

                if (label -> text() == kNavArea ) // headers go at the top
                    label -> setGeometry(0+h_len*2,0+40,3*h_len, h_height);

                if (label -> text() == kHomeLink )
                    label -> setGeometry(0+r.x(),0+40,h_len, h_height);

                if (label -> text() == kEvents )
                    label -> setGeometry(0+h_len,0+40,h_len, h_height);

                if (label -> text() == kHistory )
                    label -> setGeometry(0+h_len*5,0+40,h_len, h_height);
                if (label -> text() == kExit )
                    label -> setGeometry(0+h_len*6,0+40,h_len, h_height);

            }
        }
        catch (std::bad_cast) {
            // bad_case: cast failed on reference...
            std::cout << "warning, unknown widget class in layout" << std::endl;
        }
    }
}

// following methods provide a trivial list-based implementation of the QLayout class
int ResponsiveLayout::count() const {
    return list_.size();
}

QLayoutItem *ResponsiveLayout::itemAt(int idx) const {
    return list_.value(idx);
}

QLayoutItem *ResponsiveLayout::takeAt(int idx) {
    return idx >= 0 && idx < list_.size() ? list_.takeAt(idx) : 0;
}

void ResponsiveLayout::addItem(QLayoutItem *item) {
    list_.append(item);
}

QSize ResponsiveLayout::sizeHint() const {
    return minimumSize();
}

QSize ResponsiveLayout::minimumSize() const {
    return QSize(320,320);
}

ResponsiveLayout::~ResponsiveLayout() {
    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}
