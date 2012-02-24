#include "operation.h"

#include <core/errors/error_list.h>
#include <lambda_p_llvm/ccall/operation.h>
#include <lambda_p_llvm/basic_block/node.h>
#include <lambda_p_llvm/basic_block/split_return.h>
#include <lambda_p_llvm/basic_block/instruction_insert.h>
#include <lambda_p_llvm/instructions/call.h>
#include <lambda_p_llvm/value/node.h>
#include <lambda_p_llvm/integer_type/node.h>
#include <lambda_p_llvm/function/node.h>
#include <lambda_p_llvm/function_type/node.h>
#include <lambda_p_llvm/pointer_type/node.h>
#include <lambda_p_llvm/context/node.h>
#include <lambda_p_llvm/void_type/node.h>
#include <lambda_p_llvm/module/print.h>
#include <lambda_p_llvm/module/verify.h>
#include <lambda_p_llvm/module/node.h>
#include <lambda_p_llvm/set_type/node.h>

#include <boost/make_shared.hpp>

#include <llvm/LLVMContext.h>
#include <llvm/BasicBlock.h>
#include <llvm/Module.h>
#include <llvm/Function.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Constants.h>
#include <llvm/Instructions.h>

void lambda_p_llvm_test::ccall::operation::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
}

void lambda_p_llvm_test::ccall::operation::run_1 ()
{
	auto errors (boost::make_shared <mu::core::errors::error_list> ());
	llvm::LLVMContext context;
	llvm::Module module (llvm::StringRef (), context);
	auto mod (boost::make_shared <lambda_p_llvm::module::node> (&module));
	auto ctx (boost::make_shared <lambda_p_llvm::context::node> (&context));
	auto function (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (context), false), llvm::GlobalValue::ExternalLinkage, llvm::Twine (), &module));
	auto block (llvm::BasicBlock::Create (context, llvm::Twine (), function));
	auto bl (boost::make_shared <lambda_p_llvm::basic_block::node> (block));
	lambda_p_llvm::ccall::operation ccall (bl, boost::make_shared <lambda_p_llvm::basic_block::split_return> (bl, boost::make_shared <lambda_p_llvm::basic_block::instruction_insert> (bl, boost::make_shared <lambda_p_llvm::instructions::call> ())));
	std::vector <boost::shared_ptr <mu::core::node>> a1;
	std::vector <boost::shared_ptr <mu::core::node>> r1;
	auto bool_l (boost::make_shared <lambda_p_llvm::value::node> (llvm::ConstantInt::get (context, llvm::APInt (1, 0)), boost::make_shared <lambda_p_llvm::integer_type::node> (llvm::Type::getInt1Ty (context))));
	a1.push_back (bool_l);
	auto true_function (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (context), false), llvm::GlobalValue::ExternalLinkage, llvm::Twine (), &module));
	auto true_fn (boost::make_shared <lambda_p_llvm::function::node> (true_function, boost::make_shared <lambda_p_llvm::pointer_type::node> (boost::make_shared <lambda_p_llvm::function_type::node> (ctx, std::vector <boost::shared_ptr <lambda_p_llvm::type::node>> (), boost::make_shared <lambda_p_llvm::void_type::node> (ctx)))));
	a1.push_back (true_fn);
	auto false_function (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (context), false), llvm::GlobalValue::ExternalLinkage, llvm::Twine (), &module));
	auto false_fn (boost::make_shared <lambda_p_llvm::function::node> (false_function, boost::make_shared <lambda_p_llvm::pointer_type::node> (boost::make_shared <lambda_p_llvm::function_type::node> (ctx, std::vector <boost::shared_ptr <lambda_p_llvm::type::node>> (), boost::make_shared <lambda_p_llvm::void_type::node> (ctx)))));
	a1.push_back (false_fn);
	ccall.perform (errors, a1, r1);
	assert (errors->errors.empty ());	
	assert (r1.size () == 0);
	bl->block->getInstList ().push_back (llvm::ReturnInst::Create (context));
	lambda_p_llvm::module::print print;
	std::vector <boost::shared_ptr <mu::core::node>> a3;
	std::vector <boost::shared_ptr <mu::core::node>> r3;
	a3.push_back (mod);
	print (errors, a3, r3);
	lambda_p_llvm::module::verify verify;
	verify (errors, a3, r3);
	assert (errors->errors.empty ());
}

