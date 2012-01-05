#include "package.h"

#include <lambda_p/core/statement.h>
#include <lambda_p_kernel/nodes/data.h>
#include <lambda_p/core/association.h>
#include <lambda_p/errors/unexpected_binder_type.h>
#include <lambda_p/binder/list.h>
#include <lambda_p/errors/error_list.h>

#include <boost/tokenizer.hpp>
#include <boost/array.hpp>

#include <sstream>

void lambda_p_kernel::package::bind (lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems)
{
	bool problem (false);
	size_t argument_count (statement->association->references.size ());
	size_t result_count (statement->association->declarations.size ());
	if (argument_count == result_count)
	{
		size_t current_argument (0);
		for (std::vector <size_t>::iterator i = statement->association->references.begin (); i != statement->association->references.end (); ++i, ++current_argument)
		{
			size_t parameter (*i);
			boost::shared_ptr <lambda_p::binder::node> instance (nodes [parameter]);
			boost::shared_ptr <lambda_p_kernel::nodes::data> node_data (boost::dynamic_pointer_cast < lambda_p_kernel::nodes::data> (instance));
			if (node_data.get () != nullptr)
			{
				parse_one (nodes, node_data, statement->association->declarations [current_argument], problems);
			}
			else
			{
				problems (new lambda_p::errors::unexpected_binder_type (binder_name (), 0, std::wstring (L"data")));
				break;
			}
		}
	}
	else
	{
		std::wstring message;
		message.append (L"package_binder is expecting an equal number of arguments and results, have: ");
		std::wstringstream stream;
		stream << argument_count;
		message.append (stream.str ());
		message.append (L" arguments and: ");
		std::wstringstream stream2;
		stream2 << result_count;
		message.append (stream2.str ());
		message.append (L" results\n");
		add_error (message, problems);
	}
}

void lambda_p_kernel::package::parse_one (lambda_p::binder::list & nodes, boost::shared_ptr < lambda_p_kernel::nodes::data> node, size_t result, lambda_p::errors::error_list & problems)
{
	boost::shared_ptr <lambda_p::binder::node> current_node (shared_from_this ());
	boost::shared_ptr <lambda_p_kernel::package> current_package (shared_from_this ());
	std::wstring string (node->string ());
	boost::char_separator <wchar_t> separator (L"/");
	boost::tokenizer <boost::char_separator <wchar_t>, std::wstring::const_iterator, std::wstring> tokenizer (string, separator);
	std::wstring current_string;
	for (boost::tokenizer <boost::char_separator <wchar_t>, std::wstring::const_iterator, std::wstring>::iterator i = tokenizer.begin (); current_node.get () != nullptr && i != tokenizer.end (); ++i)
	{
		if (current_package.get () != nullptr)
		{
			current_string = *i;
			std::map <std::wstring, boost::shared_ptr <lambda_p::binder::node>>::iterator target = current_package->nodes.find (current_string);
			if (target != current_package->nodes.end ())
			{
				current_node = target->second;
				current_package = boost::dynamic_pointer_cast <lambda_p_kernel::package> (current_node);
			}
			else
			{
                current_node.reset ();
				std::wstring message;
				message.append (L"package_binder has no member named: ");
				message.append (current_string);
				add_error (message, problems);
			}
		}
		else
		{
            current_node.reset ();
			std::wstring message;
			message.append (L"package_binder member named: ");
			message.append (current_string);
			add_error (message, problems);
		}
	}
	if (current_node.get () != nullptr)
	{
		nodes [result] = current_node;
	}
}

std::wstring lambda_p_kernel::package::binder_name ()
{
	return std::wstring (L"package_binder");
}