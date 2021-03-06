#include <reflectionzeug/StringProperty.h>

namespace reflectionzeug
{

StringProperty::~StringProperty()
{
}

void StringProperty::accept(AbstractPropertyVisitor * visitor)
{
    auto * typedVisitor = dynamic_cast<PropertyVisitor<std::string> *>(visitor);
    
    if (typedVisitor == nullptr)
        return StringPropertyInterface::accept(visitor);
    
    typedVisitor->visit(reinterpret_cast<Property<std::string> *>(this));
}

std::string StringProperty::toString() const
{
    return this->value();
}

bool StringProperty::fromString(const std::string & string)
{
    this->setValue(string);
    return true;
}

} // namespace reflectionzeug
