#include <mu/script/type_check/operation.h>

#include <mu/core/errors/error_target.h>
#include <sstream>

bool mu::script::type_check::check_count (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, size_t expected)
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

void mu::script::type_check::invalid_type (boost::shared_ptr <mu::core::errors::error_target> errors_a, boost::shared_ptr <mu::core::node> node_a, size_t position)
{
	std::wstringstream message;
	message << L"In operation: ";
	//message << name ();
	message << L" invalid node type:";
	message << node_a->name ();
	message << L" at position: ";
	message << position;
	(*errors_a) (message.str ());
}