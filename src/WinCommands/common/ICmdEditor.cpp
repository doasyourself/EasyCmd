#include "ICmdEditor.h"

ICmdEditor::ICmdEditor(QWidget *parent) : QWidget(parent)
{

}

int ICmdEditor::getProperty(int propertyId, QVariant &out_property)
{
    return 0;
}

int ICmdEditor::setProperty(int propertyId, const QVariant &property)
{
    return 0;
}

void ICmdEditor::slotOnNotify(int type, const QVariantHash &val)
{

}

