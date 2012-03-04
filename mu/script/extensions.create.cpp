#include <mu/script/extensions.create.h>

#include <mu/script/extensions.node.h>

#include <boost/make_shared.hpp>

void mu::script::extensions::create::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	results.push_back (boost::make_shared <mu::script::extensions::node> ());
}

size_t mu::script::extensions::create::count ()
{
	return 0;
}
