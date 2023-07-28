#include <QtGui>
#include <QList>
#include <QLayout>
#include <QPushButton>

class Simple_layout:public QLayout
{
public:

    Simple_layout():QLayout(){}
    ~Simple_layout();

    // standard functions for a QLayout
    void setGeometry(const QRect &rect);

    void addItem(QLayoutItem *item);

    QLayoutItem *itemAt(int idx) const;
    QLayoutItem *takeAt(int idx);
    QSize sizeHint() const;
    QSize minimumSize() const;
    int count() const;

private:
    QList<QLayoutItem*> m_list;


};
