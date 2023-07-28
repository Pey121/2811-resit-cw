#include <QtGui>
#include <QList>
#include <QLayout>
#include <QScrollArea>
#include <QPushButton>
#include "responsive_label.h"

class SetGrid_Layout:public QLayout
{
public:
    SetGrid_Layout():QLayout(){}

    ~SetGrid_Layout();

    // standard functions for a QLayout
    void setGeometry(const QRect &rect);
    int count() const;
    QLayoutItem *itemAt(int idx) const;
    QLayoutItem *takeAt(int idx);
    void addItem(QLayoutItem *item);
    QSize sizeHint() const;
    QSize minimumSize() const ;


private:
    QList<QLayoutItem*> m_list;

};
