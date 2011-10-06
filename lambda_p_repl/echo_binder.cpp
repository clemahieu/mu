#define __STDC_LIMIT_MACROS

#include "echo_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/binder/data.h>
#include <lambda_p_llvm/value.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p_llvm/constant_wstring.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/routine_instances.h>

#include <llvm/Constants.h>
#include <llvm/DerivedTypes.h>
#include <llvm/GlobalValue.h>
#include <llvm/GlobalVariable.h>
#include <llvm/Module.h>
#include <llvm/Instructions.h>

#include <sstream>

lambda_p_repl::echo_binder::echo_binder (::llvm::Value * wprintf_a, ::lambda_p_llvm::generation_context context_a)
	: context (context_a),
wprintf (wprintf_a)
{
    ::std::wstring str (L"%ls");
    ::lambda_p_llvm::constant_wstring string (context_a, str);
    echo_string_global = string.value;
}

lambda_p_repl::echo_binder::~echo_binder(void)
{
}

void lambda_p_repl::echo_binder::bind (::lambda_p::core::statement * statement, ::lambda_p::binder::routine_instances & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
{
	check_count_only_references (0, 1, statement, problems);
	if (problems.empty ())
	{
		::boost::shared_ptr < ::lambda_p_llvm::value> string (::boost::dynamic_pointer_cast < ::lambda_p_llvm::value> (instances [statement->association->parameters [0]]));
		if (string.get () != NULL)
		{
			::std::vector < ::llvm::Value *> arguments;
			arguments.push_back (echo_string_global);
			arguments.push_back (string->value_m);
			::llvm::CallInst * call (::llvm::CallInst::Create (wprintf, arguments.begin (), arguments.end ()));
			context.block->getInstList ().push_back (call);
		}
		else
		{
			add_error (::std::wstring (L"Argument 1 is not an llvm_value"), problems);
		}
	}
}

::std::wstring lambda_p_repl::echo_binder::binder_name ()
{
	return ::std::wstring (L"echo_binder");
}