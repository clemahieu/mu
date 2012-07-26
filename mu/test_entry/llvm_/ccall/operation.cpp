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

#include <llvm/LLVMContext.h>
#include <llvm/BasicBlock.h>
#include <llvm/Module.h>
#include <llvm/Function.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Constants.h>
#include <llvm/Instructions.h>

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (llvm_test, ccall_operation1)
{
	mu::core::errors::errors errors (*new (GC) mu::core::errors::error_list);
	llvm::LLVMContext context;
	llvm::Module module (llvm::StringRef (), context);
	auto mod (new (GC) mu::llvm_::module::node (&module));
	auto ctx (new (GC) mu::llvm_::context::node (&context));
	auto function (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (context), false), llvm::GlobalValue::ExternalLinkage, llvm::Twine (), &module));
	auto block (llvm::BasicBlock::Create (context, llvm::Twine (), function));
	auto bl (new (GC) mu::llvm_::basic_block::node (block));
	mu::script::context ctx2 (errors);
	ctx2.push (new (GC) mu::llvm_::ccall::operation (bl, new (GC) mu::llvm_::basic_block::split_return (bl, new (GC) mu::llvm_::basic_block::instruction_insert (bl, new (GC) mu::llvm_::instructions::call))));
	auto bool_l (new (GC) mu::llvm_::value::node (llvm::ConstantInt::get (context, llvm::APInt (1, 0)), new (GC) mu::llvm_::integer_type::node (llvm::Type::getInt1Ty (context))));
	ctx2.push (bool_l);
	auto true_function (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (context), false), llvm::GlobalValue::ExternalLinkage, llvm::Twine (), &module));
	auto true_fn (new (GC) mu::llvm_::function::node (true_function, new (GC) mu::llvm_::pointer_type::node (new (GC) mu::llvm_::function_type::node (ctx, std::vector <mu::llvm_::type::node *, gc_allocator <mu::llvm_::type::node *>> (), new (GC) mu::llvm_::void_type::node (ctx)))));
	ctx2.push (true_fn);
	auto false_function (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (context), false), llvm::GlobalValue::ExternalLinkage, llvm::Twine (), &module));
	auto false_fn (new (GC) mu::llvm_::function::node (false_function, new (GC) mu::llvm_::pointer_type::node (new (GC) mu::llvm_::function_type::node (ctx, std::vector <mu::llvm_::type::node *, gc_allocator <mu::llvm_::type::node *>> (), new (GC) mu::llvm_::void_type::node (ctx)))));
	ctx2.push (false_fn);
	auto valid (ctx2 ());
    EXPECT_EQ (valid, true);
	EXPECT_EQ (ctx2.working_size (), 0);
	bl->block->getInstList ().push_back (llvm::ReturnInst::Create (context));
	ctx2.drop ();
	ctx2.push (new (GC) mu::llvm_::module::print);
	ctx2.push (mod);
	auto valid2 (ctx2 ());
	EXPECT_EQ (valid2, true);
	ctx2.drop ();
	ctx2.push (new (GC) mu::llvm_::module::verify);
	ctx2.push (mod);
	auto valid3 (ctx2 ());
	EXPECT_EQ (valid3, true);
}

TEST (llvm_test, ccall_operation2)
{
	mu::core::errors::errors errors (*new (GC) mu::core::errors::error_list);
	llvm::LLVMContext context;
	llvm::Module module (llvm::StringRef (), context);
	auto mod (new (GC) mu::llvm_::module::node (&module));
	auto ctx (new (GC) mu::llvm_::context::node (&context));
	auto function (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getInt1Ty (context), false), llvm::GlobalValue::ExternalLinkage, llvm::Twine (), &module));
	auto block (llvm::BasicBlock::Create (context, llvm::Twine (), function));
	auto bl (new (GC) mu::llvm_::basic_block::node (block));
	mu::script::context ctx2 (errors);
	ctx2.push (new (GC) mu::llvm_::ccall::operation (bl, new (GC) mu::llvm_::basic_block::split_return (bl, new (GC) mu::llvm_::basic_block::instruction_insert (bl, new (GC) mu::llvm_::instructions::call))));
	auto bool_l (new (GC) mu::llvm_::value::node (llvm::ConstantInt::get (context, llvm::APInt (1, 0)), new (GC) mu::llvm_::integer_type::node (llvm::Type::getInt1Ty (context))));
	ctx2.push (bool_l);
	auto true_function (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getInt1Ty (context), false), llvm::GlobalValue::ExternalLinkage, llvm::Twine (), &module));
	auto true_fn (new (GC) mu::llvm_::function::node (true_function, new (GC) mu::llvm_::pointer_type::node (new (GC) mu::llvm_::function_type::node (ctx, std::vector <mu::llvm_::type::node *, gc_allocator <mu::llvm_::type::node *>> (), new (GC) mu::llvm_::integer_type::node (llvm::Type::getInt1Ty (context))))));
	ctx2.push (true_fn);
	auto false_function (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getInt1Ty (context), false), llvm::GlobalValue::ExternalLinkage, llvm::Twine (), &module));
	auto false_fn (new (GC) mu::llvm_::function::node (false_function, new (GC) mu::llvm_::pointer_type::node (new (GC) mu::llvm_::function_type::node (ctx, std::vector <mu::llvm_::type::node *, gc_allocator <mu::llvm_::type::node *>> (), new (GC) mu::llvm_::integer_type::node (llvm::Type::getInt1Ty (context))))));
	ctx2.push (false_fn);
	auto valid (ctx2 ());
    EXPECT_EQ (valid, true);
	EXPECT_EQ (ctx2.working_size (), 1);
	auto value (dynamic_cast <mu::llvm_::value::node *> (ctx2.working (0)));
	EXPECT_NE (value, nullptr);
	bl->block->getInstList ().push_back (llvm::ReturnInst::Create (context, value->value ()));
	ctx2.drop ();
	ctx2.push (new (GC) mu::llvm_::module::print);
	ctx2.push (mod);
	auto valid2 (ctx2 ());
	EXPECT_EQ (valid2, true);
	ctx2.drop ();
	ctx2.push (new (GC) mu::llvm_::module::verify);
	ctx2.push (mod);
	auto valid3 (ctx2 ());
	EXPECT_EQ (valid3, true);
}

