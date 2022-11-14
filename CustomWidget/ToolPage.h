#ifndef TOOLPAGE_H
#define TOOLPAGE_H

#include <QWidget>

namespace Ui
{
    class ToolPage;
}

class ToolPage : public QWidget
{
    Q_OBJECT

public:
    explicit ToolPage(QWidget* parent = nullptr);
    ~ToolPage() override;

    void InitBase();
    void InitData();

    void InitMessageFrameTypeComboBox() const;

    void InitMessageId();
    void InitMessageDLC();

    bool CheckDLCData() const;

public slots:
    void AddWidget(const QString& title, QWidget* widget) const;

    void expand() const;
    void collapse() const;

private slots:
    void On_ExpandClicked(bool bClick = false) const;
    void On_EnableCheckBoxClicked(bool bClick = false) const;
    void On_SelectCheckBoxClicked(bool bClick = false);

    void On_MessageIDChanged(const QString& arg1) const;
    void On_MessageDLCChanged(const QString& arg1);

private:
signals:
    void AddSelectedItem(ToolPage* SelectedItem);
    void RemoveSelectedItem(ToolPage* SelectedItem);

private:
    Ui::ToolPage* ui;

    bool m_bIsExpanded;
    //    QLabel *m_pLabel;

    class QDrawerCheckBox* DrawerCheckBox;
    class QCheckBox* EnableCheckBox;

    QVector<class DataEdit*> DataEdits;
};

#endif // TOOLPAGE_H
