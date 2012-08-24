#include <mu/core/errors/error_list.h>
#include <mu/io/source.h>
#include <mu/llvm_/constant_string/extension.h>
#include <mu/core/expression.h>
#include <mu/llvm_/context/node.h>
#include <mu/llvm_/module/node.h>
#include <mu/io/ast/cluster.h>
#include <mu/io/ast/expression.h>
#include <mu/io/keywording/extensions.h>

#include <boost/bind.hpp>

#include <llvm/LLVMContext.h>
#include <llvm/Module.h>

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (llvm_test, DISABLED_constant_string_extension1)
{
    assert (false);/*
	llvm::LLVMContext context;
	auto ctx (new (GC) mu::llvm_::context::node (&context));
	auto module (new (GC) mu::llvm_::module::node (new llvm::Module (llvm::StringRef (""), context)));
	mu::io::ast::builder builder;
    (*builder.keywording.extensions) (mu::string (U"`"), [module] (mu::io::keywording::keywording & keywording_a) {return new (GC) mu::llvm_::constant_string::extension (keywording_a, module);}, false);
	mu::io::process (builder, U"[` test_string]");
	EXPECT_TRUE (builder.errors.errors.empty ());
	auto cluster (builder.cluster);
	EXPECT_TRUE (cluster->expressions.size () == 1);
	auto expression (cluster->expressions [0]);
	EXPECT_TRUE (expression->values.size () == 1);*/
}