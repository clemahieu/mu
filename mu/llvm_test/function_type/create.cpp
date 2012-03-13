#include "create.h"

#include <mu/core/errors/error_list.h>
#include <mu/llvm_/function_type/create.h>
#include <mu/llvm_/function_type/node.h>
#include <mu/llvm_/context/node.h>
#include <mu/script/values/operation.h>
#include <mu/llvm_/integer_type/node.h>
#include <mu/llvm_/set_type/node.h>
#include <mu/script/context.h>

#include <boost/make_shared.hpp>

#include <llvm/DerivedTypes.h>
#include <llvm/LLVMContext.h>

void mu::llvm_test::function_type::create::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
	run_5 ();
}

void mu::llvm_test::function_type::create::run_1 ()
{
	llvm::LLVMContext context_l;
	auto context (boost::make_shared <mu::llvm_::context::node> (&context_l));
	mu::llvm_::function_type::create create;
	auto errors (boost::make_shared <mu::core::errors::error_list> ());
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	std::vector <boost::shared_ptr <mu::core::node>> results;
	arguments.push_back (context);
	arguments.push_back (boost::make_shared <mu::script::values::operation> ());
	arguments.push_back (boost::make_shared <mu::script::values::operation> ());
	std::vector <boost::shared_ptr <mu::script::debugging::call_info>> stack;
    auto ctx (mu::script::context (errors, arguments, results, stack));
	create (ctx);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	auto type (boost::dynamic_pointer_cast <mu::llvm_::function_type::node> (results [0]));
	assert (type.get () != nullptr);
	assert (type->parameters.size () == 0);
	auto return_type (type->function_type ()->getReturnType ());
	assert (return_type == llvm::Type::getVoidTy (context_l));
	assert (type->function_type ()->getNumParams () == 0);
}

void mu::llvm_test::function_type::create::run_2 ()
{
	llvm::LLVMContext context_l;
	auto context (boost::make_shared <mu::llvm_::context::node> (&context_l));
	mu::llvm_::function_type::create create;
	auto errors (boost::make_shared <mu::core::errors::error_list> ());
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	std::vector <boost::shared_ptr <mu::core::node>> results;
	arguments.push_back (context);
	auto args (boost::make_shared <mu::script::values::operation> ());
	args->values.push_back (boost::make_shared <mu::llvm_::integer_type::node> (llvm::IntegerType::get (context_l, 1)));
	arguments.push_back (args);
	arguments.push_back (boost::make_shared <mu::script::values::operation> ());
	std::vector <boost::shared_ptr <mu::script::debugging::call_info>> stack;
    auto ctx (mu::script::context (errors, arguments, results, stack));
	create (ctx);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	auto type (boost::dynamic_pointer_cast <mu::llvm_::function_type::node> (results [0]));
	assert (type.get () != nullptr);
	assert (type->parameters.size () == 1);
	auto return_type (type->function_type ()->getReturnType ());
	assert (return_type == llvm::Type::getVoidTy (context_l));
	assert (type->function_type ()->getNumParams () == 1);
	auto arg1 (type->function_type ()->getParamType (0));
	assert (arg1 == llvm::Type::getInt1Ty (context_l));
}

