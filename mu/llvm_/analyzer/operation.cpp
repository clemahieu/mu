#include "operation.h"

#include <mu/io/ast/expression.h>
#include <mu/io/analyzer/analyzer.h>
#include <mu/core/routine.h>
#include <mu/io/analyzer/extensions/extensions.h>
#include <mu/io/analyzer/extensions/global.h>
#include <mu/llvm_/instructions/add.h>
#include <mu/llvm_/instructions/and.h>
#include <mu/llvm_/instructions/ashr.h>
#include <mu/llvm_/instructions/bitcast.h>
#include <mu/llvm_/instructions/call.h>
#include <mu/llvm_/instructions/cmpxchg.h>
#include <mu/llvm_/instructions/icmp.h>
#include <mu/llvm_/instructions/inttoptr.h>
#include <mu/llvm_/instructions/load.h>
#include <mu/llvm_/instructions/lshr.h>
#include <mu/llvm_/instructions/mul.h>
#include <mu/llvm_/instructions/or.h>
#include <mu/llvm_/instructions/ptrtoint.h>
#include <mu/llvm_/instructions/sdiv.h>
#include <mu/llvm_/instructions/sext.h>
#include <mu/llvm_/instructions/shl.h>
#include <mu/llvm_/instructions/srem.h>
#include <mu/llvm_/instructions/store.h>
#include <mu/llvm_/instructions/sub.h>
#include <mu/llvm_/instructions/trunc.h>
#include <mu/llvm_/instructions/udiv.h>
#include <mu/llvm_/instructions/urem.h>
#include <mu/llvm_/instructions/xor.h>
#include <mu/llvm_/instructions/zext.h>
#include <mu/llvm_/apint/extension.h>
#include <mu/script/string/extension.h>
#include <mu/io/ast/end.h>
#include <mu/io/ast/cluster.h>
#include <mu/llvm_/value/get_type.h>
#include <mu/script_io/builder.h>
#include <mu/llvm_/basic_block/insert.h>
#include <mu/llvm_/basic_block/node.h>
#include <mu/script/cluster/node.h>
#include <mu/script/runtime/routine.h>
#include <mu/llvm_/basic_block/instruction_insert.h>
#include <mu/script/values/create.h>
#include <mu/llvm_/function_type/create.h>
#include <mu/llvm_/integer_type/create.h>
#include <mu/script/closure/single.h>
#include <mu/llvm_/context/node.h>
#include <mu/llvm_/constant_int/create.h>
#include <mu/script/identity/operation.h>
#include <mu/llvm_/predicate/node.h>
#include <mu/llvm_/pointer_type/create.h>
#include <mu/llvm_/struct_type/create.h>
#include <mu/llvm_/apint/node.h>
#include <mu/llvm_/constant_int/extension.h>
#include <mu/llvm_/linkage_types/node.h>
#include <mu/llvm_/constant_string/extension.h>
#include <mu/llvm_/module/node.h>
#include <mu/llvm_/basic_block/split_return.h>
#include <mu/llvm_/null/create.h>
#include <mu/llvm_/ccall/operation.h>

#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

#include <llvm/ADT/APInt.h>

