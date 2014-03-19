
#include <QHBoxLayout>
#include <QComboBox>

#include <reflectionzeug/Property.h>

#include <propertyguizeug/ChoiceEditor.h>

using namespace reflectionzeug;
namespace propertyguizeug
{
    
ChoiceEditor::ChoiceEditor(Property<std::string> * property, QWidget * parent)
:   PropertyEditor(parent)
,   m_property(property)
{
    QStringList list;
    for (const std::string & choice : m_property->choices())
        list << QString::fromStdString(choice);
    
    QComboBox * comboBox = new QComboBox(this);
    comboBox->addItems(list);
    this->setFocusProxy(comboBox);
    comboBox->setCurrentText(QString::fromStdString(m_property->value()));
    
    this->boxLayout()->addWidget(comboBox);
    
    this->connect(comboBox, &QComboBox::currentTextChanged, this, &ChoiceEditor::setString);
}

ChoiceEditor::~ChoiceEditor()
{
}
    
void ChoiceEditor::setString(const QString & text)
{
    m_property->setValue(text.toStdString());
}

} // namespace propertyguizeug
