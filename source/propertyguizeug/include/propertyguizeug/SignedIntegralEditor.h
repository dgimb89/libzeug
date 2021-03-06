
#pragma once

#include <propertyguizeug/PropertyEditor.h>


namespace reflectionzeug
{
    class SignedIntegralPropertyInterface;
}

namespace propertyguizeug
{
    
class LongLongSpinBox;

/** \brief Editor for signed integral point properties
 *
 * Supported options
 * - minimum (long long): lowest value to be accepted
 * - maximum (long long): greatest value to be accepted
 * - step (long long): step size of the spinbox
 */
class PROPERTYGUIZEUG_API SignedIntegralEditor : public PropertyEditor
{
public:
    SignedIntegralEditor(reflectionzeug::SignedIntegralPropertyInterface * property, 
                         QWidget * parent = nullptr);

protected:
    LongLongSpinBox * m_spinBox;
    
    reflectionzeug::SignedIntegralPropertyInterface * m_property;
};

} // namespace propertyguizeug
