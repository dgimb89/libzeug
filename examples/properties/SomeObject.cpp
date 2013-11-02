

#include <iostream>

#include <propertyzeug/AbstractProperty.h>

#include "SomeObject.h"


int SomeObject::count() const
{
    return m_count;
}

void SomeObject::setCount(const int & count)
{
    m_count = count;
}

void SomeObject::valueChanged(const int & value)
{
    std::cout << "Property value changed to \"" << value << "\"" << std::endl;
}