void mu::llvm_test::function_type::create::run_3 ()
{
	llvm::LLVMContext context_l;
	auto context (boost::make_shared <mu::llvm_::context::node> (&context_l));
	mu::llvm_::function_type::create create;
	auto errors (boost::make_shared <mu::core::errors::error_list> ());
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	std::vector <boost::shared_ptr <mu::core::node>> results;
	arguments.push_back (context);
	auto args (boost::make_shared <mu::script::values::operation> ());
	args->values.push_back (boost::make_shared <mu::llvm_::integer_type::node> (llvm::IntegerType::get (context_l, 1)));
	args->values.push_back (boost::make_shared <mu::llvm_::integer_type::node> (llvm::IntegerType::get (context_l, 8)));
	arguments.push_back (args);
	arguments.push_back (boost::make_shared <mu::script::values::operation> ());
	std::vector <boost::shared_ptr <mu::script::debugging::call_info>> stack;
    auto ctx (mu::script::context (errors, arguments, results, stack));
	create (ctx);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	auto type (boost::dynamic_pointer_cast <mu::llvm_::function_type::node> (results [0]));
	assert (type.get () != nullptr);
	assert (type->parameters.size () == 2);
	auto return_type (type->function_type ()->getReturnType ());
	assert (return_type == llvm::Type::getVoidTy (context_l));
	assert (type->function_type ()->getNumParams () == 2);
	auto arg1 (type->function_type ()->getParamType (0));
	assert (arg1 == llvm::Type::getInt1Ty (context_l));
	auto arg2 (type->function_type ()->getParamType (1));
	assert (arg2 == llvm::Type::getInt8Ty (context_l));
}

void mu::llvm_test::function_type::create::run_4 ()
{
	llvm::LLVMContext context_l;
	auto context (boost::make_shared <mu::llvm_::context::node> (&context_l));
	mu::llvm_::function_type::create create;
	auto errors (boost::make_shared <mu::core::errors::error_list> ());
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	std::vector <boost::shared_ptr <mu::core::node>> results;
	arguments.push_back (context);
	arguments.push_back (boost::make_shared <mu::script::values::operation> ());
	auto res (boost::make_shared <mu::script::values::operation> ());
	res->values.push_back (boost::make_shared <mu::llvm_::integer_type::node> (llvm::IntegerType::get (context_l, 1)));
	arguments.push_back (res);
	std::vector <boost::shared_ptr <mu::script::debugging::call_info>> stack;
    auto ctx (mu::script::context (errors, arguments, results, stack));
	create (ctx);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	auto type (boost::dynamic_pointer_cast <mu::llvm_::function_type::node> (results [0]));
	assert (type.get () != nullptr);
	assert (type->function_type ()->getNumParams () == 0);
	auto return_type (type->function_type ()->getReturnType ());
	assert (return_type == llvm::Type::getInt1Ty (context_l));
}

void mu::llvm_test::function_type::create::run_5 ()
{
	llvm::LLVMContext context_l;
	auto context (boost::make_shared <mu::llvm_::context::node> (&context_l));
	mu::llvm_::function_type::create create;
	auto errors (boost::make_shared <mu::core::errors::error_list> ());
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	std::vector <boost::shared_ptr <mu::core::node>> results;
	arguments.push_back (context);
	arguments.push_back (boost::make_shared <mu::script::values::operation> ());
	auto res (boost::make_shared <mu::script::values::operation> ());
	res->values.push_back (boost::make_shared <mu::llvm_::integer_type::node> (llvm::IntegerType::get (context_l, 1)));
	res->values.push_back (boost::make_shared <mu::llvm_::integer_type::node> (llvm::IntegerType::get (context_l, 8)));
	arguments.push_back (res);
	std::vector <boost::shared_ptr <mu::script::debugging::call_info>> stack;
    auto ctx (mu::script::context (errors, arguments, results, stack));
	create (ctx);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	auto type (boost::dynamic_pointer_cast <mu::llvm_::function_type::node> (results [0]));
	assert (type.get () != nullptr);
	assert (type->function_type ()->getNumParams () == 0);
	auto return_type (boost::dynamic_pointer_cast <mu::llvm_::set_type::node> (type->output));
	assert (return_type->elements.size () == 2);
	assert (return_type->elements [0]->type () == llvm::Type::getInt1Ty (context_l));
	assert (return_type->elements [1]->type () == llvm::Type::getInt8Ty (context_l));
	auto struct_type (llvm::dyn_cast <llvm::StructType> (return_type->type ()));
	assert (struct_type != nullptr);
	assert (struct_type->getNumElements () == 2);
	assert (struct_type->getElementType (0) == llvm::Type::getInt1Ty (context_l));
	assert (struct_type->getElementType (1) == llvm::Type::getInt8Ty (context_l));
}