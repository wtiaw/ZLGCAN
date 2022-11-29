#include "LoadDBCWindow.h"

#include <QFileDialog>

#include "mainwindow.h"
#include "ui_LoadDBCWindow.h"

LoadDBCWindow::LoadDBCWindow(QWidget *parent, Qt::WindowFlags f) :
    QWidget(parent, f),
    ui(new Ui::LoadDBCWindow)
{
    ui->setupUi(this);

    auto* mainWindow = qobject_cast<MainWindow*>(parent);

    setAttribute(Qt::WA_QuitOnClose, false);
    setWindowTitle("加载DBC");

    connect(ui->LoadDBC, &QPushButton::clicked, this, &LoadDBCWindow::On_LoadDBCClicked);
    connect(ui->SelectPath, &QPushButton::clicked, this, &LoadDBCWindow::On_SelectPathClicked);
}

LoadDBCWindow::~LoadDBCWindow()
{
    delete ui;
}

void LoadDBCWindow::On_LoadDBCClicked()
{
}

void LoadDBCWindow::On_SelectPathClicked()
{
    QFileDialog* FileDialog = new QFileDialog(this);
    FileDialog->setWindowTitle("加载DBC");
    FileDialog->setNameFilter("*.dbc");
    FileDialog->setViewMode(QFileDialog::Detail);

    QString FilePath;
    if(FileDialog->exec() == QDialog::Accepted)
        FilePath = FileDialog->selectedFiles()[0];

    ui->Path->setText(FilePath);
}
