#include <mu/llvm_test/basic_block/split_return.h>

#include <mu/llvm_/basic_block/split_return.h>
#include <mu/core/cluster.h>
#include <mu/core/routine.h>
#include <mu/core/expression.h>
#include <mu/script/synthesizer/operation.h>
#include <mu/script/context.h>
#include <mu/core/errors/error_list.h>
#include <mu/script/identity/operation.h>
#include <mu/llvm_/void_type/node.h>
#include <mu/llvm_/integer_type/node.h>
#include <mu/llvm_/set_type/node.h>
#include <mu/llvm_/constant/node.h>
#include <mu/script/cluster/node.h>
#include <mu/llvm_/basic_block/node.h>
#include <mu/script/runtime/routine.h>
#include <mu/core/parameters.h>

#include <boost/make_shared.hpp>

#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Function.h>
#include <llvm/BasicBlock.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Constants.h>

void mu::llvm_test::basic_block::split_return::run ()
{
	run_1 ();
}

void mu::llvm_test::basic_block::split_return::run_1 ()
{
	mu::core::errors::errors errors (boost::make_shared <mu::core::errors::error_list> ());
	mu::script::context context (errors);
	context.push (boost::make_shared <mu::script::synthesizer::operation> ());
	auto cluster (boost::make_shared <mu::core::cluster> ());
	auto routine (boost::make_shared <mu::core::routine> ());
	cluster->routines.push_back (routine);
	auto body (boost::make_shared <mu::core::expression> ());
	routine->body = body;
	body->dependencies.push_back (boost::make_shared <mu::script::identity::operation> ());
	body->dependencies.push_back (boost::make_shared <mu::core::parameters> ());
	context.push (cluster);
	auto valid (context ());
	assert (valid);
	assert (context.working_size () == 1);
	auto cl (boost::dynamic_pointer_cast <mu::script::cluster::node> (context.working (0)));
	assert (cl->routines.size () == 1);
	auto r (cl->routines [0]);
	llvm::LLVMContext ctx;
	auto module (new llvm::Module (llvm::StringRef (), ctx));
	auto function (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (ctx), false), llvm::GlobalValue::LinkageTypes::PrivateLinkage));
	module->getFunctionList ().push_back (function);
	auto bl (llvm::BasicBlock::Create (ctx));
	function->getBasicBlockList ().push_back (bl);
	auto block (boost::make_shared <mu::llvm_::basic_block::node> (bl));
	context.drop ();
	context.push (boost::make_shared <mu::llvm_::basic_block::split_return> (block, r));
	context.push (boost::make_shared <mu::llvm_::constant::node> (llvm::ConstantInt::get (llvm::Type::getInt32Ty (ctx), 0, false), boost::make_shared <mu::llvm_::integer_type::node> (llvm::Type::getInt32Ty (ctx))));
	auto valid2 (context ());
	assert (valid2);
	assert (context.working_size () == 1);
}