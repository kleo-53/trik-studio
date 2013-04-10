#include "gridParameters.h"
#include <QtGui/QSlider>
#include <QtGui/QCheckBox>
#include <QtGui/QGroupBox>
#include <QtGui/QLabel>
#include <QString>
#include "../../../qrkernel/settingsManager.h"

gridParameters::gridParameters(QWidget *parent)
	: QGroupBox(parent)
{
    showGridCheckBox = new QCheckBox(this);
    showGridCheckBox->setObjectName(QString::fromUtf8("showGridCheckBox"));
    showGridCheckBox->setGeometry(QRect(10, 20, 70, 17));

    cellSize = new QSlider(this);
    cellSize->setObjectName(QString::fromUtf8("cellSize"));
    cellSize->setGeometry(QRect(10, 50, 131, 19));
    cellSize->setOrientation(Qt::Horizontal);
    cellSize->setMinimum(50);
    cellSize->setMaximum(200);
    cellSize->setTickInterval(10);
    cellSize->setEnabled(false);

    cellSizeLabel = new QLabel(this);
    cellSizeLabel->setObjectName(QString::fromUtf8("label_8"));
    cellSizeLabel->setGeometry(QRect(50, 40, 46, 13));

    connect(showGridCheckBox, SIGNAL(toggled(bool)), cellSize, SLOT(setEnabled(bool)));
    connect(showGridCheckBox, SIGNAL(toggled(bool)), this, SLOT(showGrid(bool)));
    connect(cellSize, SIGNAL(valueChanged(int)), this, SLOT(setCellSize(int)));
}

gridParameters:: ~gridParameters()
{
}

void gridParameters::showGrid(bool isGridEnabled)
{
    qReal::SettingsManager::setValue("2dShowGrid", isGridEnabled);
}

void gridParameters::setCellSize(int cellSizeValue)
{
    qReal::SettingsManager::setValue("2dGridCellSize", cellSizeValue);
}
