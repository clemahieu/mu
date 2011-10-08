#define __STDC_LIMIT_MACROS

#include "constant_int_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/binder/data.h>
#include <lambda_p_llvm/literal_value.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p/core/association.h>
#include <lambda_p/errors/unexpected_binder_type.h>
#include <lambda_p/binder/routine_instances.h>

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

void lambda_p_llvm::constant_int_binder::bind (::lambda_p::core::statement * statement, ::lambda_p::binder::routine_instances & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)	
{
	check_count (1, 3, statement, problems);
	if (problems.empty ())
	{
		::boost::shared_ptr < ::lambda_p::binder::data> base_data (::boost::dynamic_pointer_cast < ::lambda_p::binder::data> (instances [statement->association->parameters [0]]));
		if (base_data.get () != NULL)
		{
			::boost::shared_ptr < ::lambda_p::binder::data> number_data (::boost::dynamic_pointer_cast < ::lambda_p::binder::data> (instances [statement->association->parameters [1]]));
			if (number_data.get () != NULL)
			{
				::boost::shared_ptr < ::lambda_p::binder::data> bits_data (::boost::dynamic_pointer_cast < ::lambda_p::binder::data> (instances [statement->association->parameters [2]]));
				if (bits_data.get () != NULL)
				{
					parse_nodes (base_data, number_data, bits_data, statement->association->results [0], instances, problems);
				}
				else
				{
					problems.push_back (::boost::shared_ptr < ::lambda_p::errors::error> (new ::lambda_p::errors::unexpected_binder_type (binder_name (), 0, ::std::wstring (L"data"))));
				}
			}
			else
			{
				problems.push_back (::boost::shared_ptr < ::lambda_p::errors::error> (new ::lambda_p::errors::unexpected_binder_type (binder_name (), 0, ::std::wstring (L"data"))));
			}
		}
		else
		{
			problems.push_back (::boost::shared_ptr < ::lambda_p::errors::error> (new ::lambda_p::errors::unexpected_binder_type (binder_name (), 0, ::std::wstring (L"data"))));
		}
	}
}

void lambda_p_llvm::constant_int_binder::parse_number (unsigned long base, unsigned long bits, ::std::wstring & number_wstring, size_t declaration_node, ::lambda_p::binder::routine_instances & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
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
		::boost::shared_ptr < ::lambda_p_llvm::value> value (new ::lambda_p_llvm::literal_value (::llvm::ConstantInt::get (::llvm::IntegerType::get (context.context, bits), number)));
		instances [declaration_node] = value;
	}
}

void lambda_p_llvm::constant_int_binder::parse_nodes (::boost::shared_ptr < ::lambda_p::binder::data> base_data, ::boost::shared_ptr < ::lambda_p::binder::data> number_data, ::boost::shared_ptr < ::lambda_p::binder::data> bits_data, size_t declaration_node, ::lambda_p::binder::routine_instances & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
{
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