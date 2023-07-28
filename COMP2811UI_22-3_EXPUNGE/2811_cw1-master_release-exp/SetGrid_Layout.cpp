#include "SetGrid_Layout.h"
#include "responsive_layout.h"
#include "responsive_label.h"
#include <iostream>

SetGrid_Layout::~SetGrid_Layout()
{
    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}
void SetGrid_Layout::setGeometry(const QRect &rect)
{
    QLayout::setGeometry(rect);
    if(0 == m_list.size())
        return;
    try{
        int S_length = rect.width()/4-1;
//        int SS_lenth = 3*SA_length;
        int S_hei=rect.width()/2;


        for(int i=0;i<m_list.size();i++){
                QLayoutItem *o = m_list.at(i);
                ResponsiveLabel *label = static_cast<ResponsiveLabel *>(o->widget());
                 if (i % 4 == 0){
                    label->setGeometry(rect.x(),rect.y()+S_hei*((i+4)/4 -1)+3,S_length,S_hei);
                }else if(i % 4 == 1){
                        label->setGeometry(rect.x()+S_length,rect.y()+S_hei*((i+3)/4 -1)+3,S_length,S_hei);
                    }
                else if (i % 4 == 2){
                        label->setGeometry(rect.x()+S_hei+2,rect.y()+S_hei*((i+2)/4 -1)+3,S_length,S_hei);
                }
                else if (i % 4 == 3){
                    label->setGeometry(rect.x()+S_hei+S_length+2,rect.y()+S_hei*((i+1)/4 -1)+3,S_length,S_hei);
                }

            }
    }
    catch (std::bad_cast) {
        // bad_case: cast failed on reference...
        qDebug() << "warning, unknown widget class in layout" ;
    }
}

void SetGrid_Layout::addItem(QLayoutItem *item)
{
    m_list.append(item);
}

QSize SetGrid_Layout::sizeHint() const
{
    return QSize();
}

QSize SetGrid_Layout::minimumSize() const
{
    return QSize(280,5000 );
    //add range for scroll
}

int SetGrid_Layout::count() const
{
    return m_list.size();
}

QLayoutItem *SetGrid_Layout::itemAt(int idx) const
{
    return m_list.value(idx);
}

QLayoutItem *SetGrid_Layout::takeAt(int idx)
{
    return idx >= 0 && idx < m_list.size() ? m_list.takeAt(idx) : 0;
}
