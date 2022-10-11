#include "QDrawerCheckBox.h"
#include <QMouseEvent>
#include <QApplication>

QString QDrawerCheckBox::EnableQss = R"(
                  QCheckBox{
                      spacing: 2px;
                      color:rgb(0,0,0);
                      font: 12pt "Microsoft YaHei UI";
                  }
                  QCheckBox::indicator {
                      width:  18px;
                      height: 18px;
                  }
                  QCheckBox::indicator:unchecked {
                      image: url(:/Icon/Resourse/Collapsed.png);
                  }
                  QCheckBox::indicator:unchecked:hover {
                      image:url(:/Icon/Resourse/Collapsed.png);
                  }
                  QCheckBox::indicator:unchecked:pressed {
                      image:url(:/Icon/Resourse/Collapsed.png);
                  }
                  QCheckBox::indicator:checked {
                      image: url(:/Icon/Resourse/Expanded.png);
                  }
                  QCheckBox::indicator:checked:hover {
                      image: url(:/Icon/Resourse/Expanded.png);
                  }
                  QCheckBox::indicator:checked:pressed {
                      image: url(:/Icon/Resourse/Expanded.png);
                  })";

QString QDrawerCheckBox::DisableQss = R"(
              QCheckBox{
                  spacing: 2px;
                  color:rgb(200,200,200);
                  font: 12pt "Microsoft YaHei UI";
              }
              QCheckBox::indicator {
                  width:  18px;
                  height: 18px;
              }
              QCheckBox::indicator:unchecked {
                  image: url(:/Icon/Resourse/Collapsed_Disable.png);
              }
              QCheckBox::indicator:unchecked:hover {
                  image:url(:/Icon/Resourse/Collapsed_Disable.png);
              }
              QCheckBox::indicator:unchecked:pressed {
                  image:url(:/Icon/Resourse/Collapsed_Disable.png);
              }
              QCheckBox::indicator:checked {
                  image: url(:/Icon/Resourse/Expanded_Disable.png);
              }
              QCheckBox::indicator:checked:hover {
                  image: url(:/Icon/Resourse/Expanded_Disable.png);
              }
              QCheckBox::indicator:checked:pressed {
                  image: url(:/Icon/Resourse/Expanded_Disable.png);
              })";

QDrawerCheckBox::QDrawerCheckBox()
{
    setStyleSheet(DisableQss);
}

void QDrawerCheckBox::mousePressEvent(QMouseEvent *event)
{
    event->accept();

    emit clicked(!isChecked());
    setChecked(!isChecked());
}
