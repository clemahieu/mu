#include <mu/core/errors/error_list.h>
#include <mu/llvm_/global_variable/create_set.h>
#include <mu/llvm_/constant_int/node.h>
#include <mu/llvm_/integer_type/node.h>
#include <mu/llvm_/global_variable/node.h>
#include <mu/llvm_/pointer_type/node.h>
#include <mu/llvm_/module/node.h>
#include <mu/script/context.h>

#include <boost/make_shared.hpp>

#include <llvm/Constants.h>
#include <llvm/DerivedTypes.h>
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (llvm_test, global_variable_create_set1)
{
	llvm::LLVMContext context;
	mu::core::errors::errors errors (new (GC) mu::core::errors::error_list);
	auto module (boost::make_shared <mu::llvm_::module::node> (new llvm::Module (llvm::StringRef (), context)));
	mu::script::context ctx (errors);
	ctx.push (boost::make_shared <mu::llvm_::global_variable::create_set> ());
	ctx.push (module);
	ctx.push (boost::make_shared <mu::llvm_::constant_int::node> (llvm::ConstantInt::get (llvm::Type::getInt1Ty (context), 0, false), boost::make_shared <mu::llvm_::integer_type::node> (llvm::Type::getInt1Ty (context))));
	auto valid (ctx ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (ctx.working_size (), 1);
	auto result (boost::dynamic_pointer_cast <mu::llvm_::global_variable::node> (ctx.working (0)));
	EXPECT_NE (result.get (), nullptr);
	auto type (boost::dynamic_pointer_cast <mu::llvm_::pointer_type::node> (result->type));
	EXPECT_NE (type.get (), nullptr);
	auto element_type (boost::dynamic_pointer_cast <mu::llvm_::integer_type::node> (type->element));
	EXPECT_NE (element_type.get (), nullptr);
}