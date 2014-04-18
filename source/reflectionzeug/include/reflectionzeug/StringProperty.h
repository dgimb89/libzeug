
#pragma once

#include <vector>

#include <signalzeug/Signal.h>

#include <reflectionzeug/reflectionzeug.h>
#include <reflectionzeug/ValueProperty.h>

namespace reflectionzeug
{
    
/** \brief Part of the property hierarchy that manages a string and can have choices.
 */
class StringProperty : public ValueProperty<std::string>
{
public:
    template <typename... Arguments>
    StringProperty(Arguments&&... args);
    
    REFLECTIONZEUG_API virtual ~StringProperty() = 0;

    REFLECTIONZEUG_API bool hasChoices() const;
    REFLECTIONZEUG_API void addChoice(const std::string & string);

    REFLECTIONZEUG_API const std::vector<std::string>  & choices() const;
    REFLECTIONZEUG_API void setChoices(const std::vector<std::string> & choices);
    
    REFLECTIONZEUG_API void clearChoices();

    REFLECTIONZEUG_API virtual std::string toString() const;
    REFLECTIONZEUG_API virtual bool fromString(const std::string & string);
    
    signalzeug::Signal<const std::vector<std::string> &> choicesChanged;
    
protected:
    std::vector<std::string> m_choices;
};

} // namespace reflectionzeug

#include "StringProperty.hpp"
