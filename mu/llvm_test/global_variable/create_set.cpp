#include "create_set.h"

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
	auto errors (boost::make_shared <mu::core::errors::error_list> ());
	auto module (boost::make_shared <mu::llvm_::module::node> (new llvm::Module (llvm::StringRef (), context)));
	std::vector <boost::shared_ptr <mu::core::node>> a1;
	a1.push_back (module);
	a1.push_back (boost::make_shared <mu::llvm_::constant_int::node> (llvm::ConstantInt::get (llvm::Type::getInt1Ty (context), 0, false), boost::make_shared <mu::llvm_::integer_type::node> (llvm::Type::getInt1Ty (context))));
	std::vector <boost::shared_ptr <mu::core::node>> r1;
	mu::llvm_::global_variable::create_set create;
	std::vector <boost::shared_ptr <mu::script::operation>> stack;
    auto ctx (mu::script::context (errors, a1, r1, stack));
	create (ctx);
	assert (errors->errors.empty ());
	assert (r1.size () == 1);
	auto result (boost::dynamic_pointer_cast <mu::llvm_::global_variable::node> (r1 [0]));
	assert (result.get () != nullptr);
	auto type (boost::dynamic_pointer_cast <mu::llvm_::pointer_type::node> (result->type));
	assert (type.get () != nullptr);
	auto element_type (boost::dynamic_pointer_cast <mu::llvm_::integer_type::node> (type->element));
	assert (element_type.get () != nullptr);
}