void lambda_p_llvm_test::ccall::operation::run_2 ()
{
	auto errors (boost::make_shared <mu::core::errors::error_list> ());
	llvm::LLVMContext context;
	llvm::Module module (llvm::StringRef (), context);
	auto mod (boost::make_shared <lambda_p_llvm::module::node> (&module));
	auto ctx (boost::make_shared <lambda_p_llvm::context::node> (&context));
	auto function (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getInt1Ty (context), false), llvm::GlobalValue::ExternalLinkage, llvm::Twine (), &module));
	auto block (llvm::BasicBlock::Create (context, llvm::Twine (), function));
	auto bl (boost::make_shared <lambda_p_llvm::basic_block::node> (block));
	lambda_p_llvm::ccall::operation ccall (bl, boost::make_shared <lambda_p_llvm::basic_block::split_return> (bl, boost::make_shared <lambda_p_llvm::basic_block::instruction_insert> (bl, boost::make_shared <lambda_p_llvm::instructions::call> ())));
	std::vector <boost::shared_ptr <mu::core::node>> a1;
	std::vector <boost::shared_ptr <mu::core::node>> r1;
	auto bool_l (boost::make_shared <lambda_p_llvm::value::node> (llvm::ConstantInt::get (context, llvm::APInt (1, 0)), boost::make_shared <lambda_p_llvm::integer_type::node> (llvm::Type::getInt1Ty (context))));
	a1.push_back (bool_l);
	auto true_function (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getInt1Ty (context), false), llvm::GlobalValue::ExternalLinkage, llvm::Twine (), &module));
	auto true_fn (boost::make_shared <lambda_p_llvm::function::node> (true_function, boost::make_shared <lambda_p_llvm::pointer_type::node> (boost::make_shared <lambda_p_llvm::function_type::node> (ctx, std::vector <boost::shared_ptr <lambda_p_llvm::type::node>> (), boost::make_shared <lambda_p_llvm::integer_type::node> (llvm::Type::getInt1Ty (context))))));
	a1.push_back (true_fn);
	auto false_function (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getInt1Ty (context), false), llvm::GlobalValue::ExternalLinkage, llvm::Twine (), &module));
	auto false_fn (boost::make_shared <lambda_p_llvm::function::node> (false_function, boost::make_shared <lambda_p_llvm::pointer_type::node> (boost::make_shared <lambda_p_llvm::function_type::node> (ctx, std::vector <boost::shared_ptr <lambda_p_llvm::type::node>> (), boost::make_shared <lambda_p_llvm::integer_type::node> (llvm::Type::getInt1Ty (context))))));
	a1.push_back (false_fn);
	ccall.perform (errors, a1, r1);
	assert (errors->errors.empty ());	
	assert (r1.size () == 1);
	auto value (boost::dynamic_pointer_cast <lambda_p_llvm::value::node> (r1 [0]));
	assert (value.get () != nullptr);
	bl->block->getInstList ().push_back (llvm::ReturnInst::Create (context, value->value ()));
	lambda_p_llvm::module::print print;
	std::vector <boost::shared_ptr <mu::core::node>> a3;
	std::vector <boost::shared_ptr <mu::core::node>> r3;
	a3.push_back (mod);
	print (errors, a3, r3);
	lambda_p_llvm::module::verify verify;
	verify (errors, a3, r3);
	assert (errors->errors.empty ());
}

