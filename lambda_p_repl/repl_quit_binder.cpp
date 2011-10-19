#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS

#include "repl_quit_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/routine_instances.h>

#include <llvm/Instructions.h>
#include <llvm/BasicBlock.h>
#include <llvm/Function.h>

#include <string>
#include <sstream>

lambda_p_repl::repl_quit_binder::repl_quit_binder (::lambda_p_llvm::generation_context & context_a, ::llvm::Function * quit_function_a, ::llvm::Value * quit_object_a)
	: context (context_a),
	quit_function (quit_function_a),
    quit_object (quit_object_a)
{
}

lambda_p_repl::repl_quit_binder::~repl_quit_binder (void)
{
}

void lambda_p_repl::repl_quit_binder::bind (::lambda_p::core::statement * statement, lambda_p::binder::routine_instances & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
{
    check_count (0, 0, statement, problems);
    if (problems.empty ())
    {
        ::std::vector < ::llvm::Value *> arguments;
        arguments.push_back (quit_object);
        ::llvm::CallInst * call (::llvm::CallInst::Create (quit_function, arguments.begin (), arguments.end ()));
        context.block->getInstList ().push_back (call);
	}
}

::std::wstring lambda_p_repl::repl_quit_binder::binder_name ()
{
	return ::std::wstring (L"repl_quit_binder");
}