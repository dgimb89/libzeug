
#include <propertyzeug/Announcer.h>
#include <propertyzeug/AbstractAttribute.h>

namespace propertyzeug {

Announcer::Announcer(AbstractAttribute * attribute)
:   m_subscriptions(new std::unordered_map<int, 
        std::forward_list<std::function<void(AbstractAttribute &)>> *>())
,   m_attribute(attribute)
{
}

Announcer::~Announcer()
{
    for (auto pair : *m_subscriptions)
        delete std::get<1>(pair);
    delete m_subscriptions;
}

void Announcer::subscribe(int event, std::function<void(AbstractAttribute &)> functor)
{
    this->subscriptions(event).push_front(functor);
}

void Announcer::notify(int event)
{
    for (std::function<void(AbstractAttribute &)> functor : this->subscriptions(event))
        functor(*m_attribute);
}

std::forward_list<std::function<void(AbstractAttribute &)>> & Announcer::subscriptions(int event)
{
    if (m_subscriptions->find(event) == m_subscriptions->end()) {
        auto list = new std::forward_list<std::function<void(AbstractAttribute &)>>();
        m_subscriptions->insert(std::make_pair(event, list));
    }
    
    return *m_subscriptions->at(event);
}

}