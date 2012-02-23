#include "call.h"

#include <lambda_p/errors/error_list.h>
#include <lambda_p_llvm/instructions/call.h>
#include <lambda_p_llvm/value/node.h>
#include <lambda_p_llvm/pointer_type/node.h>
#include <lambda_p_llvm/context/node.h>
#include <lambda_p_llvm/function_type/node.h>
#include <lambda_p_llvm/integer_type/node.h>
#include <lambda_p_llvm/constant_int/node.h>
#include <lambda_p_llvm/void_type/node.h>
#include <lambda_p_llvm/set_type/node.h>
#include <lambda_p_llvm/instruction/node.h>

#include <boost/make_shared.hpp>

#include <llvm/Constants.h>
#include <llvm/LLVMContext.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Module.h>

void lambda_p_llvm_test::instructions::call::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
}

void lambda_p_llvm_test::instructions::call::run_1 ()
{
	auto errors (boost::make_shared <lambda_p::errors::error_list> ());
	llvm::LLVMContext context;
	auto ctx (boost::make_shared <lambda_p_llvm::context::node> (&context));
	std::vector <boost::shared_ptr <lambda_p_llvm::type::node>> arguments;
	arguments.push_back (boost::make_shared <lambda_p_llvm::integer_type::node> (llvm::Type::getInt1Ty (context)));
	auto type (boost::make_shared <lambda_p_llvm::pointer_type::node> (boost::make_shared <lambda_p_llvm::function_type::node> (ctx, arguments, boost::make_shared <lambda_p_llvm::integer_type::node> (llvm::Type::getInt1Ty (context)))));
	std::vector <boost::shared_ptr <lambda_p::node>> a1;
	a1.push_back (boost::make_shared <lambda_p_llvm::value::node> (llvm::ConstantPointerNull::get (type->pointer_type ()), type));
	std::vector <boost::shared_ptr <lambda_p::node>> r1;
	lambda_p_llvm::instructions::call call;
	call.perform (errors, a1, r1);
	assert (!errors->errors.empty ());
}

void lambda_p_llvm_test::instructions::call::run_2 ()
{
	auto errors (boost::make_shared <lambda_p::errors::error_list> ());
	llvm::LLVMContext context;
	auto ctx (boost::make_shared <lambda_p_llvm::context::node> (&context));
	std::vector <boost::shared_ptr <lambda_p_llvm::type::node>> arguments;
	arguments.push_back (boost::make_shared <lambda_p_llvm::integer_type::node> (llvm::Type::getInt1Ty (context)));
	auto type (boost::make_shared <lambda_p_llvm::pointer_type::node> (boost::make_shared <lambda_p_llvm::function_type::node> (ctx, arguments, boost::make_shared <lambda_p_llvm::integer_type::node> (llvm::Type::getInt1Ty (context)))));
	std::vector <boost::shared_ptr <lambda_p::node>> a1;
	a1.push_back (boost::make_shared <lambda_p_llvm::value::node> (llvm::ConstantPointerNull::get (type->pointer_type ()), type));
	a1.push_back (boost::make_shared <lambda_p_llvm::constant_int::node> (llvm::ConstantInt::get (llvm::Type::getInt16Ty (context), 0, false), boost::make_shared <lambda_p_llvm::integer_type::node> (llvm::Type::getInt16Ty (context))));
	std::vector <boost::shared_ptr <lambda_p::node>> r1;
	lambda_p_llvm::instructions::call call;
	call.perform (errors, a1, r1);
	assert (!errors->errors.empty ());
}

void lambda_p_llvm_test::instructions::call::run_3 ()
{
	auto errors (boost::make_shared <lambda_p::errors::error_list> ());
	llvm::LLVMContext context;
	auto ctx (boost::make_shared <lambda_p_llvm::context::node> (&context));
	auto type (boost::make_shared <lambda_p_llvm::pointer_type::node> (boost::make_shared <lambda_p_llvm::function_type::node> (ctx, std::vector <boost::shared_ptr <lambda_p_llvm::type::node>> (), boost::make_shared <lambda_p_llvm::integer_type::node> (llvm::Type::getInt1Ty (context)))));
	std::vector <boost::shared_ptr <lambda_p::node>> a1;
	a1.push_back (boost::make_shared <lambda_p_llvm::value::node> (llvm::ConstantPointerNull::get (type->pointer_type ()), type));
	std::vector <boost::shared_ptr <lambda_p::node>> r1;
	lambda_p_llvm::instructions::call call;
	call.perform (errors, a1, r1);
	assert (errors->errors.empty ());
	assert (r1.size () == 1);
	llvm::Module module (llvm::StringRef (), context);
	auto function (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (context), false), llvm::GlobalValue::ExternalLinkage, llvm::Twine (), &module));
	auto block (llvm::BasicBlock::Create (context, llvm::Twine (), function));
	block->getInstList ().push_back (boost::static_pointer_cast <lambda_p_llvm::instruction::node> (r1 [0])->instruction ());
}

void lambda_p_llvm_test::instructions::call::run_4 ()
{
	auto errors (boost::make_shared <lambda_p::errors::error_list> ());
	llvm::LLVMContext context;
	auto ctx (boost::make_shared <lambda_p_llvm::context::node> (&context));
	auto type (boost::make_shared <lambda_p_llvm::pointer_type::node> (boost::make_shared <lambda_p_llvm::function_type::node> (ctx, std::vector <boost::shared_ptr <lambda_p_llvm::type::node>> (), boost::make_shared <lambda_p_llvm::void_type::node> (ctx))));
	std::vector <boost::shared_ptr <lambda_p::node>> a1;
	std::vector <boost::shared_ptr <lambda_p::node>> r1;
	lambda_p_llvm::instructions::call call;
	call.perform (errors, a1, r1);
	assert (!errors->errors.empty ());
}