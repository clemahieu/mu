#include <mu/script/astring.truncate.h>

#include <mu/script/string.node.h>
#include <mu/script/astring.node.h>

#include <boost/make_shared.hpp>

void mu::script::astring::truncate::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <mu::script::string::node> (parameters [0]));
	if (one.get () != nullptr)
	{
		std::string string (one->string.begin (), one->string.end ());
		results.push_back (boost::make_shared <mu::script::astring::node> (string));
	}
	else
	{
		invalid_type (errors_a, parameters [0], 0);
	}
}

size_t mu::script::astring::truncate::count ()
{
	return 1;
}
