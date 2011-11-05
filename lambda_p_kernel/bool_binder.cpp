#include "bool_binder.h"

#include <lambda_p/binder/binder_implementor.h>
#include <lambda_p/binder/data.h>

#include <sstream>
#include <cctype>

lambda_p_kernel::bool_binder::bool_binder ()
{
	lambda_p_kernel::bool_c t (true);
	lambda_p_kernel::bool_c f (false);
	map [std::wstring (L"true")] = t;
	map [std::wstring (L"1")] = t;
	map [std::wstring (L"t")] = t;
	map [std::wstring (L"on")] = t;
	map [std::wstring (L"yes")] = t;
	map [std::wstring (L"high")] = t;
	map [std::wstring (L"false")] = f;
	map [std::wstring (L"0")] = f;
	map [std::wstring (L"f")] = f;
	map [std::wstring (L"off")] = f;
	map [std::wstring (L"no")] = f;
	map [std::wstring (L"low")] = f;
}

void lambda_p_kernel::bool_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::node_list & nodes, lambda_p::errors::error_list & problems)
{
	check_count (1, 1, statement, problems);
	if (problems.errors.empty ())
	{
		boost::shared_ptr <lambda_p::binder::data> data (boost::dynamic_pointer_cast <lambda_p::binder::data> (nodes [statement->association->references [0]]));
		check_binder (data, 0, L"data", problems);
		if (problems.errors.empty ())
		{
			std::wstring string (data->string ());
			std::transform (string.begin (), string.end (), string.begin (), std::tolower);
			auto value (map.find (string));
			if (value != map.end ())
			{
				nodes [statement->association->declarations [0]] = boost::shared_ptr <lambda_p_kernel::bool_c> (new lambda_p_kernel::bool_c (value->second));
			}
			else
			{
				std::wstringstream message;
				message << L"Cannot convert: ";
				message << data->string ();
				message << L" to a boolean value";
				add_error (message.str (), problems);
			}
		}
	}
}

std::wstring lambda_p_kernel::bool_binder::binder_name ()
{
	return std::wstring (L"bool_binder");
}
