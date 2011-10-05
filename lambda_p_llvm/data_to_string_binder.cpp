#define __STDC_LIMIT_MACROS

#include "data_to_string_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/node.h>
#include <lambda_p/binder/data.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p_llvm/value.h>
#include <lambda_p_llvm/constant_wstring.h>
#include <lambda_p/core/declaration.h>
#include <lambda_p/core/association.h>
#include <lambda_p/errors/unexpected_node_type.h>

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

void lambda_p_llvm::data_to_string_binder::bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
{
	check_count (1, 1, statement, problems);
	if (problems.empty ())
	{
		::lambda_p::core::node_id arg2_type (statement->association->parameters [0]->node_type ());
		switch (arg2_type)
		{
		case ::lambda_p::core::node_data:
			{
				::lambda_p::binder::data * data (static_cast < ::lambda_p::binder::data *> (statement->association->parameters [0]));
				::lambda_p_llvm::constant_wstring string (context, data->string ());                        
				::boost::shared_ptr < ::lambda_p_llvm::value> value (new ::lambda_p_llvm::value (string.value));
				instances [statement->association->results [0]] = value;
			}
			break;
		default:
			problems.push_back (::boost::shared_ptr < ::lambda_p::errors::error> (new ::lambda_p::errors::unexpected_node_type (binder_name (), 0, arg2_type)));
			break;
		}
	}
}

::std::wstring lambda_p_llvm::data_to_string_binder::binder_name ()
{
	return ::std::wstring (L"data_to_string_binder");
}