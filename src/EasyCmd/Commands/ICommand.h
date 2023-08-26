#ifndef ICOMMAND_H
#define ICOMMAND_H

#include <QString>
#include <QWidget>

#include "ICmdEditor.h"

class ICommand
{
public:
    ICommand();
    virtual ~ICommand();

    /**
     * @brief getCmdName
     *  获取命令名称，在编辑器初始化后作为初始命令显示。
     * @return
     */
    virtual QString getCmdName() = 0;

    /**
     * @brief createEditorWidget
     *  创建命令编辑器
     * @return
     */
    virtual ICmdEditor *createCmdEditorWidget() = 0;
};

#endif // ICOMMAND_H
