#include "operation.h"

#include <mu/core/errors/error_list.h>
#include <mu/llvm_/ccall/operation.h>
#include <mu/llvm_/basic_block/node.h>
#include <mu/llvm_/basic_block/split_return.h>
#include <mu/llvm_/basic_block/instruction_insert.h>
#include <mu/llvm_/instructions/call.h>
#include <mu/llvm_/value/node.h>
#include <mu/llvm_/integer_type/node.h>
#include <mu/llvm_/function/node.h>
#include <mu/llvm_/function_type/node.h>
#include <mu/llvm_/pointer_type/node.h>
#include <mu/llvm_/context/node.h>
#include <mu/llvm_/void_type/node.h>
#include <mu/llvm_/module/print.h>
#include <mu/llvm_/module/verify.h>
#include <mu/llvm_/module/node.h>
#include <mu/llvm_/set_type/node.h>
#include <mu/script/context.h>

#include <boost/make_shared.hpp>

#include <llvm/LLVMContext.h>
#include <llvm/BasicBlock.h>
#include <llvm/Module.h>
#include <llvm/Function.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Constants.h>
#include <llvm/Instructions.h>

void mu::llvm_test::ccall::operation::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
}

void mu::llvm_test::ccall::operation::run_1 ()
{
	mu::core::errors::errors errors (boost::make_shared <mu::core::errors::error_list> ());
	llvm::LLVMContext context;
	llvm::Module module (llvm::StringRef (), context);
	auto mod (boost::make_shared <mu::llvm_::module::node> (&module));
	auto ctx (boost::make_shared <mu::llvm_::context::node> (&context));
	auto function (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (context), false), llvm::GlobalValue::ExternalLinkage, llvm::Twine (), &module));
	auto block (llvm::BasicBlock::Create (context, llvm::Twine (), function));
	auto bl (boost::make_shared <mu::llvm_::basic_block::node> (block));
	mu::script::context ctx2 (errors);
	ctx2.push (boost::make_shared <mu::llvm_::ccall::operation> (bl, boost::make_shared <mu::llvm_::basic_block::split_return> (bl, boost::make_shared <mu::llvm_::basic_block::instruction_insert> (bl, boost::make_shared <mu::llvm_::instructions::call> ()))));
	auto bool_l (boost::make_shared <mu::llvm_::value::node> (llvm::ConstantInt::get (context, llvm::APInt (1, 0)), boost::make_shared <mu::llvm_::integer_type::node> (llvm::Type::getInt1Ty (context))));
	ctx2.push (bool_l);
	auto true_function (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (context), false), llvm::GlobalValue::ExternalLinkage, llvm::Twine (), &module));
	auto true_fn (boost::make_shared <mu::llvm_::function::node> (true_function, boost::make_shared <mu::llvm_::pointer_type::node> (boost::make_shared <mu::llvm_::function_type::node> (ctx, std::vector <boost::shared_ptr <mu::llvm_::type::node>> (), boost::make_shared <mu::llvm_::void_type::node> (ctx)))));
	ctx2.push (true_fn);
	auto false_function (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (context), false), llvm::GlobalValue::ExternalLinkage, llvm::Twine (), &module));
	auto false_fn (boost::make_shared <mu::llvm_::function::node> (false_function, boost::make_shared <mu::llvm_::pointer_type::node> (boost::make_shared <mu::llvm_::function_type::node> (ctx, std::vector <boost::shared_ptr <mu::llvm_::type::node>> (), boost::make_shared <mu::llvm_::void_type::node> (ctx)))));
	ctx2.push (false_fn);
	auto valid (ctx2 ());
	assert (ctx2.working_size () == 0);
	bl->block->getInstList ().push_back (llvm::ReturnInst::Create (context));
	ctx2.drop ();
	ctx2.push (boost::make_shared <mu::llvm_::module::print> ());
	ctx2.push (mod);
	auto valid2 (ctx2 ());
	assert (valid2);
	ctx2.drop ();
	ctx2.push (boost::make_shared <mu::llvm_::module::verify> ());
	ctx2.push (mod);
	auto valid3 (ctx2 ());
	assert (valid3);
}

