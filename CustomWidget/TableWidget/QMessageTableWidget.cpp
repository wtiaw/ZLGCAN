#include "QMessageTableWidget.h"
#include "qheaderview.h"

QMessageTableWidget::QMessageTableWidget(QWidget *parent) :
    QTableWidget(parent)
{
    setColumnCount(6);
    QStringList header;

    header<<"Time(s)"<<"ID"<<"Type"<<"Dir"<<"DLC"<<"Data";
    setHorizontalHeaderLabels(header);

    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSortingEnabled( false );
    verticalHeader()->hide();
    setWordWrap( false );
    setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    setShowGrid( false );
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    horizontalHeader()->setHighlightSections( false );
    setAlternatingRowColors( true );   // alternative colors
    setFrameShape(QFrame::NoFrame);

    //表头加粗
    QFont font =  horizontalHeader()->font();
    font.setBold(true);
    horizontalHeader()->setFont(font);

    // column width
    setColumnWidth(0, 70);
    setColumnWidth(1, 50);
    setColumnWidth(2, 60);
    setColumnWidth(3, 50);
    setColumnWidth(4, 50);
    setColumnWidth(5, 200);
};
