#include <mu/script/package.create.h>

#include <mu/script/package.node.h>

void mu::script::package::create::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	results.push_back (boost::shared_ptr <mu::script::package::node> (new mu::script::package::node));
}

std::wstring mu::script::package::create::name ()
{
	return std::wstring (L"mu::script::package::create");
}

size_t mu::script::package::create::count ()
{
	return 0;
}
