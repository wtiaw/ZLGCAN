#ifndef DATADISPLAYWIDGET_H
#define DATADISPLAYWIDGET_H

#include <QWidget>
#include <QtUiPlugin/QDesignerExportWidget>

namespace Ui {
class DataDisplayWidget;
}

class QDESIGNER_WIDGET_EXPORT DataDisplayWidget : public QWidget
{
    Q_OBJECT


    Q_PROPERTY(QString DataDisplayName READ GetDataDisplayName WRITE SetDataDisplayName)
    Q_PROPERTY(QString DataDisplay READ GetDataDisplay WRITE SetDataDisplay)
    Q_PROPERTY(uint MaxLength READ GetMaxLength WRITE SetMaxLength)
    Q_PROPERTY(Qt::Alignment DataDisplayAlignment READ GetDataDisplayAlignment WRITE SetDataDisplayAlignment)

public:
    enum EUnitType
    {
        Null,

        Volt,
        MilliVolt,

        Ampere,
        MilliAmpere,

        Celsius,
        RPM,
        HallSteps,
        FiveMS,
        Percent,
        Acceleration,
    };
    Q_ENUM(EUnitType)

    Q_PROPERTY(EUnitType UnitType READ GetUnitType WRITE SetUnitType)

public:
    explicit DataDisplayWidget(QWidget *parent = nullptr);
    ~DataDisplayWidget();

    QString GetDataDisplayName() const;
    void SetDataDisplayName(const QString& IntDataDisplayName);

    QString GetDataDisplay() const;
    void SetDataDisplay(const QString& InDataDisplay);

    EUnitType GetUnitType() const;
    void SetUnitType(const EUnitType& InUnitType);

    uint GetMaxLength() const;
    void SetMaxLength(const uint InMaxLength);

    Qt::Alignment GetDataDisplayAlignment() const;
    void SetDataDisplayAlignment(const Qt::Alignment& InDataDisplayAlignment);

private:
    Ui::DataDisplayWidget *ui;

    QString DataDisplayName = "Data";
    QString DataDisplay = "0";

    EUnitType UnitType = EUnitType::Null;
    Qt::Alignment DataDisplayAlignment;

    uint MaxLength = 16777215;
};

#endif // DATADISPLAYWIDGET_H
