#include <mu/llvm_/api.h>

#include <mu/io/analyzer/extensions/global.h>
#include <mu/llvm_/context/create.h>
#include <mu/llvm_/module/add_package.h>
#include <mu/llvm_/module/assemble.h>
#include <mu/llvm_/module/create.h>
#include <mu/llvm_/module/get_function.h>
#include <mu/llvm_/execution_engine/create_jit.h>
#include <mu/llvm_/execution_engine/run_function.h>
#include <mu/llvm_/module/get_package.h>
#include <mu/llvm_/linker/link_modules.h>
#include <mu/llvm_/compile/operation.h>
#include <mu/llvm_/value/get_context.h>
#include <mu/llvm_/value/get_type.h>
#include <mu/llvm_/integer_type/create.h>
#include <mu/llvm_/execution_engine/generic_value/create_int.h>
#include <mu/llvm_/synthesizer/operation.h>
#include <mu/llvm_/cluster/get.h>
#include <mu/llvm_/value/set_name.h>
#include <mu/llvm_/module/print.h>
#include <mu/llvm_/linkage_types/node.h>
#include <mu/llvm_/global_value/set_linkage.h>
#include <mu/llvm_/module/verify.h>
#include <mu/llvm_/function/create.h>
#include <mu/llvm_/function_type/create.h>
#include <mu/llvm_/module/add_function.h>
#include <mu/llvm_/apint/create.h>
#include <mu/llvm_/pointer_type/create.h>
#include <mu/llvm_/global_variable/create.h>
#include <mu/llvm_/module/add_global_variable.h>
#include <mu/llvm_/module/merge.h>
#include <mu/script/extensions/node.h>
#include <mu/io/analyzer/extensions/extensions.h>
#include <mu/llvm_/apint/extension.h>
#include <mu/llvm_/constant_int/extension.h>
#include <mu/llvm_/constant_string/extension.h>
#include <mu/script/values/operation.h>
#include <mu/llvm_/basic_block/node.h>
#include <mu/script/identity/operation.h>
#include <mu/script/closure/single.h>
#include <mu/llvm_/apint/node.h>
#include <mu/llvm_/struct_type/create.h>
#include <mu/llvm_/constant_int/create.h>
#include <mu/llvm_/basic_block/instruction_insert.h>
#include <mu/llvm_/basic_block/split_return.h>
#include <mu/llvm_/instructions/add.h>
#include <mu/llvm_/instructions/and_c.h>
#include <mu/llvm_/instructions/ashr.h>
#include <mu/llvm_/instructions/bitcast.h>
#include <mu/llvm_/instructions/call.h>
#include <mu/llvm_/instructions/cmpxchg.h>
#include <mu/llvm_/instructions/icmp.h>
#include <mu/llvm_/instructions/inttoptr.h>
#include <mu/llvm_/instructions/load.h>
#include <mu/llvm_/instructions/lshr.h>
#include <mu/llvm_/instructions/mul.h>
#include <mu/llvm_/instructions/or_c.h>
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
#include <mu/llvm_/instructions/xor_c.h>
#include <mu/llvm_/instructions/zext.h>
#include <mu/llvm_/predicate/node.h>
#include <mu/llvm_/null/create.h>
#include <mu/llvm_/ccall/operation.h>
#include <mu/llvm_/context/node.h>
#include <mu/llvm_/module/node.h>
#include <mu/llvm_/basic_block/node.h>
#include <mu/llvm_/function_type/divider.h>
#include <mu/core/expression.h>

#include <boost/make_shared.hpp>

#include <gc_cpp.h>

