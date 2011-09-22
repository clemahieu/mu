#define __STDC_LIMIT_MACROS

#include "constant_int_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/node.h>
#include <lambda_p/core/data.h>
#include <lambda_p_llvm/value.h>
#include <lambda_p_llvm/generation_context.h>

#include <llvm/Constants.h>
#include <llvm/Type.h>

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

void lambda_p_llvm::constant_int_binder::bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::wstringstream & problems)	
{
	size_t argument_count (statement->arguments.size ());
	if (argument_count == 4)
	{
		::lambda_p::core::node * declaration_node (statement->arguments [1]);
		::lambda_p::core::node_id declaration_id (declaration_node->node_type ());
		switch (declaration_id)
		{
		case ::lambda_p::core::node_declaration:
			{
				::lambda_p::core::node * base_node (statement->arguments [2]);
				::lambda_p::core::node_id base_id (base_node->node_type ());
				switch (base_id)
				{
				case ::lambda_p::core::node_data:
					{
						::lambda_p::core::node * number_node (statement->arguments [3]);
						::lambda_p::core::node_id number_id (number_node->node_type ());
						switch (number_id)
						{
						case ::lambda_p::core::node_data:
							{
								parse_nodes (base_node, number_node, declaration_node, instances, problems);
							}
							break;
						default:
							problems << L"constant_int_binder expects argument 3 to be data, have: ";
							problems << number_node->node_type_name ();
							problems << '\n';
							break;
						}
					}
					break;
				default:
					problems << L"constant_int_binder expects argument 2 to be data, have: ";
					problems << base_node->node_type_name ();
					problems << '\n';
					break;
				}
			}
			break;
		default:
			problems << L"constant_int_binder expects argument 1 to be a declaration, have: ";
			problems << declaration_node->node_type_name ();
			problems << '\n';
			break;
		}
	}
	else
	{
		problems << L"constant_int_binder is expecting 2 arguments, have: ";
		problems << argument_count;
		problems << '\n';
	}
}

void lambda_p_llvm::constant_int_binder::parse_number (unsigned long base, ::std::wstring & number_wstring, ::lambda_p::core::node * declaration_node, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::wstringstream & problems)
{
	wchar_t * next;
	wchar_t const * string (number_wstring.c_str ());
	errno = 0;
	unsigned long number = ::std::wcstol (string, &next, base);
	if (base == 0 && string == next)
	{
		problems << L"constant_int_binder was unable to parse number: ";
		problems << number_wstring;
		problems << '\n';
	}
	else if (errno == ERANGE)
	{
		problems << L"constant_int_binder number overflowed\n";
	}
	else
	{
		::boost::shared_ptr < ::lambda_p_llvm::value> value (new ::lambda_p_llvm::value (::llvm::ConstantInt::get (::llvm::Type::getInt64Ty (context.context), number)));
		instances [declaration_node] = value;
	}
}

void lambda_p_llvm::constant_int_binder::parse_nodes (::lambda_p::core::node * base_node, ::lambda_p::core::node * number_node, ::lambda_p::core::node * declaration_node, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::wstringstream & problems)
{
	::lambda_p::core::data * base_data (static_cast < ::lambda_p::core::data *> (base_node));
	::lambda_p::core::data * number_data (static_cast < ::lambda_p::core::data *> (number_node));
	::std::wstring base_wstring (base_data->string ());
	::std::wstring number_wstring (number_data->string ());
	wchar_t * next;
	wchar_t const * string (base_wstring.c_str ());
	unsigned long base = ::std::wcstol (string, &next, 10);
	if (base == 0 && string == next)
	{
		problems << L"constant_int_binder was unable to parse base: ";
		problems << base_wstring;
		problems << '\n';
	}
	else
	{
		if (base >= 2 && base <= 36)
		{
			parse_number (base, number_wstring, declaration_node, instances, problems);
		}
		else
		{
			problems << L"constant_int_binder has a base that's not between 2 and 36, inclusive\n";
		}
	}
}