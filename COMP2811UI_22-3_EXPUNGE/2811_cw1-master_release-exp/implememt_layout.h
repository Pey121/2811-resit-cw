#ifndef MYVBOX_LAYOUT_H
#define MYVBOX_LAYOUT_H

#include <QtGui>
#include <QList>
#include <QLayout>
#include <QPushButton>
#include "responsive_label.h"

class implememt_layout : public QLayout
{
public:
    implememt_layout():QLayout(){}
    ~implememt_layout();

    // standard functions for a QLayout
    void setGeometry(const QRect &rect);

    void addItem(QLayoutItem *item);

    int count() const;
    QLayoutItem *itemAt(int idx) const;
    QLayoutItem *takeAt(int idx);
    QSize sizeHint() const;
    QSize minimumSize() const;

private:
    QList<QLayoutItem*> m_list;

};

#endif // MYVBOX_LAYOUT_H
