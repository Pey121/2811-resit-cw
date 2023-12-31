//
// Created by twak on 07/10/2019.
//

#ifndef RESPONSIVELAYOUT_H
#define RESPONSIVELAYOUT_H

#include <QtGui>
#include <QList>
#include <QLayout>

class ResponsiveLayout : public QLayout {
public:
    ResponsiveLayout(): QLayout() {}
    ~ResponsiveLayout();

    // standard functions for a QLayout
    void setGeometry(const QRect &rect);

    void addItem(QLayoutItem *item);
    QSize sizeHint() const;
    QSize minimumSize() const;
    int count() const;
    QLayoutItem *itemAt(int) const;
    QLayoutItem *takeAt(int);
    int rsize;

    int v_len;
    int v_height;

    int h_len;
    int h_height;

private:
    QList<QLayoutItem*> list_;
};
#endif // RESPONSIVELAYOUT_H
