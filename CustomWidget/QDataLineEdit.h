#ifndef QDATALINEEDIT_H
#define QDATALINEEDIT_H

#include <QLineEdit>

class QDataLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    QDataLineEdit();

    void SetNextEdit(QDataLineEdit* InEdit){ NextEdit = InEdit; }
    QDataLineEdit* GetNextEdit() const { return NextEdit; }

private:
    QDataLineEdit* NextEdit = nullptr;
};

#endif // QDATALINEEDIT_H
