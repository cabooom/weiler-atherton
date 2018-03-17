/********************************************************************************
** Form generated from reading UI file 'PolygonClipper.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POLYGONCLIPPER_H
#define UI_POLYGONCLIPPER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PolygonClipperClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QWidget *paintWidget;
    QLabel *xyLabel;
    QWidget *toolWidget;
    QVBoxLayout *verticalLayout;
    QRadioButton *rbPolygon1;
    QRadioButton *rbPolygon2;
    QRadioButton *rbIntersection;
    QPushButton *btnSave;
    QPushButton *btnLoad;
    QPushButton *btnPrint;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PolygonClipperClass)
    {
        if (PolygonClipperClass->objectName().isEmpty())
            PolygonClipperClass->setObjectName(QStringLiteral("PolygonClipperClass"));
        PolygonClipperClass->resize(877, 630);
        centralWidget = new QWidget(PolygonClipperClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setMouseTracking(true);
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        paintWidget = new QWidget(centralWidget);
        paintWidget->setObjectName(QStringLiteral("paintWidget"));

        horizontalLayout->addWidget(paintWidget);

        xyLabel = new QLabel(centralWidget);
        xyLabel->setObjectName(QStringLiteral("xyLabel"));

        horizontalLayout->addWidget(xyLabel);

        toolWidget = new QWidget(centralWidget);
        toolWidget->setObjectName(QStringLiteral("toolWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(toolWidget->sizePolicy().hasHeightForWidth());
        toolWidget->setSizePolicy(sizePolicy);
        toolWidget->setMaximumSize(QSize(278, 16777215));
        verticalLayout = new QVBoxLayout(toolWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        rbPolygon1 = new QRadioButton(toolWidget);
        rbPolygon1->setObjectName(QStringLiteral("rbPolygon1"));
        rbPolygon1->setChecked(true);

        verticalLayout->addWidget(rbPolygon1, 0, Qt::AlignRight);

        rbPolygon2 = new QRadioButton(toolWidget);
        rbPolygon2->setObjectName(QStringLiteral("rbPolygon2"));

        verticalLayout->addWidget(rbPolygon2, 0, Qt::AlignRight);

        rbIntersection = new QRadioButton(toolWidget);
        rbIntersection->setObjectName(QStringLiteral("rbIntersection"));

        verticalLayout->addWidget(rbIntersection, 0, Qt::AlignRight);

        btnSave = new QPushButton(toolWidget);
        btnSave->setObjectName(QStringLiteral("btnSave"));

        verticalLayout->addWidget(btnSave, 0, Qt::AlignRight);

        btnLoad = new QPushButton(toolWidget);
        btnLoad->setObjectName(QStringLiteral("btnLoad"));

        verticalLayout->addWidget(btnLoad, 0, Qt::AlignRight);

        btnPrint = new QPushButton(toolWidget);
        btnPrint->setObjectName(QStringLiteral("btnPrint"));

        verticalLayout->addWidget(btnPrint, 0, Qt::AlignRight);


        horizontalLayout->addWidget(toolWidget);

        PolygonClipperClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(PolygonClipperClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setMouseTracking(true);
        PolygonClipperClass->setStatusBar(statusBar);

        retranslateUi(PolygonClipperClass);

        QMetaObject::connectSlotsByName(PolygonClipperClass);
    } // setupUi

    void retranslateUi(QMainWindow *PolygonClipperClass)
    {
        PolygonClipperClass->setWindowTitle(QApplication::translate("PolygonClipperClass", "PolygonClipper", Q_NULLPTR));
        xyLabel->setText(QApplication::translate("PolygonClipperClass", "TextLabel", Q_NULLPTR));
        rbPolygon1->setText(QApplication::translate("PolygonClipperClass", "Polygon 1", Q_NULLPTR));
        rbPolygon2->setText(QApplication::translate("PolygonClipperClass", "Polygon 2", Q_NULLPTR));
        rbIntersection->setText(QApplication::translate("PolygonClipperClass", "Intersection", Q_NULLPTR));
        btnSave->setText(QApplication::translate("PolygonClipperClass", "Save", Q_NULLPTR));
        btnLoad->setText(QApplication::translate("PolygonClipperClass", "Load", Q_NULLPTR));
        btnPrint->setText(QApplication::translate("PolygonClipperClass", "Print", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PolygonClipperClass: public Ui_PolygonClipperClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POLYGONCLIPPER_H
