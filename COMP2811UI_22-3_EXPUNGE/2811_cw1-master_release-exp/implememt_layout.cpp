#include "implememt_layout.h"
#include <iostream>

implememt_layout::~implememt_layout()
{
    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}

void implememt_layout::setGeometry(const QRect &rect)
{
    QLayout::setGeometry(rect);
    int w_hei = rect.height()/10;

    if(0 == m_list.size())
        return;
    if (( rect.width() >rect.height())){
        //horizonal layout

        int h_len1=rect.width()/5;
        QLayoutItem *o = m_list.at(0);
        //responsive layout
        QRect geom(rect.x(),rect.y(), rect.width()/5,rect.height());//  x=1/5, y=y
        o->setGeometry(geom);

        o = m_list.at(1);
        //space of navbar in horizonal layout
        QRect geom2(rect.x()+h_len1+3,rect.y(), h_len1*4,w_hei); // x=4/5, y=1/10
        o->setGeometry(geom2);

        o = m_list.at(2);
        //space of gridlayout
        QRect geom3(rect.x()+h_len1+3,rect.y()+w_hei, h_len1*4,7*w_hei); // x=4/5, y=7/10
        o->setGeometry(geom3);

        o = m_list.at(3);
        //show backward and forward
        QRect geom4(rect.x()+h_len1+3,rect.height()-w_hei-5,  h_len1*4, 2*w_hei); // x=4/5, y=2/10
        o->setGeometry(geom4);

    }else if (rect.height()>rect.width()){
        // vertical layout

        QLayoutItem *o = m_list.at(0);
        // responsive layout

        QRect geom(rect.x(),rect.y(), rect.width(),w_hei*2); // x=x , y=2/10
        o->setGeometry(geom);

        o = m_list.at(1);
        // set zero for void navbar
        QRect geom1(rect.x(),rect.height()-w_hei, 0, 0);  // void
        o->setGeometry(geom1);

        o = m_list.at(2);
        // gridlayout to show song
        QRect geom2(rect.x(),rect.y()+w_hei*2, rect.width(),w_hei*6); //x=x y=6/10
        o->setGeometry(geom2);

        o = m_list.at(3);
        // show backward and forward
        QRect geom3(rect.x(),rect.height()-1.5*w_hei, rect.width(), w_hei*1);// x=x, y=1/10
        o->setGeometry(geom3);

    }

}

void implememt_layout::addItem(QLayoutItem *item)
{
    m_list.append(item);
}

QSize implememt_layout::sizeHint() const
{
    return minimumSize();
}

QSize implememt_layout::minimumSize() const
{
     return QSize(300,500 );
}

int implememt_layout::count() const
{
    return m_list.size();
}

QLayoutItem *implememt_layout::itemAt(int idx) const
{
    return m_list.value(idx);
}

QLayoutItem *implememt_layout::takeAt(int idx)
{
    return idx >= 0 && idx < m_list.size() ? m_list.takeAt(idx) : 0;
}
