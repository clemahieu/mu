#include <mu/script/type_check/check.h>

#include <mu/core/errors/error_target.h>
#include <sstream>

bool mu::script::check_count (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, size_t expected)
{
	bool result (parameters.size () == expected);
	if (!result)
	{
		std::wstringstream message;
		message << L"In operation: ";
		//message << name ();
		message << L" expecting: ";
		message << expected;
		message << L" arguments, have: ";
		message << parameters.size ();
		(*errors_a) (message.str ());
	}
	return result;
}

void mu::script::invalid_type (boost::shared_ptr <mu::core::errors::error_target> errors_a, std::type_info const & actual, std::type_info const & expected, size_t position)
{
	std::wstringstream message;
	message << L"In operation: ";
	//message << name ();
	message << L" invalid node type:";
	message << actual.name ();
	message << L" at position: ";
	message << position;
	message << L" expecting: ";
	message << expected.name ();
	(*errors_a) (message.str ());
}