TEST (llvm_test, ccall_operation3)
{
	mu::core::errors::errors errors (*new (GC) mu::core::errors::error_list);
	llvm::LLVMContext context;
	llvm::Module module (llvm::StringRef (), context);
	auto mod (new (GC) mu::llvm_::module::node (&module));
	auto ctx (new (GC) mu::llvm_::context::node (&context));
	auto result_type (new (GC) mu::llvm_::set_type::node (ctx));
	result_type->elements.push_back (new (GC) mu::llvm_::integer_type::node (llvm::Type::getInt1Ty (context)));
	result_type->elements.push_back (new (GC) mu::llvm_::integer_type::node (llvm::Type::getInt1Ty (context)));
	auto function (llvm::Function::Create (llvm::FunctionType::get (result_type->type (), false), llvm::GlobalValue::ExternalLinkage, llvm::Twine (), &module));
	auto block (llvm::BasicBlock::Create (context, llvm::Twine (), function));
	auto bl (new (GC) mu::llvm_::basic_block::node (block));
	mu::script::context ctx2 (errors);
	ctx2.push (new (GC) mu::llvm_::ccall::operation (bl, new (GC) mu::llvm_::basic_block::split_return (bl, new (GC) mu::llvm_::basic_block::instruction_insert (bl, new (GC) mu::llvm_::instructions::call))));
	auto bool_l (new (GC) mu::llvm_::value::node (llvm::ConstantInt::get (context, llvm::APInt (1, 0)), new (GC) mu::llvm_::integer_type::node (llvm::Type::getInt1Ty (context))));
	ctx2.push (bool_l);
	auto true_function (llvm::Function::Create (llvm::FunctionType::get (result_type->type (), false), llvm::GlobalValue::ExternalLinkage, llvm::Twine (), &module));
	auto true_fn (new (GC) mu::llvm_::function::node (true_function, new (GC) mu::llvm_::pointer_type::node (new (GC) mu::llvm_::function_type::node (ctx, std::vector <mu::llvm_::type::node *, gc_allocator <mu::llvm_::type::node *>> (), result_type))));
	ctx2.push (true_fn);
	auto false_function (llvm::Function::Create (llvm::FunctionType::get (result_type->type (), false), llvm::GlobalValue::ExternalLinkage, llvm::Twine (), &module));
	auto false_fn (new (GC) mu::llvm_::function::node (false_function, new (GC) mu::llvm_::pointer_type::node (new (GC) mu::llvm_::function_type::node (ctx, std::vector <mu::llvm_::type::node *, gc_allocator <mu::llvm_::type::node *>> (), result_type))));
	ctx2.push (false_fn);
	auto valid (ctx2 ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (ctx2.working_size (), 2);
	auto value1 (dynamic_cast <mu::llvm_::value::node *> (ctx2.working (0)));
	EXPECT_NE (value1, nullptr);
	auto value2 (dynamic_cast <mu::llvm_::value::node *> (ctx2.working (1)));
	EXPECT_NE (value2, nullptr);
	llvm::Value * result (llvm::ConstantAggregateZero::get (result_type->type ()));
	result = llvm::InsertValueInst::Create (result, value1->value (), 0, llvm::Twine (), bl->block);
	result = llvm::InsertValueInst::Create (result, value2->value (), 1, llvm::Twine (), bl->block);
	bl->block->getInstList ().push_back (llvm::ReturnInst::Create (context, result));
	ctx2.drop ();
	ctx2.push (new (GC) mu::llvm_::module::print);
	ctx2.push (mod);
	auto valid2 (ctx2 ());
	EXPECT_EQ (valid2, true);
	ctx2.drop ();
	ctx2.push (new (GC) mu::llvm_::module::verify);
	ctx2.push (mod);
	auto valid3 (ctx2 ());
	EXPECT_EQ (valid3, true);
}