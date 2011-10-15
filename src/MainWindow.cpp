#include "MainWindow.h"
#include <QApplication>
#include <QCloseEvent>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMenuBar>
#include <QMessageBox>
#include <QTabBar>
#include <QToolBar>
#include <QStyle>
#include "Globals.h"
#include "SharedMenuBar.h"
#include "SharedPreferences.h"
#include "TabWidget.h"
#include "View.h"

namespace UJ
{

namespace Qelly
{

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    buildToolBar();
    setMenuBar(SharedMenuBar::sharedInstance());
    _tabs = new TabWidget(this);
    _tabs->setTabPosition(QTabWidget::North);
    SharedPreferences *prefs = SharedPreferences::sharedInstance();
    int cellWidth = prefs->cellWidth();
    int cellHeight = prefs->cellHeight();
    int row = BBS::SizeRowCount;
    int column = BBS::SizeColumnCount;
    _width = column * cellWidth;
    _height = row * cellHeight + _tabs->tabBarHeight();
    setCentralWidget(_tabs);
}

MainWindow::~MainWindow()
{
    delete _stretch;
    delete _inputFrame;
}

void MainWindow::buildToolBar()
{
    _stretch = new QWidget();
    _stretch->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    _address = new QLineEdit();
    _address->setPlaceholderText(tr("Input site address"));
    _address->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    _address->setFocusPolicy(Qt::ClickFocus);
    QLabel *inputLabel = new QLabel(QString("<small>") +
                                    tr("Address") +
                                    QString("</small>"));
    inputLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    inputLabel->setAlignment(Qt::AlignCenter);
    inputLabel->setFocusPolicy(Qt::ClickFocus);
    _inputFrame = new QWidget();
    _inputFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    QVBoxLayout *inputLayout = new QVBoxLayout(_inputFrame);
    inputLayout->addWidget(_address);
    inputLayout->addWidget(inputLabel);
    _inputFrame->setLayout(inputLayout);

    QStyle *style = qApp->style();
    _toolbar = addToolBar(tr("General"));
    _toolbar->addAction(style->standardIcon(QStyle::SP_DriveNetIcon),
                        tr("Sites"));
    _toolbar->addAction(style->standardIcon(QStyle::SP_BrowserReload),
                        tr("Reconnect"));
    _toolbar->addAction(style->standardIcon(QStyle::SP_DialogSaveButton),
                        tr("Add"));
    _toolbar->addWidget(_inputFrame);
    _toolbar->addWidget(_stretch);
    _toolbar->addAction(style->standardIcon(QStyle::SP_DirIcon),
                        tr("Emicons"));
    _toolbar->addAction(style->standardIcon(QStyle::SP_DirIcon),
                        tr("Anti-Idle"));
    _toolbar->addAction(style->standardIcon(QStyle::SP_DirIcon),
                        tr("Peek"));
    _toolbar->addAction(style->standardIcon(QStyle::SP_DirIcon),
                        tr("Double Byte"));
    setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    setUnifiedTitleAndToolBarOnMac(true);
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    e->ignore();
    emit windowShouldClose();
}

}   // namespace Qelly

}   // namespace UJ
