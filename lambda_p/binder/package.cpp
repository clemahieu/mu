#include "package.h"

#include <lambda_p/core/declaration.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/binder/data.h>
#include <lambda_p/core/association.h>
#include <lambda_p/errors/unexpected_node_type.h>

#include <boost/tokenizer.hpp>
#include <boost/array.hpp>

#include <sstream>

lambda_p::binder::package::package(void)
{
}

lambda_p::binder::package::~package(void)
{
}

void lambda_p::binder::package::bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
{
	bool problem (false);
	size_t argument_count (statement->association->parameters.size ());
	size_t result_count (statement->association->results.size ());
	if (argument_count == result_count)
	{
		size_t current_argument (0);
		for (::std::vector < ::lambda_p::core::node *>::iterator i = statement->association->parameters.begin (); i != statement->association->parameters.end (); ++i, ++current_argument)
		{
			::lambda_p::core::node * parameter (*i);
			::lambda_p::core::node_id argument_1_id (parameter->node_type ());
			switch (argument_1_id)
			{
			case ::lambda_p::core::node_data:
				{
					parse_one (instances, parameter, statement->association->results [current_argument], problems);
				}
				break;
			default:
				problems.push_back (::boost::shared_ptr < ::lambda_p::errors::error> (new ::lambda_p::errors::unexpected_node_type (binder_name (), 0, argument_1_id)));
				break;
			}
		}
	}
	else
	{
		::std::wstring message;
		message.append (L"package_binder is expecting an equal number of arguments and results, have: ");
		::std::wstringstream stream;
		stream << argument_count;
		message.append (stream.str ());
		message.append (L" arguments and: ");
		::std::wstringstream stream2;
		stream2 << result_count;
		message.append (stream2.str ());
		message.append (L" results\n");
		add_error (message, problems);
	}
}

void lambda_p::binder::package::parse_one (::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::lambda_p::core::node * node, ::lambda_p::core::declaration * result, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
{
	::boost::shared_ptr < ::lambda_p::binder::node_instance> current_node (shared_from_this ());
	::boost::shared_ptr < ::lambda_p::binder::package> current_package (shared_from_this ());
	::lambda_p::binder::data * name (static_cast < ::lambda_p::binder::data *> (node));
	::std::wstring string (name->string ());
	::boost::char_separator <wchar_t> separator (L".");
	::boost::tokenizer < ::boost::char_separator <wchar_t>, ::std::wstring::const_iterator, ::std::wstring> tokenizer (string, separator);
	::std::wstring current_string;
	for (::boost::tokenizer < ::boost::char_separator <wchar_t>, ::std::wstring::const_iterator, ::std::wstring>::iterator i = tokenizer.begin (); current_node.get () != NULL && i != tokenizer.end (); ++i)
	{
		if (current_package.get () != NULL)
		{
			current_string = *i;
			::std::map < ::std::wstring, ::boost::shared_ptr < ::lambda_p::binder::node_instance> >::iterator target = current_package->nodes.find (current_string);
			if (target != current_package->nodes.end ())
			{
				current_node = target->second;
				current_package = ::boost::dynamic_pointer_cast < ::lambda_p::binder::package> (current_node);
			}
			else
			{
                current_node.reset ();
				::std::wstring message;
				message.append (L"package_binder has no member named: ");
				message.append (current_string);
				add_error (message, problems);
			}
		}
		else
		{
            current_node.reset ();
			::std::wstring message;
			message.append (L"package_binder member named: ");
			message.append (current_string);
			add_error (message, problems);
		}
	}
	if (current_node.get () != NULL)
	{
		instances [result] = current_node;
	}
}

::std::wstring lambda_p::binder::package::binder_name ()
{
	return ::std::wstring (L"package_binder");
}