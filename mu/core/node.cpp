#include <mu/core/node.h>

#include <typeinfo>

mu::core::node::~node ()
{
}

mu::string mu::core::node::name ()
{
    auto & id (typeid (*this));
    std::string str (id.name ());
	return mu::string (str.begin (), str.end ());
}

mu::string mu::core::node::debug ()
{
	return name ();
}