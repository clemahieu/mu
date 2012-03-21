#include <mu/llvm_test/global_variable/create_set.h>

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

void mu::llvm_test::global_variable::create_set::run ()
{
	run_1 ();
}

void mu::llvm_test::global_variable::create_set::run_1 ()
{
	llvm::LLVMContext context;
	mu::core::errors::errors errors (boost::make_shared <mu::core::errors::error_list> ());
	auto module (boost::make_shared <mu::llvm_::module::node> (new llvm::Module (llvm::StringRef (), context)));
	mu::script::context ctx (errors);
	ctx.push (boost::make_shared <mu::llvm_::global_variable::create_set> ());
	ctx.push (module);
	ctx.push (boost::make_shared <mu::llvm_::constant_int::node> (llvm::ConstantInt::get (llvm::Type::getInt1Ty (context), 0, false), boost::make_shared <mu::llvm_::integer_type::node> (llvm::Type::getInt1Ty (context))));
	auto valid (ctx ());
	assert (valid);
	assert (ctx.working_size () == 1);
	auto result (boost::dynamic_pointer_cast <mu::llvm_::global_variable::node> (ctx.working (0)));
	assert (result.get () != nullptr);
	auto type (boost::dynamic_pointer_cast <mu::llvm_::pointer_type::node> (result->type));
	assert (type.get () != nullptr);
	auto element_type (boost::dynamic_pointer_cast <mu::llvm_::integer_type::node> (type->element));
	assert (element_type.get () != nullptr);
}