void lambda_p_llvm_test::ccall::operation::run_3 ()
{
	auto errors (boost::make_shared <mu::core::errors::error_list> ());
	llvm::LLVMContext context;
	llvm::Module module (llvm::StringRef (), context);
	auto mod (boost::make_shared <lambda_p_llvm::module::node> (&module));
	auto ctx (boost::make_shared <lambda_p_llvm::context::node> (&context));
	auto result_type (boost::make_shared <lambda_p_llvm::set_type::node> (ctx));
	result_type->elements.push_back (boost::make_shared <lambda_p_llvm::integer_type::node> (llvm::Type::getInt1Ty (context)));
	result_type->elements.push_back (boost::make_shared <lambda_p_llvm::integer_type::node> (llvm::Type::getInt1Ty (context)));
	auto function (llvm::Function::Create (llvm::FunctionType::get (result_type->type (), false), llvm::GlobalValue::ExternalLinkage, llvm::Twine (), &module));
	auto block (llvm::BasicBlock::Create (context, llvm::Twine (), function));
	auto bl (boost::make_shared <lambda_p_llvm::basic_block::node> (block));
	lambda_p_llvm::ccall::operation ccall (bl, boost::make_shared <lambda_p_llvm::basic_block::split_return> (bl, boost::make_shared <lambda_p_llvm::basic_block::instruction_insert> (bl, boost::make_shared <lambda_p_llvm::instructions::call> ())));
	std::vector <boost::shared_ptr <mu::core::node>> a1;
	std::vector <boost::shared_ptr <mu::core::node>> r1;
	auto bool_l (boost::make_shared <lambda_p_llvm::value::node> (llvm::ConstantInt::get (context, llvm::APInt (1, 0)), boost::make_shared <lambda_p_llvm::integer_type::node> (llvm::Type::getInt1Ty (context))));
	a1.push_back (bool_l);
	auto true_function (llvm::Function::Create (llvm::FunctionType::get (result_type->type (), false), llvm::GlobalValue::ExternalLinkage, llvm::Twine (), &module));
	auto true_fn (boost::make_shared <lambda_p_llvm::function::node> (true_function, boost::make_shared <lambda_p_llvm::pointer_type::node> (boost::make_shared <lambda_p_llvm::function_type::node> (ctx, std::vector <boost::shared_ptr <lambda_p_llvm::type::node>> (), result_type))));
	a1.push_back (true_fn);
	auto false_function (llvm::Function::Create (llvm::FunctionType::get (result_type->type (), false), llvm::GlobalValue::ExternalLinkage, llvm::Twine (), &module));
	auto false_fn (boost::make_shared <lambda_p_llvm::function::node> (false_function, boost::make_shared <lambda_p_llvm::pointer_type::node> (boost::make_shared <lambda_p_llvm::function_type::node> (ctx, std::vector <boost::shared_ptr <lambda_p_llvm::type::node>> (), result_type))));
	a1.push_back (false_fn);
	ccall.perform (errors, a1, r1);
	assert (errors->errors.empty ());	
	assert (r1.size () == 2);
	auto value1 (boost::dynamic_pointer_cast <lambda_p_llvm::value::node> (r1 [0]));
	assert (value1.get () != nullptr);
	auto value2 (boost::dynamic_pointer_cast <lambda_p_llvm::value::node> (r1 [0]));
	assert (value2.get () != nullptr);
	llvm::Value * result (llvm::ConstantAggregateZero::get (result_type->type ()));
	result = llvm::InsertValueInst::Create (result, value1->value (), 0, llvm::Twine (), bl->block);
	result = llvm::InsertValueInst::Create (result, value2->value (), 1, llvm::Twine (), bl->block);
	bl->block->getInstList ().push_back (llvm::ReturnInst::Create (context, result));
	lambda_p_llvm::module::print print;
	std::vector <boost::shared_ptr <mu::core::node>> a3;
	std::vector <boost::shared_ptr <mu::core::node>> r3;
	a3.push_back (mod);
	print (errors, a3, r3);
	lambda_p_llvm::module::verify verify;
	verify (errors, a3, r3);
	assert (errors->errors.empty ());
}