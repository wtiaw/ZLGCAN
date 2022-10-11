#include "QWidgetLibrary.h"
#include "CustomWidget/DataEdit.h"
#include "Setting/QDeviceSettingConfig.h"
#include "qcombobox.h"
#include "qlabel.h"
#include "qlayoutitem.h"
#include "qwidget.h"
#include "qlayout.h"


void QWidgetLibrary::ClearLayoutChildrenWidget(QLayout *InLayout)
{
    if(!InLayout)
        return;

    while (QLayoutItem* child = InLayout->takeAt(0))
    {
        //setParent为NULL，防止删除之后界面不消失
        if(child->widget())
        {
            child->widget()->setParent(NULL);
        }

        delete child;
    }
}

QString QWidgetLibrary::GetLineTextValue(const QLineEdit *InLineEdit)
{
    QString Result = InLineEdit->text();
    if(Result == ""){
        Result = InLineEdit->placeholderText();
    }

    return Result;
}

bool QWidgetLibrary::ChackDLCData(QLineEdit *DLCEditer, QComboBox* InComboBox)
{
    int tmp = DLCEditer->text().toInt();

    if(tmp < 0)
    {
        DLCEditer->setText("0");
        return false;
    }
    else if(tmp > 8)
    {
        if(InComboBox->currentIndex())
        {
            //CANFD
            if(tmp > 64)
            {
                DLCEditer->setText("64");
                return false;
            }
        }
        else
        {
            //CAN
            DLCEditer->setText("8");
            return false;
        }
    }

    return true;
}

void QWidgetLibrary::CreateDataEdit(QLayout *InLayout, QLineEdit* DLCEditer, QVector<DataEdit*> &DataEdits)
{
    if(!InLayout)
        return;

    QGridLayout* Container = qobject_cast<QGridLayout*>(InLayout);
    if(!Container)
        return;

    QVector<DataEdit*>().swap(DataEdits);
    QWidgetLibrary::ClearLayoutChildrenWidget(InLayout);

    int DataLength =  GetLineTextValue(DLCEditer).toInt();
    int RowCount = DataLength / 8;
    if(DataLength % 8 == 0){
        RowCount -= 1;
    }

    //在（0,0）生产 “数据(0x)” 文本
    QLabel* Datalab = new QLabel();
    Datalab->setText(QString("数据(0x)"));
    Datalab->setAlignment(Qt::AlignCenter);
    Container->addWidget(Datalab,0,0);

    for(int i = 0; i < (DataLength > 8 ? 8 : DataLength); i++){
        QLabel* IndexLab = new QLabel();
        IndexLab->setText(QString("%1").arg(i));
        IndexLab->setAlignment(Qt::AlignCenter);
        Container->addWidget(IndexLab,0,i + 1);
    }

    QSpacerItem* Hor = new QSpacerItem(10,10,QSizePolicy::Expanding);
    Container->addItem(Hor, 0, (DataLength > 8 ? 8 : DataLength) + 1);


    int RowRemainDataLength = DataLength;
    DataEdit* Prebt = nullptr;

    for(int i = 0; i < RowCount + 1; i++)
    {
        QLabel* IndexLab = new QLabel();
        IndexLab->setText(QString("%1").arg(i));
        IndexLab->setAlignment(Qt::AlignCenter);
        Container->addWidget(IndexLab, i + 1, 0);

        for(int j = 1; j < (RowRemainDataLength > 8 ? 8 : RowRemainDataLength) + 1; j++){
            DataEdit* bt = new DataEdit();

            if(Prebt){
                Prebt->SetNextEdit(bt);
            }
            Prebt = bt;

            bt->setPlaceholderText("00");
            bt->setAlignment(Qt::AlignCenter);
            Container->addWidget(bt, i + 1, j);

            DataEdits.append(bt);
        }
        RowRemainDataLength -= 8;
        if(RowRemainDataLength < 0) RowRemainDataLength = 0;
    }
}

void QWidgetLibrary::InitMessageFrameTypeComboBox(QComboBox *InComboBox)
{
    InComboBox->clear();

    for (const auto &i : QDeviceSettingConfig::MessageFrameType) {
        InComboBox->addItem(i.Display);
    }


    InComboBox->setCurrentIndex(0);
}

void QWidgetLibrary::InitMessageID(QLineEdit *MessageIDEditer)
{
    QRegularExpression regx("[A-Fa-f0-9]{1,4}");
    QValidator* validator = new QRegularExpressionValidator(regx, MessageIDEditer);
    MessageIDEditer->setValidator(validator);
}

void QWidgetLibrary::InitMessageDLC(QLineEdit *DLCEditer)
{
    QRegularExpression regx("[0-9]{1,2}");
    QValidator* validator = new QRegularExpressionValidator(regx, DLCEditer);
    DLCEditer->setValidator(validator);
}