void mu::llvm_::api::binding (mu::script::extensions::node *& results, mu::script::values::operation *& context)
{
	results = new mu::script::extensions::node;
	context = new mu::script::values::operation;
	auto ctx (new (GC) mu::llvm_::context::node (nullptr));
	context->values.push_back (ctx);
	auto module (new (GC) mu::llvm_::module::node (nullptr));
	context->values.push_back (module);
	auto block (new (GC) mu::llvm_::basic_block::node (nullptr));
	context->values.push_back (block);
	results->extensions->extensions_m [std::wstring (L"#")] = new (GC) mu::llvm_::apint::extension;
	results->extensions->extensions_m [std::wstring (L"#i")] = new (GC) mu::llvm_::constant_int::extension (ctx);
	results->extensions->extensions_m [std::wstring (L"`")] = new (GC) mu::llvm_::constant_string::extension (module);
	results->extensions->extensions_m [std::wstring (L"..")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::function_type::divider);
	results->extensions->extensions_m [std::wstring (L"~")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::script::identity::operation);
	auto function_type (new (GC) mu::script::closure::single (new (GC) mu::llvm_::function_type::create));
	function_type->closed.push_back (ctx);
	results->extensions->extensions_m [std::wstring (L"fun-t")] = new (GC) mu::io::analyzer::extensions::global (function_type);
	auto integer_type (new (GC) mu::script::closure::single (new (GC) mu::llvm_::integer_type::create));
	integer_type->closed.push_back (ctx);
	results->extensions->extensions_m [std::wstring (L"int-t")] = new (GC) mu::io::analyzer::extensions::global (integer_type);
	auto i1_type (new (GC) mu::script::closure::single (new (GC) mu::llvm_::integer_type::create));
	i1_type->closed.push_back (ctx);
	i1_type->closed.push_back (new (GC) mu::llvm_::apint::node (new llvm::APInt (64, 1)));
	auto i1_call (new (GC) mu::core::expression);
	i1_call->dependencies.push_back (i1_type);
	results->extensions->extensions_m [std::wstring (L"i1")] = new (GC) mu::io::analyzer::extensions::global (i1_call);
	auto i8_type (new (GC) mu::script::closure::single (new (GC) mu::llvm_::integer_type::create));
	i8_type->closed.push_back (ctx);
	i8_type->closed.push_back (new (GC) mu::llvm_::apint::node (new llvm::APInt (64, 8)));
	auto i8_call (new (GC) mu::core::expression);
	i8_call->dependencies.push_back (i8_type);
	results->extensions->extensions_m [std::wstring (L"i8")] = new (GC) mu::io::analyzer::extensions::global (i8_call);
	auto i16_type (new (GC) mu::script::closure::single (new (GC) mu::llvm_::integer_type::create));
	i16_type->closed.push_back (ctx);
	i16_type->closed.push_back (new (GC) mu::llvm_::apint::node (new llvm::APInt (64, 16)));
	auto i16_call (new (GC) mu::core::expression);
	i16_call->dependencies.push_back (i16_type);
	results->extensions->extensions_m [std::wstring (L"i16")] = new (GC) mu::io::analyzer::extensions::global (i16_call);
	auto i32_type (new (GC) mu::script::closure::single (new (GC) mu::llvm_::integer_type::create));
	i32_type->closed.push_back (ctx);
	i32_type->closed.push_back (new (GC) mu::llvm_::apint::node (new llvm::APInt (64, 32)));
	auto i32_call (new (GC) mu::core::expression);
	i32_call->dependencies.push_back (i32_type);
	results->extensions->extensions_m [std::wstring (L"i32")] = new (GC) mu::io::analyzer::extensions::global (i32_call);
	auto i64_type (new (GC) mu::script::closure::single (new (GC) mu::llvm_::integer_type::create));
	i64_type->closed.push_back (ctx);
	i64_type->closed.push_back (new (GC) mu::llvm_::apint::node (new llvm::APInt (64, 64)));
	auto i64_call (new (GC) mu::core::expression);
	i64_call->dependencies.push_back (i64_type);
	results->extensions->extensions_m [std::wstring (L"i64")] = new (GC) mu::io::analyzer::extensions::global (i64_call);
	auto struct_type (new (GC) mu::script::closure::single (new (GC) mu::llvm_::struct_type::create));
	struct_type->closed.push_back (ctx);
	results->extensions->extensions_m [std::wstring (L"struct-t")] = new (GC) mu::io::analyzer::extensions::global (struct_type);
	auto constant_int (new (GC) mu::script::closure::single (new (GC) mu::llvm_::constant_int::create));
	constant_int->closed.push_back (ctx);
	results->extensions->extensions_m [std::wstring (L"int-c")] = new (GC) mu::io::analyzer::extensions::global (constant_int);
	results->extensions->extensions_m [std::wstring (L"add")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::add));
	results->extensions->extensions_m [std::wstring (L"and")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::and_c));
	results->extensions->extensions_m [std::wstring (L"ashr")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::ashr));
	results->extensions->extensions_m [std::wstring (L"bitcast")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::bitcast));
	auto call (new (GC) mu::llvm_::basic_block::split_return (block, new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::call)));
	results->extensions->extensions_m [std::wstring (L"call")] = new (GC) mu::io::analyzer::extensions::global (call);
	results->extensions->extensions_m [std::wstring (L"ccall")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::ccall::operation (block, call));
	results->extensions->extensions_m [std::wstring (L"cmpxchg")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::cmpxchg));
	results->extensions->extensions_m [std::wstring (L"eq")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::predicate::node (llvm::CmpInst::Predicate::ICMP_EQ));
	results->extensions->extensions_m [std::wstring (L"icmp")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::icmp));
	results->extensions->extensions_m [std::wstring (L"inttoptr")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::inttoptr));
	results->extensions->extensions_m [std::wstring (L"load")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::load));
	results->extensions->extensions_m [std::wstring (L"lshr")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::lshr));
	results->extensions->extensions_m [std::wstring (L"mul")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::mul));
	results->extensions->extensions_m [std::wstring (L"ne")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::predicate::node (llvm::CmpInst::Predicate::ICMP_NE));
	results->extensions->extensions_m [std::wstring (L"null")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::null::create);
	results->extensions->extensions_m [std::wstring (L"or")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::or_c));
	results->extensions->extensions_m [std::wstring (L"ptr")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::pointer_type::create);
	results->extensions->extensions_m [std::wstring (L"ptrtoint")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::ptrtoint));
	results->extensions->extensions_m [std::wstring (L"sdiv")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::sdiv));
	results->extensions->extensions_m [std::wstring (L"sext")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::sext));
	results->extensions->extensions_m [std::wstring (L"sge")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::predicate::node (llvm::CmpInst::Predicate::ICMP_SGE));
	results->extensions->extensions_m [std::wstring (L"sgt")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::predicate::node (llvm::CmpInst::Predicate::ICMP_SGT));
	results->extensions->extensions_m [std::wstring (L"shl")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::shl));
	results->extensions->extensions_m [std::wstring (L"sle")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::predicate::node (llvm::CmpInst::Predicate::ICMP_SLE));
	results->extensions->extensions_m [std::wstring (L"slt")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::predicate::node (llvm::CmpInst::Predicate::ICMP_SLT));
	results->extensions->extensions_m [std::wstring (L"srem")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::srem));
	results->extensions->extensions_m [std::wstring (L"store")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::store));
	results->extensions->extensions_m [std::wstring (L"sub")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::sub));
	results->extensions->extensions_m [std::wstring (L"trunc")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::trunc));
	results->extensions->extensions_m [std::wstring (L"udiv")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::udiv));
	results->extensions->extensions_m [std::wstring (L"uge")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::predicate::node (llvm::CmpInst::Predicate::ICMP_UGE));
	results->extensions->extensions_m [std::wstring (L"ugt")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::predicate::node (llvm::CmpInst::Predicate::ICMP_UGT));
	results->extensions->extensions_m [std::wstring (L"ule")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::predicate::node (llvm::CmpInst::Predicate::ICMP_ULE));
	results->extensions->extensions_m [std::wstring (L"ult")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::predicate::node (llvm::CmpInst::Predicate::ICMP_ULT));
	results->extensions->extensions_m [std::wstring (L"urem")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::urem));
	results->extensions->extensions_m [std::wstring (L"xor")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::xor_c));
	results->extensions->extensions_m [std::wstring (L"zext")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::zext));
}