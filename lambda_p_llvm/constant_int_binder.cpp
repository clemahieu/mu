#define __STDC_LIMIT_MACROS

#include "constant_int_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/node.h>
#include <lambda_p/binder/data.h>
#include <lambda_p_llvm/value.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p/core/declaration.h>
#include <lambda_p/core/association.h>
#include <lambda_p/errors/unexpected_node_type.h>

#include <llvm/Constants.h>
#include <llvm/DerivedTypes.h>

#include <wchar.h>
#include <errno.h>

#include <sstream>

lambda_p_llvm::constant_int_binder::constant_int_binder (::lambda_p_llvm::generation_context & context_a)
	: context (context_a)
{
}

lambda_p_llvm::constant_int_binder::~constant_int_binder(void)
{
}

void lambda_p_llvm::constant_int_binder::bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)	
{
	check_count (1, 3, statement, problems);
	if (problems.empty ())
	{
		::lambda_p::core::node * base_node (statement->association->parameters [0]);
		::lambda_p::core::node_id base_id (base_node->node_type ());
		switch (base_id)
		{
		case ::lambda_p::core::node_data:
			{
				::lambda_p::core::node * number_node (statement->association->parameters [1]);
				::lambda_p::core::node_id number_id (number_node->node_type ());
				switch (number_id)
				{
				case ::lambda_p::core::node_data:
					{
						::lambda_p::core::node * bits_node (statement->association->parameters [2]);
						::lambda_p::core::node_id bits_id (bits_node->node_type ());
						switch (bits_id)
						{
						case ::lambda_p::core::node_data:
							parse_nodes (base_node, number_node, bits_node, statement->association->results [0], instances, problems);
							break;
						default:
							problems.push_back (::boost::shared_ptr < ::lambda_p::errors::error> (new ::lambda_p::errors::unexpected_node_type (binder_name (), 0, bits_id)));
							break;
						}
					}
					break;
				default:
					problems.push_back (::boost::shared_ptr < ::lambda_p::errors::error> (new ::lambda_p::errors::unexpected_node_type (binder_name (), 0, number_id)));
					break;
				}
			}
			break;
		default:
			problems.push_back (::boost::shared_ptr < ::lambda_p::errors::error> (new ::lambda_p::errors::unexpected_node_type (binder_name (), 0, base_id)));
			break;
		}
	}
}

void lambda_p_llvm::constant_int_binder::parse_number (unsigned long base, unsigned long bits, ::std::wstring & number_wstring, ::lambda_p::core::node * declaration_node, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
{
	wchar_t * next;
	wchar_t const * string (number_wstring.c_str ());
	errno = 0;
	unsigned long number = ::std::wcstol (string, &next, (int)base);
	if (base == 0 && string == next)
	{
		::std::wstring message;
		message.append (L"constant_int_binder was unable to parse number: ");
		message.append (number_wstring);
		add_error (message, problems);
	}
	else if (errno == ERANGE)
	{
		add_error (::std::wstring (L"constant_int_binder number overflowed"), problems);
	}
	else
	{
		::boost::shared_ptr < ::lambda_p_llvm::value> value (new ::lambda_p_llvm::value (::llvm::ConstantInt::get (::llvm::IntegerType::get (context.context, bits), number)));
		instances [declaration_node] = value;
	}
}

void lambda_p_llvm::constant_int_binder::parse_nodes (::lambda_p::core::node * base_node, ::lambda_p::core::node * number_node, ::lambda_p::core::node * bits_node, ::lambda_p::core::node * declaration_node, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
{
	::lambda_p::binder::data * base_data (static_cast < ::lambda_p::binder::data *> (base_node));
	::lambda_p::binder::data * number_data (static_cast < ::lambda_p::binder::data *> (number_node));
	::lambda_p::binder::data * bits_data (static_cast < ::lambda_p::binder::data *> (bits_node));
	::std::wstring base_wstring (base_data->string ());
	::std::wstring number_wstring (number_data->string ());
	::std::wstring bits_wstring (bits_data->string ());
	wchar_t * next;
	wchar_t const * string (base_wstring.c_str ());
	unsigned long base = ::std::wcstol (string, &next, 10);
	if (base == 0 && string == next)
	{
		::std::wstring message;
		message.append (L"unable to parse base: ");
		message.append (base_wstring);
		add_error (message, problems);
	}
	else
	{
		wchar_t * bits_next;
		wchar_t const * bits_string (bits_wstring.c_str ());
		unsigned long bits = ::std::wcstol (bits_string, &bits_next, 10);
		if (bits == 0 && bits_string == bits_next)
		{
			::std::wstring message;
			message.append (L"unable to parse bits: ");
			message.append (bits_wstring);
			add_error (message, problems);
		}
		else
		{
			if (base >= 2 && base <= 36)
			{
				parse_number (base, bits, number_wstring, declaration_node, instances, problems);
			}
			else
			{
				add_error (::std::wstring (L"base is not between 2 and 36, inclusive"), problems);
			}
		}
	}
}

::std::wstring lambda_p_llvm::constant_int_binder::binder_name ()
{
	return ::std::wstring (L"constant_int_binder");
}