void mu::llvm_test::ccall::operation::run_2 ()
{
	mu::core::errors::errors errors (boost::make_shared <mu::core::errors::error_list> ());
	llvm::LLVMContext context;
	llvm::Module module (llvm::StringRef (), context);
	auto mod (boost::make_shared <mu::llvm_::module::node> (&module));
	auto ctx (boost::make_shared <mu::llvm_::context::node> (&context));
	auto function (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getInt1Ty (context), false), llvm::GlobalValue::ExternalLinkage, llvm::Twine (), &module));
	auto block (llvm::BasicBlock::Create (context, llvm::Twine (), function));
	auto bl (boost::make_shared <mu::llvm_::basic_block::node> (block));
	mu::script::context ctx2 (errors);
	ctx2.push (boost::make_shared <mu::llvm_::ccall::operation> (bl, boost::make_shared <mu::llvm_::basic_block::split_return> (bl, boost::make_shared <mu::llvm_::basic_block::instruction_insert> (bl, boost::make_shared <mu::llvm_::instructions::call> ()))));
	auto bool_l (boost::make_shared <mu::llvm_::value::node> (llvm::ConstantInt::get (context, llvm::APInt (1, 0)), boost::make_shared <mu::llvm_::integer_type::node> (llvm::Type::getInt1Ty (context))));
	ctx2.push (bool_l);
	auto true_function (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getInt1Ty (context), false), llvm::GlobalValue::ExternalLinkage, llvm::Twine (), &module));
	auto true_fn (boost::make_shared <mu::llvm_::function::node> (true_function, boost::make_shared <mu::llvm_::pointer_type::node> (boost::make_shared <mu::llvm_::function_type::node> (ctx, std::vector <boost::shared_ptr <mu::llvm_::type::node>> (), boost::make_shared <mu::llvm_::integer_type::node> (llvm::Type::getInt1Ty (context))))));
	ctx2.push (true_fn);
	auto false_function (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getInt1Ty (context), false), llvm::GlobalValue::ExternalLinkage, llvm::Twine (), &module));
	auto false_fn (boost::make_shared <mu::llvm_::function::node> (false_function, boost::make_shared <mu::llvm_::pointer_type::node> (boost::make_shared <mu::llvm_::function_type::node> (ctx, std::vector <boost::shared_ptr <mu::llvm_::type::node>> (), boost::make_shared <mu::llvm_::integer_type::node> (llvm::Type::getInt1Ty (context))))));
	ctx2.push (false_fn);
	auto valid (ctx2 ());
	assert (ctx2.working_size () == 1);
	auto value (boost::dynamic_pointer_cast <mu::llvm_::value::node> (ctx2.working (0)));
	assert (value.get () != nullptr);
	bl->block->getInstList ().push_back (llvm::ReturnInst::Create (context, value->value ()));
	ctx2.drop ();
	ctx2.push (boost::make_shared <mu::llvm_::module::print> ());
	ctx2.push (mod);
	auto valid2 (ctx2 ());
	assert (valid2);
	ctx2.drop ();
	ctx2.push (boost::make_shared <mu::llvm_::module::verify> ());
	ctx2.push (mod);
	auto valid3 (ctx2 ());
	assert (valid3);
}

void mu::llvm_test::ccall::operation::run_3 ()
{
	mu::core::errors::errors errors (boost::make_shared <mu::core::errors::error_list> ());
	llvm::LLVMContext context;
	llvm::Module module (llvm::StringRef (), context);
	auto mod (boost::make_shared <mu::llvm_::module::node> (&module));
	auto ctx (boost::make_shared <mu::llvm_::context::node> (&context));
	auto result_type (boost::make_shared <mu::llvm_::set_type::node> (ctx));
	result_type->elements.push_back (boost::make_shared <mu::llvm_::integer_type::node> (llvm::Type::getInt1Ty (context)));
	result_type->elements.push_back (boost::make_shared <mu::llvm_::integer_type::node> (llvm::Type::getInt1Ty (context)));
	auto function (llvm::Function::Create (llvm::FunctionType::get (result_type->type (), false), llvm::GlobalValue::ExternalLinkage, llvm::Twine (), &module));
	auto block (llvm::BasicBlock::Create (context, llvm::Twine (), function));
	auto bl (boost::make_shared <mu::llvm_::basic_block::node> (block));
	mu::script::context ctx2 (errors);
	ctx2.push (boost::make_shared <mu::llvm_::ccall::operation> (bl, boost::make_shared <mu::llvm_::basic_block::split_return> (bl, boost::make_shared <mu::llvm_::basic_block::instruction_insert> (bl, boost::make_shared <mu::llvm_::instructions::call> ()))));
	auto bool_l (boost::make_shared <mu::llvm_::value::node> (llvm::ConstantInt::get (context, llvm::APInt (1, 0)), boost::make_shared <mu::llvm_::integer_type::node> (llvm::Type::getInt1Ty (context))));
	ctx2.push (bool_l);
	auto true_function (llvm::Function::Create (llvm::FunctionType::get (result_type->type (), false), llvm::GlobalValue::ExternalLinkage, llvm::Twine (), &module));
	auto true_fn (boost::make_shared <mu::llvm_::function::node> (true_function, boost::make_shared <mu::llvm_::pointer_type::node> (boost::make_shared <mu::llvm_::function_type::node> (ctx, std::vector <boost::shared_ptr <mu::llvm_::type::node>> (), result_type))));
	ctx2.push (true_fn);
	auto false_function (llvm::Function::Create (llvm::FunctionType::get (result_type->type (), false), llvm::GlobalValue::ExternalLinkage, llvm::Twine (), &module));
	auto false_fn (boost::make_shared <mu::llvm_::function::node> (false_function, boost::make_shared <mu::llvm_::pointer_type::node> (boost::make_shared <mu::llvm_::function_type::node> (ctx, std::vector <boost::shared_ptr <mu::llvm_::type::node>> (), result_type))));
	ctx2.push (false_fn);
	auto valid (ctx2 ());
	assert (valid);
	assert (ctx2.working_size () == 2);
	auto value1 (boost::dynamic_pointer_cast <mu::llvm_::value::node> (ctx2.working (0)));
	assert (value1.get () != nullptr);
	auto value2 (boost::dynamic_pointer_cast <mu::llvm_::value::node> (ctx2.working (1)));
	assert (value2.get () != nullptr);
	llvm::Value * result (llvm::ConstantAggregateZero::get (result_type->type ()));
	result = llvm::InsertValueInst::Create (result, value1->value (), 0, llvm::Twine (), bl->block);
	result = llvm::InsertValueInst::Create (result, value2->value (), 1, llvm::Twine (), bl->block);
	bl->block->getInstList ().push_back (llvm::ReturnInst::Create (context, result));
	ctx2.drop ();
	ctx2.push (boost::make_shared <mu::llvm_::module::print> ());
	ctx2.push (mod);
	auto valid2 (ctx2 ());
	assert (valid2);
	ctx2.drop ();
	ctx2.push (boost::make_shared <mu::llvm_::module::verify> ());
	ctx2.push (mod);
	auto valid3 (ctx2 ());
	assert (valid3);
}