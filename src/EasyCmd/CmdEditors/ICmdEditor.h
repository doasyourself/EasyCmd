#ifndef ICMDEDITOR_H
#define ICMDEDITOR_H

#include <QString>
#include <QWidget>

class ICmdEditor : public QWidget
{
    Q_OBJECT
public:
    explicit ICmdEditor(QWidget *parent = NULL);

    virtual bool isModified() const = 0;

    /**
     * @brief getCmdName
     *  获取命令名称，在编辑器初始化后作为初始命令显示。
     * @return
     */
    virtual QString getCmdName();

    /**
     * @brief getCmdString
     *  获取完整命令，包括命令名称、参数、可选择项，可以进行校验，对用户进行提示。
     * @return
     */
    virtual QString getCmdString() = 0;

signals:
    void sigModified();/*更新命令*/
    void sigExecute();/*立即执行命令*/
};

#endif // ICMDEDITOR_H
