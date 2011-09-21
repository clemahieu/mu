#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS

#include "repl_quit_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/binder/command_list.h>
#include <lambda_p_llvm/generation_context.h>

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

void lambda_p_repl::repl_quit_binder::bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::wstringstream & problems)
{
	size_t argument_count (statement->arguments.size ());
	if (argument_count == 1)
	{
        ::std::vector < ::llvm::Value *> arguments;
        arguments.push_back (quit_object);
        ::llvm::CallInst * call (::llvm::CallInst::Create (quit_function, arguments.begin (), arguments.end ()));
        context.block->getInstList ().push_back (call);
	}
	else
	{
		problems << L"quit is expecting no arguments, have: ";
		problems << argument_count - 1;
		problems << '\n';
	}
}

void lambda_p_repl::repl_quit_binder::operator () ()
{
}