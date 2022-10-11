#ifndef QDRAWERCHECKBOX_H
#define QDRAWERCHECKBOX_H

#include <QCheckBox>
#include <QObject>

class QDrawerCheckBox : public QCheckBox
{
    Q_OBJECT
public:
    QDrawerCheckBox();

    static QString EnableQss;

    static QString DisableQss;

protected:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // QDRAWERCHECKBOX_H
