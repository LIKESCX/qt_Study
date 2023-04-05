/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actOpen;
    QAction *actSave;
    QAction *actAppend;
    QAction *actInsert;
    QAction *actDelete;
    QAction *actExit;
    QAction *actModelData;
    QAction *actAlignLeft;
    QAction *actAlignCenter;
    QAction *actAlignRight;
    QAction *actFontBold;
    QWidget *centralwidget;
    QGridLayout *gridLayout_3;
    QSplitter *splitter;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QTableView *tableView;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QPlainTextEdit *plainTextEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(662, 448);
        actOpen = new QAction(MainWindow);
        actOpen->setObjectName(QString::fromUtf8("actOpen"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/icons/open.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        actOpen->setIcon(icon);
        actSave = new QAction(MainWindow);
        actSave->setObjectName(QString::fromUtf8("actSave"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/icons/save.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        actSave->setIcon(icon1);
        actAppend = new QAction(MainWindow);
        actAppend->setObjectName(QString::fromUtf8("actAppend"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/icons/append.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        actAppend->setIcon(icon2);
        actInsert = new QAction(MainWindow);
        actInsert->setObjectName(QString::fromUtf8("actInsert"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/icons/306.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        actInsert->setIcon(icon3);
        actDelete = new QAction(MainWindow);
        actDelete->setObjectName(QString::fromUtf8("actDelete"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/icons/delete.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        actDelete->setIcon(icon4);
        actExit = new QAction(MainWindow);
        actExit->setObjectName(QString::fromUtf8("actExit"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/images/icons/exit.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        actExit->setIcon(icon5);
        actModelData = new QAction(MainWindow);
        actModelData->setObjectName(QString::fromUtf8("actModelData"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/images/icons/export1.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        actModelData->setIcon(icon6);
        actAlignLeft = new QAction(MainWindow);
        actAlignLeft->setObjectName(QString::fromUtf8("actAlignLeft"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/images/icons/508.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        actAlignLeft->setIcon(icon7);
        actAlignCenter = new QAction(MainWindow);
        actAlignCenter->setObjectName(QString::fromUtf8("actAlignCenter"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/images/icons/510.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        actAlignCenter->setIcon(icon8);
        actAlignRight = new QAction(MainWindow);
        actAlignRight->setObjectName(QString::fromUtf8("actAlignRight"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/images/icons/512.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        actAlignRight->setIcon(icon9);
        actFontBold = new QAction(MainWindow);
        actFontBold->setObjectName(QString::fromUtf8("actFontBold"));
        actFontBold->setCheckable(true);
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/images/icons/500.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        actFontBold->setIcon(icon10);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_3 = new QGridLayout(centralwidget);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        groupBox = new QGroupBox(splitter);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tableView = new QTableView(groupBox);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        gridLayout->addWidget(tableView, 0, 0, 1, 1);

        splitter->addWidget(groupBox);
        groupBox_2 = new QGroupBox(splitter);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        plainTextEdit = new QPlainTextEdit(groupBox_2);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));

        gridLayout_2->addWidget(plainTextEdit, 0, 0, 1, 1);

        splitter->addWidget(groupBox_2);

        gridLayout_3->addWidget(splitter, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 662, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        toolBar->setContextMenuPolicy(Qt::DefaultContextMenu);
        toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(actOpen);
        toolBar->addAction(actSave);
        toolBar->addAction(actModelData);
        toolBar->addSeparator();
        toolBar->addAction(actAppend);
        toolBar->addAction(actInsert);
        toolBar->addAction(actDelete);
        toolBar->addSeparator();
        toolBar->addAction(actAlignLeft);
        toolBar->addAction(actAlignCenter);
        toolBar->addAction(actAlignRight);
        toolBar->addAction(actFontBold);
        toolBar->addSeparator();
        toolBar->addAction(actExit);

        retranslateUi(MainWindow);
        QObject::connect(actExit, SIGNAL(triggered()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "QTableView\344\270\216QStandardItemModel", nullptr));
        actOpen->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
#ifndef QT_NO_TOOLTIP
        actOpen->setToolTip(QApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
#endif // QT_NO_TOOLTIP
        actSave->setText(QApplication::translate("MainWindow", "\345\217\246\345\255\230\346\226\207\344\273\266", nullptr));
#ifndef QT_NO_TOOLTIP
        actSave->setToolTip(QApplication::translate("MainWindow", "\345\217\246\345\255\230\346\226\207\344\273\266", nullptr));
#endif // QT_NO_TOOLTIP
        actAppend->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240\350\241\214", nullptr));
#ifndef QT_NO_TOOLTIP
        actAppend->setToolTip(QApplication::translate("MainWindow", "\346\267\273\345\212\240\344\270\200\350\241\214", nullptr));
#endif // QT_NO_TOOLTIP
        actInsert->setText(QApplication::translate("MainWindow", "\346\217\222\345\205\245\350\241\214", nullptr));
#ifndef QT_NO_TOOLTIP
        actInsert->setToolTip(QApplication::translate("MainWindow", "\346\217\222\345\205\245\344\270\200\350\241\214", nullptr));
#endif // QT_NO_TOOLTIP
        actDelete->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\350\241\214", nullptr));
#ifndef QT_NO_TOOLTIP
        actDelete->setToolTip(QApplication::translate("MainWindow", "\345\210\240\351\231\244\345\275\223\345\211\215\350\241\214", nullptr));
#endif // QT_NO_TOOLTIP
        actExit->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
#ifndef QT_NO_TOOLTIP
        actExit->setToolTip(QApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
#endif // QT_NO_TOOLTIP
        actModelData->setText(QApplication::translate("MainWindow", "\346\225\260\346\215\256\346\250\241\345\236\213\351\242\204\350\247\210", nullptr));
#ifndef QT_NO_TOOLTIP
        actModelData->setToolTip(QApplication::translate("MainWindow", "\346\250\241\345\236\213\346\225\260\346\215\256\346\230\276\347\244\272\345\210\260\346\226\207\346\234\254\346\241\206\351\207\214", nullptr));
#endif // QT_NO_TOOLTIP
        actAlignLeft->setText(QApplication::translate("MainWindow", "\345\261\205\345\267\246", nullptr));
#ifndef QT_NO_TOOLTIP
        actAlignLeft->setToolTip(QApplication::translate("MainWindow", "\346\226\207\345\255\227\345\267\246\345\257\271\351\275\220", nullptr));
#endif // QT_NO_TOOLTIP
        actAlignCenter->setText(QApplication::translate("MainWindow", "\345\261\205\344\270\255", nullptr));
#ifndef QT_NO_TOOLTIP
        actAlignCenter->setToolTip(QApplication::translate("MainWindow", "\346\226\207\345\255\227\345\261\205\344\270\255\345\257\271\351\275\220", nullptr));
#endif // QT_NO_TOOLTIP
        actAlignRight->setText(QApplication::translate("MainWindow", "\345\261\205\345\217\263", nullptr));
#ifndef QT_NO_TOOLTIP
        actAlignRight->setToolTip(QApplication::translate("MainWindow", "\346\226\207\345\255\227\345\217\263\345\257\271\351\275\220", nullptr));
#endif // QT_NO_TOOLTIP
        actFontBold->setText(QApplication::translate("MainWindow", "\347\262\227\344\275\223", nullptr));
#ifndef QT_NO_TOOLTIP
        actFontBold->setToolTip(QApplication::translate("MainWindow", "\347\262\227\344\275\223\345\255\227\344\275\223", nullptr));
#endif // QT_NO_TOOLTIP
        groupBox->setTitle(QApplication::translate("MainWindow", "TableView", nullptr));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "PlainTextEdit", nullptr));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
