#ifndef TOOLBOX_H
#define TOOLBOX_H

#include "qboxlayout.h"
#include <QWidget>

namespace Ui {
class ToolBox;
}

class ToolBox : public QWidget
{
    Q_OBJECT

public:
    explicit ToolBox(QWidget *parent = nullptr);
    ~ToolBox();

    void AddItem();

    void RemoveItem(class ToolPage* RemovedItem);

private:
    Ui::ToolBox *ui;

    QVBoxLayout *m_pContentVBoxLayout;
};

#endif // TOOLBOX_H
