#ifndef DATAEDIT_H
#define DATAEDIT_H

#include <QLineEdit>

class DataEdit : public QLineEdit
{
    Q_OBJECT
public:
    DataEdit();

    void SetNextEdit(DataEdit* InEdit){ NextEdit = InEdit; }
    DataEdit* GetNextEdit() const { return NextEdit; }

protected:
    virtual void focusInEvent(QFocusEvent *e);

private slots:
    void On_TextChanged(const QString &arg1);
    void On_editingFinished();

private:
    DataEdit* NextEdit = nullptr;
};

#endif // DATAEDIT_H
