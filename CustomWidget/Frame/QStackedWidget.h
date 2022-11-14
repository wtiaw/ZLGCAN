#ifndef QSTACKEDWIDGET_H
#define QSTACKEDWIDGET_H

#include <QWidget>

namespace Ui
{
    class QStackedWidget;
}

class QStackedWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QStackedWidget(QWidget* parent = nullptr);
    ~QStackedWidget();

    int GetCurrentActiveIndex() { return CurrentActiveIndex; }
    void SetActiveIndex(int index);

    void AddWidget(QWidget* InWidget);

    int GetWidgetNum() { return Widgets.length(); }

    template <class type>
    type* GetCurrentWidget();

private:
    Ui::QStackedWidget* ui;

    int CurrentActiveIndex = 0;

    QVector<QWidget*> Widgets;
};

template <class type>
type* QStackedWidget::GetCurrentWidget()
{
    return qobject_cast<type>(Widgets[CurrentActiveIndex]);
}

#endif // QSTACKEDWIDGET_H
