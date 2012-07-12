#include <mu/core/errors/error_list.h>
#include <mu/llvm_/constant_string/create.h>
#include <mu/script/string/node.h>
#include <mu/llvm_/context/node.h>
#include <mu/llvm_/module/node.h>
#include <mu/llvm_/global_variable/node.h>
#include <mu/llvm_/pointer_type/node.h>
#include <mu/llvm_/integer_type/node.h>
#include <mu/script/context.h>

#include <boost/make_shared.hpp>

#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/GlobalVariable.h>
#include <llvm/Constants.h>
#include <llvm/DerivedTypes.h>

#include <gtest/gtest.h>

TEST (llvm_test, constant_string_create1)
{
	mu::core::errors::errors errors (boost::make_shared <mu::core::errors::error_list> ());
	llvm::LLVMContext context;
	auto module (new llvm::Module (llvm::StringRef (), context));
	mu::script::context ctx;
	ctx.push (boost::make_shared <mu::llvm_::constant_string::create> ());
	ctx.push (boost::make_shared <mu::llvm_::context::node> (&context));
	ctx.push (boost::make_shared <mu::llvm_::module::node> (module));
	ctx.push (boost::make_shared <mu::script::string::node> (std::wstring (L"test string")));
	auto valid (ctx ());
	assert (valid);
	assert (ctx.working_size () == 1);
	auto result (boost::dynamic_pointer_cast <mu::llvm_::value::node> (ctx.working (0)));
	assert (result.get () != nullptr);
	//assert (result->global_variable ()->isConstant ());
	//assert (result->global_variable ()->hasInitializer ());
	//auto initializer (result->global_variable ()->getInitializer ());
	//assert (initializer != nullptr);
	//auto array (llvm::cast <llvm::ConstantArray> (initializer));
	//assert (array != nullptr);
	//auto elements (array->getType ()->getNumElements ());
	//assert (elements == 11);
	auto type (boost::dynamic_pointer_cast <mu::llvm_::pointer_type::node> (result->type));
	assert (type.get () != nullptr);
	auto element_type (boost::dynamic_pointer_cast <mu::llvm_::integer_type::node> (type->element));
	assert (element_type.get () != nullptr);
}