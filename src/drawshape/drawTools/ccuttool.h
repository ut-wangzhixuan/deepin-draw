// SPDX-FileCopyrightText: 2020 - 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef CCUTTOOL_H
#define CCUTTOOL_H

#include "idrawtool.h"
#include "cgraphicscutitem.h"
#include "csizehandlerect.h"
class CCutWidget;
class CCutTool : public IDrawTool
{
    Q_OBJECT
public:
    CCutTool();
    virtual ~CCutTool() override;
    DrawAttribution::SAttrisList attributions() override;

    /**
     * @brief toolButton 定义工具的激活按钮
     */
    QAbstractButton *initToolButton() override;

    void  setAttributionVar(int attri, const QVariant &var, int phase, bool autoCmdStack) override;
    void  registerAttributionWidgets() override;

protected:
    /**
     * @brief toolStart　工具开始事件
     * @param event      当次事件信息
     * @param pInfo      记录信息
     */
    virtual void toolStart(CDrawToolEvent *event, ITERecordInfo *pInfo) override;

    /**
     * @brief toolStart　判断工具活跃类型
     * @param event      当次事件信息
     * @param pInfo      记录信息
     */

    enum EOperateType { ENothing,
                        EDragMove,
                        EResizeMove
                      };
    virtual int decideUpdate(CDrawToolEvent *event, ITERecordInfo *pInfo) override;

    /**
     * @brief toolStart　 工具刷新事件
     * @param event       当次事件信息
     * @param pInfo       记录信息
     */
    virtual void toolUpdate(CDrawToolEvent *event, ITERecordInfo *pInfo) override;

    /**
     * @brief toolStart　工具结束事件
     * @param event      当次事件信息
     * @param pInfo      记录信息
     */
    virtual void toolFinish(CDrawToolEvent *event, ITERecordInfo *pInfo) override;

    /**
     * @brief toolStart　鼠标hover事件（处理高亮，鼠标样式变化等）
     * @param event      当次事件信息
     */
    virtual void mouseHoverEvent(CDrawToolEvent *event) override;


public:
    /**
     * @brief createCutItem 创建裁剪图元
     * @param scene　场景句柄
     */
    void createCutItem(PageScene *scene);
    /**
     * @brief deleteCutItem　删除裁剪图元
     * @param scene　场景句柄
     */
    void deleteCutItem(PageScene *scene);
    /**
     * @brief changeCutType　改变裁剪类型
     * @param scene　场景句柄
     */
    QSizeF changeCutType(int, PageScene *scene);
    /**
     * @brief changeCutSize　改变裁剪尺寸
     */
    void changeCutSize(const PageScene *scene, const QSize &);

    /**
     * @brief doFinished　结束裁剪
     */
    void doFinished(bool accept, bool cmd = false);

    /**
     * @brief getCutStatus　获取裁剪状态（移动位置、大小改变都会返回true，否则返回false）
     */
    bool getCutStatus();

    /**
     * @brief getCutRect　获取裁剪区域矩形大小
     * @return
     */
    //QRectF getCutRect(PageScene *scene);

    /**
     * @brief getCutType　获取裁剪区域裁剪类型
     * @return
     */
    //int getCutType(PageScene *scene);

    CGraphicsCutItem *getCurCutItem();
    CGraphicsCutItem *getCutItem(PageScene *scene);

    void onStatusChanged(EStatus oldStatus, EStatus newStatus) override;

    bool blockPageBeforeOutput(Page *page) override;

protected:
    bool returnToSelectTool(CDrawToolEvent *event, IDrawTool::ITERecordInfo *pInfo) override;


    bool eventFilter(QObject *o, QEvent *e) override;

private:
    CGraphicsCutItem *m_pCutItem;
    CSizeHandleRect::EDirection m_dragHandle; //选中的方块方向

    bool m_bModify;

    // 用于保存剪裁图元避免多个场景有裁剪的时候其它场景不显示
    QMap<PageScene *, CGraphicsCutItem *> m_cutItems;

    QMap<PageScene *, QRectF> m_originSizeMap;

    CCutWidget *_pCutWidget = nullptr;
};

#endif // CCUTTOOL_H
