#include "SetHbox_layout.h"


SetHbox_layout::~SetHbox_layout()
{
    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}

void SetHbox_layout::setGeometry(const QRect &rect)
{
    QLayout::setGeometry(rect);

    if(0 == m_list.size())
        return;

    int w_lenth = rect.width()/2;
    for(int i=0;i<m_list.size();i++){
        QLayoutItem *o = m_list.at(i);
        ResponsiveLabel *label = static_cast<ResponsiveLabel *>(o->widget());
            if   (label -> text() == kNavArea ) // headers go at the top
                label -> setGeometry(0+rect.x(),0+rect.y(),rect.width(), rect.height());
            else if(label->text() == kSongsBackward){
                    label->setGeometry(rect.width()/2-w_lenth/2,rect.y(),w_lenth/2,40);
                }else if(label->text() == kSongsForward){
                    label->setGeometry(rect.width()/2,rect.y(),w_lenth/2,40);
                }

    }

}

void SetHbox_layout::addItem(QLayoutItem *item)
{
     m_list.append(item);
}

QSize SetHbox_layout::sizeHint() const
{
    return minimumSize();
}

QSize SetHbox_layout::minimumSize() const
{
    return QSize(80,60 );
}

int SetHbox_layout::count() const
{
    return m_list.size();
}

QLayoutItem *SetHbox_layout::itemAt(int idx) const
{
    return m_list.value(idx);
}

QLayoutItem *SetHbox_layout::takeAt(int idx)
{
    return idx >= 0 && idx < m_list.size() ? m_list.takeAt(idx) : 0;
}