mu::llvm_::analyzer::operation::operation ()
	: extensions (new mu::io::analyzer::extensions::extensions)
{
	context.context_m = boost::make_shared <mu::llvm_::context::node> (nullptr);
	context.module = boost::make_shared <mu::llvm_::module::node> (nullptr);
	context.block = boost::make_shared <mu::llvm_::basic_block::node> (nullptr);
	extensions->extensions_m [std::wstring (L"#")] = boost::make_shared <mu::llvm_::apint::extension> ();
	extensions->extensions_m [std::wstring (L"#i")] = boost::make_shared <mu::llvm_::constant_int::extension> (context.context_m);
	extensions->extensions_m [std::wstring (L"`")] = boost::make_shared <mu::llvm_::constant_string::extension> (context.context_m, context.module);
	extensions->extensions_m [std::wstring (L"{")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::values::create> ());
	extensions->extensions_m [std::wstring (L"~")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::identity::operation> ());
	auto function_type (boost::make_shared <mu::script::closure::single> (boost::make_shared <mu::llvm_::function_type::create> ()));
	function_type->closed.push_back (context.context_m);
	extensions->extensions_m [std::wstring (L"fun-t")] = boost::make_shared <mu::io::analyzer::extensions::global> (function_type);
	auto integer_type (boost::make_shared <mu::script::closure::single> (boost::make_shared <mu::llvm_::integer_type::create> ()));
	integer_type->closed.push_back (context.context_m);
	extensions->extensions_m [std::wstring (L"int-t")] = boost::make_shared <mu::io::analyzer::extensions::global> (integer_type);
	auto i1_type (boost::make_shared <mu::script::closure::single> (boost::make_shared <mu::llvm_::integer_type::create> ()));
	i1_type->closed.push_back (context.context_m);
	i1_type->closed.push_back (boost::make_shared <mu::llvm_::apint::node> (new llvm::APInt (64, 1)));
	extensions->extensions_m [std::wstring (L"i1")] = boost::make_shared <mu::io::analyzer::extensions::global> (i1_type);
	auto i8_type (boost::make_shared <mu::script::closure::single> (boost::make_shared <mu::llvm_::integer_type::create> ()));
	i8_type->closed.push_back (context.context_m);
	i8_type->closed.push_back (boost::make_shared <mu::llvm_::apint::node> (new llvm::APInt (64, 8)));
	extensions->extensions_m [std::wstring (L"i8")] = boost::make_shared <mu::io::analyzer::extensions::global> (i8_type);
	auto i16_type (boost::make_shared <mu::script::closure::single> (boost::make_shared <mu::llvm_::integer_type::create> ()));
	i16_type->closed.push_back (context.context_m);
	i16_type->closed.push_back (boost::make_shared <mu::llvm_::apint::node> (new llvm::APInt (64, 16)));
	extensions->extensions_m [std::wstring (L"i16")] = boost::make_shared <mu::io::analyzer::extensions::global> (i16_type);
	auto i32_type (boost::make_shared <mu::script::closure::single> (boost::make_shared <mu::llvm_::integer_type::create> ()));
	i32_type->closed.push_back (context.context_m);
	i32_type->closed.push_back (boost::make_shared <mu::llvm_::apint::node> (new llvm::APInt (64, 32)));
	extensions->extensions_m [std::wstring (L"i32")] = boost::make_shared <mu::io::analyzer::extensions::global> (i32_type);
	auto i64_type (boost::make_shared <mu::script::closure::single> (boost::make_shared <mu::llvm_::integer_type::create> ()));
	i64_type->closed.push_back (context.context_m);
	i64_type->closed.push_back (boost::make_shared <mu::llvm_::apint::node> (new llvm::APInt (64, 64)));
	extensions->extensions_m [std::wstring (L"i64")] = boost::make_shared <mu::io::analyzer::extensions::global> (i64_type);
	auto struct_type (boost::make_shared <mu::script::closure::single> (boost::make_shared <mu::llvm_::struct_type::create> ()));
	struct_type->closed.push_back (context.context_m);
	extensions->extensions_m [std::wstring (L"struct-t")] = boost::make_shared <mu::io::analyzer::extensions::global> (struct_type);
	auto constant_int (boost::make_shared <mu::script::closure::single> (boost::make_shared <mu::llvm_::constant_int::create> ()));
	constant_int->closed.push_back (context.context_m);
	extensions->extensions_m [std::wstring (L"int-c")] = boost::make_shared <mu::io::analyzer::extensions::global> (constant_int);	
	extensions->extensions_m [std::wstring (L"add")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (context.block, boost::make_shared <mu::llvm_::instructions::add> ()));
	extensions->extensions_m [std::wstring (L"and")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (context.block, boost::make_shared <mu::llvm_::instructions::and> ()));
	extensions->extensions_m [std::wstring (L"ashr")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (context.block, boost::make_shared <mu::llvm_::instructions::ashr> ()));
	extensions->extensions_m [std::wstring (L"bitcast")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (context.block, boost::make_shared <mu::llvm_::instructions::bitcast> ()));
	auto call (boost::make_shared <mu::llvm_::basic_block::split_return> (context.block, boost::make_shared <mu::llvm_::basic_block::instruction_insert> (context.block, boost::make_shared <mu::llvm_::instructions::call> ())));
	extensions->extensions_m [std::wstring (L"call")] = boost::make_shared <mu::io::analyzer::extensions::global> (call);
	extensions->extensions_m [std::wstring (L"ccall")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::ccall::operation> (context.block, call));
	extensions->extensions_m [std::wstring (L"cmpxchg")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (context.block, boost::make_shared <mu::llvm_::instructions::cmpxchg> ()));
	extensions->extensions_m [std::wstring (L"eq")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::predicate::node> (llvm::CmpInst::Predicate::ICMP_EQ));
	extensions->extensions_m [std::wstring (L"icmp")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (context.block, boost::make_shared <mu::llvm_::instructions::icmp> ()));
	extensions->extensions_m [std::wstring (L"inttoptr")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (context.block, boost::make_shared <mu::llvm_::instructions::inttoptr> ()));
	extensions->extensions_m [std::wstring (L"load")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (context.block, boost::make_shared <mu::llvm_::instructions::load> ()));
	extensions->extensions_m [std::wstring (L"lshr")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (context.block, boost::make_shared <mu::llvm_::instructions::lshr> ()));
	extensions->extensions_m [std::wstring (L"mul")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (context.block, boost::make_shared <mu::llvm_::instructions::mul> ()));
	extensions->extensions_m [std::wstring (L"ne")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::predicate::node> (llvm::CmpInst::Predicate::ICMP_NE));
	extensions->extensions_m [std::wstring (L"null")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::null::create> ());
	extensions->extensions_m [std::wstring (L"or")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (context.block, boost::make_shared <mu::llvm_::instructions::or> ()));
	extensions->extensions_m [std::wstring (L"ptr")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::pointer_type::create> ());
	extensions->extensions_m [std::wstring (L"ptrtoint")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (context.block, boost::make_shared <mu::llvm_::instructions::ptrtoint> ()));
	extensions->extensions_m [std::wstring (L"sdiv")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (context.block, boost::make_shared <mu::llvm_::instructions::sdiv> ()));
	extensions->extensions_m [std::wstring (L"sext")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (context.block, boost::make_shared <mu::llvm_::instructions::sext> ()));
	extensions->extensions_m [std::wstring (L"sge")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::predicate::node> (llvm::CmpInst::Predicate::ICMP_SGE));
	extensions->extensions_m [std::wstring (L"sgt")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::predicate::node> (llvm::CmpInst::Predicate::ICMP_SGT));
	extensions->extensions_m [std::wstring (L"shl")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (context.block, boost::make_shared <mu::llvm_::instructions::shl> ()));
	extensions->extensions_m [std::wstring (L"sle")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::predicate::node> (llvm::CmpInst::Predicate::ICMP_SLE));
	extensions->extensions_m [std::wstring (L"slt")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::predicate::node> (llvm::CmpInst::Predicate::ICMP_SLT));
	extensions->extensions_m [std::wstring (L"srem")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (context.block, boost::make_shared <mu::llvm_::instructions::srem> ()));
	extensions->extensions_m [std::wstring (L"store")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (context.block, boost::make_shared <mu::llvm_::instructions::store> ()));
	extensions->extensions_m [std::wstring (L"sub")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (context.block, boost::make_shared <mu::llvm_::instructions::sub> ()));
	extensions->extensions_m [std::wstring (L"trunc")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (context.block, boost::make_shared <mu::llvm_::instructions::trunc> ()));
	extensions->extensions_m [std::wstring (L"udiv")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (context.block, boost::make_shared <mu::llvm_::instructions::udiv> ()));
	extensions->extensions_m [std::wstring (L"uge")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::predicate::node> (llvm::CmpInst::Predicate::ICMP_UGE));
	extensions->extensions_m [std::wstring (L"ugt")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::predicate::node> (llvm::CmpInst::Predicate::ICMP_UGT));
	extensions->extensions_m [std::wstring (L"ule")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::predicate::node> (llvm::CmpInst::Predicate::ICMP_ULE));
	extensions->extensions_m [std::wstring (L"ult")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::predicate::node> (llvm::CmpInst::Predicate::ICMP_ULT));
	extensions->extensions_m [std::wstring (L"urem")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (context.block, boost::make_shared <mu::llvm_::instructions::urem> ()));
	extensions->extensions_m [std::wstring (L"xor")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (context.block, boost::make_shared <mu::llvm_::instructions::xor> ()));
	extensions->extensions_m [std::wstring (L"zext")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (context.block, boost::make_shared <mu::llvm_::instructions::zext> ()));
}

void mu::llvm_::analyzer::operation::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <mu::io::ast::cluster> (parameters [0]));
	if (one.get () != nullptr)
	{
		auto function (boost::bind (&mu::llvm_::analyzer::operation::add, this, &results, _1));
		mu::io::analyzer::analyzer analyzer (function, errors_a, extensions);
		for (auto i (one->expressions.begin ()), j (one->expressions.end ()); i != j; ++i)
		{
			analyzer.input (*i);
		}
		mu::core::context context;
		if (one->expressions.size () > 0)
		{
			context = mu::core::context (one->expressions [one->expressions.size () - 1]->context.last, one->expressions [one->expressions.size () - 1]->context.last);
		}
		analyzer.input (boost::make_shared <mu::io::ast::end> (context));
	}
	else
	{
		invalid_type (errors_a, parameters [0], 0);
	}
}

size_t mu::llvm_::analyzer::operation::count ()
{
	return 1;
}

void mu::llvm_::analyzer::operation::add (std::vector <boost::shared_ptr <mu::core::node>> * results, boost::shared_ptr <mu::core::cluster> cluster_a)
{
	results->push_back (cluster_a);
}