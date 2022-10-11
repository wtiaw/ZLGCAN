#ifndef TOOLPAGE_H
#define TOOLPAGE_H

#include <QWidget>

namespace Ui {
class ToolPage;
}

class ToolPage : public QWidget
{
    Q_OBJECT

public:
    explicit ToolPage(QWidget *parent = nullptr);
    ~ToolPage();

    void InitBase();
    void InitData();

    void InitMessageFrameTypeComboBox();

    void InitMessageId();
    void InitMessageDLC();

    bool ChackDLCData();

public slots:
    void addWidget(const QString &title, QWidget *widget);

    void expand();
    void collapse();

private slots:
    void On_ExpandClicked(bool bClick = false);
    void On_EnableCheckBoxClicked(bool bClick = false);
    void On_SelectCheckBoxClicked(bool bClick = false);

    void On_MessageIDChanged(const QString &arg1);
    void On_MessageDLCChanged(const QString &arg1);

private:
signals:
    void AddSelectedItem(ToolPage* SelectedItem);
    void RemoveSelectedItem(ToolPage* SelectedItem);

private:
    Ui::ToolPage *ui;

    bool m_bIsExpanded;
//    QLabel *m_pLabel;

    class QDrawerCheckBox* DrawerCheckBox;
    class QCheckBox* EnableCheckBox;

    QVector<class DataEdit*> DataEdits;
};

#endif // TOOLPAGE_H
