#include "call.h"

#include <mu/core/errors/error_list.h>
#include <mu/llvm_/instructions/call.h>
#include <mu/llvm_/value/node.h>
#include <mu/llvm_/pointer_type/node.h>
#include <mu/llvm_/context/node.h>
#include <mu/llvm_/function_type/node.h>
#include <mu/llvm_/integer_type/node.h>
#include <mu/llvm_/constant_int/node.h>
#include <mu/llvm_/void_type/node.h>
#include <mu/llvm_/set_type/node.h>
#include <mu/llvm_/instruction/node.h>

#include <boost/make_shared.hpp>

#include <llvm/Constants.h>
#include <llvm/LLVMContext.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Module.h>

void mu::llvm_test::instructions::call::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
}

void mu::llvm_test::instructions::call::run_1 ()
{
	auto errors (boost::make_shared <mu::core::errors::error_list> ());
	llvm::LLVMContext context;
	auto ctx (boost::make_shared <mu::llvm_::context::node> (&context));
	std::vector <boost::shared_ptr <mu::llvm_::type::node>> arguments;
	arguments.push_back (boost::make_shared <mu::llvm_::integer_type::node> (llvm::Type::getInt1Ty (context)));
	auto type (boost::make_shared <mu::llvm_::pointer_type::node> (boost::make_shared <mu::llvm_::function_type::node> (ctx, arguments, boost::make_shared <mu::llvm_::integer_type::node> (llvm::Type::getInt1Ty (context)))));
	std::vector <boost::shared_ptr <mu::core::node>> a1;
	a1.push_back (boost::make_shared <mu::llvm_::value::node> (llvm::ConstantPointerNull::get (type->pointer_type ()), type));
	std::vector <boost::shared_ptr <mu::core::node>> r1;
	mu::llvm_::instructions::call call;
	call.perform (errors, a1, r1);
	assert (!errors->errors.empty ());
}

void mu::llvm_test::instructions::call::run_2 ()
{
	auto errors (boost::make_shared <mu::core::errors::error_list> ());
	llvm::LLVMContext context;
	auto ctx (boost::make_shared <mu::llvm_::context::node> (&context));
	std::vector <boost::shared_ptr <mu::llvm_::type::node>> arguments;
	arguments.push_back (boost::make_shared <mu::llvm_::integer_type::node> (llvm::Type::getInt1Ty (context)));
	auto type (boost::make_shared <mu::llvm_::pointer_type::node> (boost::make_shared <mu::llvm_::function_type::node> (ctx, arguments, boost::make_shared <mu::llvm_::integer_type::node> (llvm::Type::getInt1Ty (context)))));
	std::vector <boost::shared_ptr <mu::core::node>> a1;
	a1.push_back (boost::make_shared <mu::llvm_::value::node> (llvm::ConstantPointerNull::get (type->pointer_type ()), type));
	a1.push_back (boost::make_shared <mu::llvm_::constant_int::node> (llvm::ConstantInt::get (llvm::Type::getInt16Ty (context), 0, false), boost::make_shared <mu::llvm_::integer_type::node> (llvm::Type::getInt16Ty (context))));
	std::vector <boost::shared_ptr <mu::core::node>> r1;
	mu::llvm_::instructions::call call;
	call.perform (errors, a1, r1);
	assert (!errors->errors.empty ());
}

void mu::llvm_test::instructions::call::run_3 ()
{
	auto errors (boost::make_shared <mu::core::errors::error_list> ());
	llvm::LLVMContext context;
	auto ctx (boost::make_shared <mu::llvm_::context::node> (&context));
	auto type (boost::make_shared <mu::llvm_::pointer_type::node> (boost::make_shared <mu::llvm_::function_type::node> (ctx, std::vector <boost::shared_ptr <mu::llvm_::type::node>> (), boost::make_shared <mu::llvm_::integer_type::node> (llvm::Type::getInt1Ty (context)))));
	std::vector <boost::shared_ptr <mu::core::node>> a1;
	a1.push_back (boost::make_shared <mu::llvm_::value::node> (llvm::ConstantPointerNull::get (type->pointer_type ()), type));
	std::vector <boost::shared_ptr <mu::core::node>> r1;
	mu::llvm_::instructions::call call;
	call.perform (errors, a1, r1);
	assert (errors->errors.empty ());
	assert (r1.size () == 1);
	llvm::Module module (llvm::StringRef (), context);
	auto function (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (context), false), llvm::GlobalValue::ExternalLinkage, llvm::Twine (), &module));
	auto block (llvm::BasicBlock::Create (context, llvm::Twine (), function));
	block->getInstList ().push_back (boost::static_pointer_cast <mu::llvm_::instruction::node> (r1 [0])->instruction ());
}

void mu::llvm_test::instructions::call::run_4 ()
{
	auto errors (boost::make_shared <mu::core::errors::error_list> ());
	llvm::LLVMContext context;
	auto ctx (boost::make_shared <mu::llvm_::context::node> (&context));
	auto type (boost::make_shared <mu::llvm_::pointer_type::node> (boost::make_shared <mu::llvm_::function_type::node> (ctx, std::vector <boost::shared_ptr <mu::llvm_::type::node>> (), boost::make_shared <mu::llvm_::void_type::node> (ctx))));
	std::vector <boost::shared_ptr <mu::core::node>> a1;
	std::vector <boost::shared_ptr <mu::core::node>> r1;
	mu::llvm_::instructions::call call;
	call.perform (errors, a1, r1);
	assert (!errors->errors.empty ());
}