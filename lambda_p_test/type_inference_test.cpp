#include "type_inference_test.h"

#include <lambda_p/builder.h>
#include <lambda_p/binder/list.h>
#include <lambda_p_kernel/apply.h>
#include <lambda_p_llvm/type_inference.h>
#include <lambda_p/errors/error_list.h>

#include <llvm/LLVMContext.h>
#include <llvm/DerivedTypes.h>

void lambda_p_test::type_inference_test::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
	run_5 ();
}

void lambda_p_test::type_inference_test::run_1 ()
{
	lambda_p::builder builder;
	builder (L"result; function; function; result; :;");
	boost::shared_ptr <lambda_p::binder::list> arguments (new lambda_p::binder::list);
	llvm::LLVMContext context;
	arguments->operator[] (0) = boost::shared_ptr <lambda_p_llvm::type_inference> (new lambda_p_llvm::type_inference (llvm::FunctionType::get (llvm::Type::getVoidTy (context), false)));
	lambda_p_kernel::apply apply;
	lambda_p::errors::error_list problems;
	boost::shared_ptr <lambda_p::binder::list> declarations (new lambda_p::binder::list);
	apply.core (builder.routines.routines->operator[] (0), *arguments, problems, *declarations);
	assert (problems.errors.empty ());
	assert (declarations->nodes.size () == 1);
	auto type (boost::dynamic_pointer_cast <lambda_p_llvm::type_inference> (declarations->operator[] (0)));
	assert (type.get () != nullptr);
	assert (type->type->isVoidTy ());
}

void lambda_p_test::type_inference_test::run_2 ()
{
	lambda_p::builder builder;
	builder (L"result; function; function; result; :;");
	boost::shared_ptr <lambda_p::binder::list> arguments (new lambda_p::binder::list);
	llvm::LLVMContext context;
	arguments->operator[] (0) = boost::shared_ptr <lambda_p_llvm::type_inference> (new lambda_p_llvm::type_inference (llvm::FunctionType::get (llvm::Type::getInt1Ty (context), false)));
	lambda_p_kernel::apply apply;
	lambda_p::errors::error_list problems;
	boost::shared_ptr <lambda_p::binder::list> declarations (new lambda_p::binder::list);
	apply.core (builder.routines.routines->operator[] (0), *arguments, problems, *declarations);
	assert (problems.errors.empty ());
	assert (declarations->nodes.size () == 1);
	auto type (boost::dynamic_pointer_cast <lambda_p_llvm::type_inference> (declarations->operator[] (0)));
	assert (type.get () != nullptr);
	auto int_type (llvm::dyn_cast <llvm::IntegerType> (type->type));
	assert (int_type != nullptr);
	assert (int_type->getBitWidth () == 1);
}

void lambda_p_test::type_inference_test::run_3 ()
{
	lambda_p::builder builder;
	builder (L"result; function input; function input; result; :;");
	boost::shared_ptr <lambda_p::binder::list> arguments (new lambda_p::binder::list);
	llvm::LLVMContext context;
	std::vector <llvm::Type const *> args;
	args.push_back (llvm::Type::getDoubleTy (context));
	arguments->operator[] (0) = boost::shared_ptr <lambda_p_llvm::type_inference> (new lambda_p_llvm::type_inference (llvm::FunctionType::get (llvm::Type::getInt1Ty (context), args, false)));
	arguments->operator[] (1) = boost::shared_ptr <lambda_p_llvm::type_inference> (new lambda_p_llvm::type_inference (llvm::Type::getDoubleTy (context)));
	lambda_p_kernel::apply apply;
	lambda_p::errors::error_list problems;
	boost::shared_ptr <lambda_p::binder::list> declarations (new lambda_p::binder::list);
	apply.core (builder.routines.routines->operator[] (0), *arguments, problems, *declarations);
	assert (problems.errors.empty ());
	assert (declarations->nodes.size () == 1);
	auto type (boost::dynamic_pointer_cast <lambda_p_llvm::type_inference> (declarations->operator[] (0)));
	assert (type.get () != nullptr);
	auto int_type (llvm::dyn_cast <llvm::IntegerType> (type->type));
	assert (int_type != nullptr);
	assert (int_type->getBitWidth () == 1);
}

void lambda_p_test::type_inference_test::run_4 ()
{
	lambda_p::builder builder;
	builder (L"result; input; input; result; :;");
	boost::shared_ptr <lambda_p::binder::list> arguments (new lambda_p::binder::list);
	llvm::LLVMContext context;
	std::vector <llvm::Type const *> args;
	args.push_back (llvm::Type::getDoubleTy (context));
	arguments->operator[] (0) = boost::shared_ptr <lambda_p_llvm::type_inference> (new lambda_p_llvm::type_inference (llvm::Type::getDoubleTy (context)));
	lambda_p_kernel::apply apply;
	lambda_p::errors::error_list problems;
	boost::shared_ptr <lambda_p::binder::list> declarations (new lambda_p::binder::list);
	apply.core (builder.routines.routines->operator[] (0), *arguments, problems, *declarations);
	assert (!problems.errors.empty ());
}

void lambda_p_test::type_inference_test::run_5 ()
{
	llvm::LLVMContext context;
	auto type (llvm::Type::getDoublePtrTy (context));
	auto inner (type->getTypeAtIndex ((unsigned int)0));
	assert (inner->isDoubleTy ());
}