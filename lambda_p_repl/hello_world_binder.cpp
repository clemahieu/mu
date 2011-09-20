#include "hello_world_binder.h"

#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS

#include <lambda_p/core/statement.h>
#include <lambda_p/binder/command_list.h>

#include <llvm/Instructions.h>
#include <llvm/GlobalValue.h>
#include <llvm/GlobalVariable.h>
#include <llvm/Module.h>

#include <sstream>

lambda_p_repl::hello_world_binder::hello_world_binder (::llvm::Value * wprintf_a, ::lambda_p_llvm::llvm_generation_context context_a)
	: wprintf (wprintf_a),
    context (context_a)
{
}

lambda_p_repl::hello_world_binder::~hello_world_binder (void)
{
}

void lambda_p_repl::hello_world_binder::bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::wstringstream & problems)
{
	size_t argument_count (statement->arguments.size ());
	if (argument_count == 1)
	{
        ::std::wstring string (L"Hello world in llvm!\n");
		::llvm::ArrayType * type (::llvm::ArrayType::get (context.wchar_t_type, string.size () + 1));
        ::std::vector < ::llvm::Constant *> initializer;
        for (::std::wstring::iterator i = string.begin (); i != string.end (); ++i)
        {
			initializer.push_back (::llvm::ConstantInt::get (context.wchar_t_type, *i));
        }        
		initializer.push_back (::llvm::ConstantInt::get (context.wchar_t_type, 0));
        ::llvm::Constant * array (::llvm::ConstantArray::get (type, initializer));
        ::llvm::GlobalVariable * string_global (new ::llvm::GlobalVariable (type, true, ::llvm::GlobalValue::ExternalLinkage, array));
        context.module->getGlobalList ().push_back (string_global);
		::llvm::CastInst * cast (::llvm::CastInst::CreatePointerCast (string_global, ::llvm::PointerType::get (context.wchar_t_type, 0)));
		context.block->getInstList ().push_back (cast);
        ::std::vector < ::llvm::Value *> arguments;
        arguments.push_back (cast);
        ::llvm::CallInst * call (::llvm::CallInst::Create (wprintf, arguments.begin (), arguments.end ()));
        context.block->getInstList ().push_back (call);
	}
	else
	{
		problems << L"hello_world is expecting no arguments, have: ";
		problems << argument_count - 1;
		problems << '\n';
	}
}

void lambda_p_repl::hello_world_binder::operator () ()
{
}