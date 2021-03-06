#include <reflectionzeug/PropertyDeserializer.h>

#ifdef USE_STD_REGEX
    #include <regex>

    namespace regex_namespace = std;
#else
    #include <boost/regex.hpp>

    namespace regex_namespace = boost;
#endif

#include <iostream>
#include <fstream>

#include <loggingzeug/logging.h>

#include <reflectionzeug/Property.h>
#include <reflectionzeug/PropertyGroup.h>
#include <reflectionzeug/util.h>

using namespace loggingzeug;

namespace reflectionzeug
{

PropertyDeserializer::PropertyDeserializer()
:   m_rootGroup(nullptr)
,   m_currentGroup(nullptr)
,   m_currentValue("")
{
}

PropertyDeserializer::~PropertyDeserializer()
{
}

bool PropertyDeserializer::deserialize(PropertyGroup & group, const std::string & filePath)
{
    std::fstream fstream;
    fstream.open(filePath, std::ios_base::in);
    if (!fstream.is_open()) {
        critical() << "Could not open file \"" << filePath << "\"" << std::endl;
        return false;
    }

    bool noErrorsOccured = true;
    m_rootGroup = &group;

    for (std::string line; std::getline(fstream, line);) {
        if (this->isGroupDeclaration(line))
            noErrorsOccured = this->updateCurrentGroup(line) && noErrorsOccured;
        else if (this->isPropertyDeclaration(line))
            noErrorsOccured = this->setPropertyValue(line) && noErrorsOccured;
    }

    fstream.close();
    return noErrorsOccured;
}

bool PropertyDeserializer::isGroupDeclaration(const std::string & line)
{
    static const regex_namespace::regex groupRegex("\\[" + AbstractProperty::s_nameRegexString + "\\]");

    return regex_namespace::regex_match(line, groupRegex);
}

bool PropertyDeserializer::isPropertyDeclaration(const std::string & line)
{
    static const regex_namespace::regex propertyRegex(AbstractProperty::s_nameRegexString +
                                          "(\\/" +
                                          AbstractProperty::s_nameRegexString +
                                          ")*=.+");

    return regex_namespace::regex_match(line, propertyRegex);
}

bool PropertyDeserializer::updateCurrentGroup(const std::string & line)
{
    std::string groupName = line.substr(1, line.length() - 2);

    assert(m_rootGroup);
    if (m_rootGroup->name() == groupName) {
        m_currentGroup = m_rootGroup;
        return true;
    }

    if (m_rootGroup->groupExists(groupName)) {
        m_currentGroup = m_rootGroup->group(groupName);
        return true;
    }

    m_currentGroup = nullptr;
    critical() << "Group with name \"" << groupName << "\" does not exist" << std::endl;
    return false;
}

bool PropertyDeserializer::setPropertyValue(const std::string & line)
{
    if (!m_currentGroup) {
        critical() << "Could not parse line\"" << line << "\"" << "because no existing group was declared" << std::endl;
        return false;
    }

    regex_namespace::smatch match;
    regex_namespace::regex_search(line, match, regex_namespace::regex("="));
    const std::string & path = match.prefix();
    std::string valueString = match.suffix();

    AbstractProperty * property = m_currentGroup->property(path);

    if (!property) {
        critical() << "Property path \"" << path << "\" " << "is invalid" << std::endl;
        return false;
    }

    if (!property->isValue()) {
        critical() << "Tried to assign value to group with name: " << property->name() << std::endl;
        return false;
    }

    if (!property->asValue()->fromString(util::trim(valueString, false))) {
        critical() << "Could not convert \"" << valueString << "\" to property." << std::endl;
        return false;
    }

    return true;
}

} // namespace reflectionzeug
