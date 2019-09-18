/*
 * Copyright (C) 2019 ~ %YEAR% Deepin Technology Co., Ltd.
 *
 * Author:     WangXing
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "cpicturewidget.h"
#include "widgets/cclickbutton.h"

#include <QMap>
#include <QHBoxLayout>
#include <QDebug>
#include <DPalette>
#include <DApplicationHelper>


const int BTN_SPACING = 13;

CPictureWidget::CPictureWidget(DWidget *parent)
    : DWidget(parent)
{
    initUI();
    initConnection();
}

CPictureWidget::~CPictureWidget()
{
}

void CPictureWidget::initUI()
{
    QMap<CClickButton::EClickBtnSatus, QString> pictureMapClick;

    pictureMapClick[CClickButton::Normal] = QString(":/theme/light/images/attribute/contrarotate_normal.svg");
    pictureMapClick[CClickButton::Hover] = QString(":/theme/light/images/attribute/contrarotate_hover.svg");
    pictureMapClick[CClickButton::Press] = QString(":/theme/light/images/attribute/contrarotate_press.svg");
    pictureMapClick[CClickButton::Disable] = QString(":/theme/light/images/attribute/contrarotate_disabled.svg");
    m_leftRotateBtn = new CClickButton(pictureMapClick, this);
    DPalette pa1;
    pa1.setColor(DPalette::Background, Qt::gray);
    m_leftRotateBtn->setPalette(pa1);
    m_leftRotateBtn->setAutoFillBackground(true);

    //m_leftRotateBtn->setb

    pictureMapClick[CClickButton::Normal] = QString(":/theme/light/images/attribute/clockwise rotation_normal.png");
    pictureMapClick[CClickButton::Hover] = QString(":/theme/light/images/attribute/clockwise rotation_hover.png");
    pictureMapClick[CClickButton::Press] = QString(":/theme/light/images/attribute/clockwise rotation_press.png");
    pictureMapClick[CClickButton::Disable] = QString(":/theme/light/images/attribute/clockwise rotation_disabled.svg");
    m_rightRotateBtn = new CClickButton(pictureMapClick, this);
    m_rightRotateBtn->setPalette(pa1);
    m_rightRotateBtn->setAutoFillBackground(true);

    pictureMapClick[CClickButton::Normal] = QString(":/theme/light/images/attribute/flip horizontal_normal.svg");
    pictureMapClick[CClickButton::Hover] = QString(":/theme/light/images/attribute/flip horizontal_hover.png");
    pictureMapClick[CClickButton::Press] = QString(":/theme/light/images/attribute/flip horizontal_press.png");
    pictureMapClick[CClickButton::Disable] = QString(":/theme/light/images/attribute/flip horizontal_disabled.svg");
    m_flipHBtn = new CClickButton(pictureMapClick, this);
    m_flipHBtn->setPalette(pa1);
    m_flipHBtn->setAutoFillBackground(true);

    pictureMapClick[CClickButton::Normal] = QString(":/theme/light/images/attribute/flip vertical_normal.svg");
    pictureMapClick[CClickButton::Hover] = QString(":/theme/light/images/attribute/flip vertical_hover.svg");
    pictureMapClick[CClickButton::Press] = QString(":/theme/light/images/attribute/flip vertical_press.png");
    pictureMapClick[CClickButton::Disable] = QString(":/theme/light/images/attribute/flip vertical_disabled.svg");
    m_flipVBtn = new CClickButton(pictureMapClick, this);
    m_flipVBtn->setPalette(pa1);
    m_flipVBtn->setAutoFillBackground(true);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->setSpacing(BTN_SPACING);
    layout->addStretch();
    layout->addWidget(m_leftRotateBtn);
    layout->addWidget(m_rightRotateBtn);
    layout->addWidget(m_flipHBtn);
    layout->addWidget(m_flipVBtn);
    layout->addStretch();
    setLayout(layout);
}

void CPictureWidget::initConnection()
{
    connect(m_leftRotateBtn, &CClickButton::buttonClick, this, [ = ]() {
        emit signalBtnClick(LeftRotate);
    });

    connect(m_rightRotateBtn, &CClickButton::buttonClick, this, [ = ]() {
        emit signalBtnClick(RightRotate);
    });

    connect(m_flipHBtn, &CClickButton::buttonClick, this, [ = ]() {
        emit signalBtnClick(FlipHorizontal);
    });

    connect(m_flipVBtn, &CClickButton::buttonClick, this, [ = ]() {
        emit signalBtnClick(FlipVertical);
    });
}
