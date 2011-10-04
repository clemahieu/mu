#define __STDC_LIMIT_MACROS

#include "data_to_string_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/node.h>
#include <lambda_p/core/data.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p_llvm/value.h>
#include <lambda_p_llvm/constant_wstring.h>
#include <lambda_p/core/declaration.h>

#include <llvm/DerivedTypes.h>
#include <llvm/Constants.h>
#include <llvm/GlobalValue.h>
#include <llvm/GlobalVariable.h>
#include <llvm/Module.h>

#include <sstream>

lambda_p_llvm::data_to_string_binder::data_to_string_binder (::lambda_p_llvm::generation_context context_a)
: context (context_a)
{
}

lambda_p_llvm::data_to_string_binder::~data_to_string_binder (void)
{
}

void lambda_p_llvm::data_to_string_binder::bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::wstringstream & problems)
{
	bool problem (false);
	check_count (problem, 1, 1, L"data_to_string_binder", statement, problems);
	if (!problem)
	{
		::lambda_p::core::node_id arg2_type (statement->parameters [0]->node_type ());
		switch (arg2_type)
		{
		case ::lambda_p::core::node_data:
			{
				::lambda_p::core::data * data (static_cast < ::lambda_p::core::data *> (statement->parameters [0]));
				::lambda_p_llvm::constant_wstring string (context, data->string ());                        
				::boost::shared_ptr < ::lambda_p_llvm::value> value (new ::lambda_p_llvm::value (string.value));
				instances [statement->results [0]] = value;
			}
			break;
		default:
			problems << L"data_to_string_binder expecting argument 1 to be data, have: ";
			problems << statement->parameters [0]->node_type_name ();
			problems << '\n';
			break;
		}
	}
}