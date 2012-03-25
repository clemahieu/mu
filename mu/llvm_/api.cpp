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

#include <boost/make_shared.hpp>

void mu::llvm_::api::binding (mu::script::extensions::node *& results, mu::script::values::operation *& context)
{
	results = new mu::script::extensions::node;
	context = new mu::script::values::operation;
	auto ctx (boost::make_shared <mu::llvm_::context::node> (nullptr));
	context->values.push_back (ctx);
	auto module (boost::make_shared <mu::llvm_::module::node> (nullptr));
	context->values.push_back (module);
	auto block (boost::make_shared <mu::llvm_::basic_block::node> (nullptr));
	context->values.push_back (block);
	results->extensions->extensions_m [std::wstring (L"#")] = boost::make_shared <mu::llvm_::apint::extension> ();
	results->extensions->extensions_m [std::wstring (L"#i")] = boost::make_shared <mu::llvm_::constant_int::extension> (ctx);
	results->extensions->extensions_m [std::wstring (L"`")] = boost::make_shared <mu::llvm_::constant_string::extension> (module);
	results->extensions->extensions_m [std::wstring (L"..")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::function_type::divider> ());
	results->extensions->extensions_m [std::wstring (L"~")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::identity::operation> ());
	auto function_type (boost::make_shared <mu::script::closure::single> (boost::make_shared <mu::llvm_::function_type::create> ()));
	function_type->closed.push_back (ctx);
	results->extensions->extensions_m [std::wstring (L"fun-t")] = boost::make_shared <mu::io::analyzer::extensions::global> (function_type);
	auto integer_type (boost::make_shared <mu::script::closure::single> (boost::make_shared <mu::llvm_::integer_type::create> ()));
	integer_type->closed.push_back (ctx);
	results->extensions->extensions_m [std::wstring (L"int-t")] = boost::make_shared <mu::io::analyzer::extensions::global> (integer_type);
	auto i1_type (boost::make_shared <mu::script::closure::single> (boost::make_shared <mu::llvm_::integer_type::create> ()));
	i1_type->closed.push_back (ctx);
	i1_type->closed.push_back (boost::make_shared <mu::llvm_::apint::node> (new llvm::APInt (64, 1)));
	results->extensions->extensions_m [std::wstring (L"i1")] = boost::make_shared <mu::io::analyzer::extensions::global> (i1_type);
	auto i8_type (boost::make_shared <mu::script::closure::single> (boost::make_shared <mu::llvm_::integer_type::create> ()));
	i8_type->closed.push_back (ctx);
	i8_type->closed.push_back (boost::make_shared <mu::llvm_::apint::node> (new llvm::APInt (64, 8)));
	results->extensions->extensions_m [std::wstring (L"i8")] = boost::make_shared <mu::io::analyzer::extensions::global> (i8_type);
	auto i16_type (boost::make_shared <mu::script::closure::single> (boost::make_shared <mu::llvm_::integer_type::create> ()));
	i16_type->closed.push_back (ctx);
	i16_type->closed.push_back (boost::make_shared <mu::llvm_::apint::node> (new llvm::APInt (64, 16)));
	results->extensions->extensions_m [std::wstring (L"i16")] = boost::make_shared <mu::io::analyzer::extensions::global> (i16_type);
	auto i32_type (boost::make_shared <mu::script::closure::single> (boost::make_shared <mu::llvm_::integer_type::create> ()));
	i32_type->closed.push_back (ctx);
	i32_type->closed.push_back (boost::make_shared <mu::llvm_::apint::node> (new llvm::APInt (64, 32)));
	results->extensions->extensions_m [std::wstring (L"i32")] = boost::make_shared <mu::io::analyzer::extensions::global> (i32_type);
	auto i64_type (boost::make_shared <mu::script::closure::single> (boost::make_shared <mu::llvm_::integer_type::create> ()));
	i64_type->closed.push_back (ctx);
	i64_type->closed.push_back (boost::make_shared <mu::llvm_::apint::node> (new llvm::APInt (64, 64)));
	results->extensions->extensions_m [std::wstring (L"i64")] = boost::make_shared <mu::io::analyzer::extensions::global> (i64_type);
	auto struct_type (boost::make_shared <mu::script::closure::single> (boost::make_shared <mu::llvm_::struct_type::create> ()));
	struct_type->closed.push_back (ctx);
	results->extensions->extensions_m [std::wstring (L"struct-t")] = boost::make_shared <mu::io::analyzer::extensions::global> (struct_type);
	auto constant_int (boost::make_shared <mu::script::closure::single> (boost::make_shared <mu::llvm_::constant_int::create> ()));
	constant_int->closed.push_back (ctx);
	results->extensions->extensions_m [std::wstring (L"int-c")] = boost::make_shared <mu::io::analyzer::extensions::global> (constant_int);
	results->extensions->extensions_m [std::wstring (L"add")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (block, boost::make_shared <mu::llvm_::instructions::add> ()));
	results->extensions->extensions_m [std::wstring (L"and")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (block, boost::make_shared <mu::llvm_::instructions::and_c> ()));
	results->extensions->extensions_m [std::wstring (L"ashr")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (block, boost::make_shared <mu::llvm_::instructions::ashr> ()));
	results->extensions->extensions_m [std::wstring (L"bitcast")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (block, boost::make_shared <mu::llvm_::instructions::bitcast> ()));
	auto call (boost::make_shared <mu::llvm_::basic_block::split_return> (block, boost::make_shared <mu::llvm_::basic_block::instruction_insert> (block, boost::make_shared <mu::llvm_::instructions::call> ())));
	results->extensions->extensions_m [std::wstring (L"call")] = boost::make_shared <mu::io::analyzer::extensions::global> (call);
	results->extensions->extensions_m [std::wstring (L"ccall")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::ccall::operation> (block, call));
	results->extensions->extensions_m [std::wstring (L"cmpxchg")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (block, boost::make_shared <mu::llvm_::instructions::cmpxchg> ()));
	results->extensions->extensions_m [std::wstring (L"eq")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::predicate::node> (llvm::CmpInst::Predicate::ICMP_EQ));
	results->extensions->extensions_m [std::wstring (L"icmp")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (block, boost::make_shared <mu::llvm_::instructions::icmp> ()));
	results->extensions->extensions_m [std::wstring (L"inttoptr")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (block, boost::make_shared <mu::llvm_::instructions::inttoptr> ()));
	results->extensions->extensions_m [std::wstring (L"load")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (block, boost::make_shared <mu::llvm_::instructions::load> ()));
	results->extensions->extensions_m [std::wstring (L"lshr")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (block, boost::make_shared <mu::llvm_::instructions::lshr> ()));
	results->extensions->extensions_m [std::wstring (L"mul")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (block, boost::make_shared <mu::llvm_::instructions::mul> ()));
	results->extensions->extensions_m [std::wstring (L"ne")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::predicate::node> (llvm::CmpInst::Predicate::ICMP_NE));
	results->extensions->extensions_m [std::wstring (L"null")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::null::create> ());
	results->extensions->extensions_m [std::wstring (L"or")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (block, boost::make_shared <mu::llvm_::instructions::or_c> ()));
	results->extensions->extensions_m [std::wstring (L"ptr")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::pointer_type::create> ());
	results->extensions->extensions_m [std::wstring (L"ptrtoint")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (block, boost::make_shared <mu::llvm_::instructions::ptrtoint> ()));
	results->extensions->extensions_m [std::wstring (L"sdiv")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (block, boost::make_shared <mu::llvm_::instructions::sdiv> ()));
	results->extensions->extensions_m [std::wstring (L"sext")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (block, boost::make_shared <mu::llvm_::instructions::sext> ()));
	results->extensions->extensions_m [std::wstring (L"sge")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::predicate::node> (llvm::CmpInst::Predicate::ICMP_SGE));
	results->extensions->extensions_m [std::wstring (L"sgt")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::predicate::node> (llvm::CmpInst::Predicate::ICMP_SGT));
	results->extensions->extensions_m [std::wstring (L"shl")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (block, boost::make_shared <mu::llvm_::instructions::shl> ()));
	results->extensions->extensions_m [std::wstring (L"sle")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::predicate::node> (llvm::CmpInst::Predicate::ICMP_SLE));
	results->extensions->extensions_m [std::wstring (L"slt")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::predicate::node> (llvm::CmpInst::Predicate::ICMP_SLT));
	results->extensions->extensions_m [std::wstring (L"srem")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (block, boost::make_shared <mu::llvm_::instructions::srem> ()));
	results->extensions->extensions_m [std::wstring (L"store")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (block, boost::make_shared <mu::llvm_::instructions::store> ()));
	results->extensions->extensions_m [std::wstring (L"sub")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (block, boost::make_shared <mu::llvm_::instructions::sub> ()));
	results->extensions->extensions_m [std::wstring (L"trunc")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (block, boost::make_shared <mu::llvm_::instructions::trunc> ()));
	results->extensions->extensions_m [std::wstring (L"udiv")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (block, boost::make_shared <mu::llvm_::instructions::udiv> ()));
	results->extensions->extensions_m [std::wstring (L"uge")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::predicate::node> (llvm::CmpInst::Predicate::ICMP_UGE));
	results->extensions->extensions_m [std::wstring (L"ugt")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::predicate::node> (llvm::CmpInst::Predicate::ICMP_UGT));
	results->extensions->extensions_m [std::wstring (L"ule")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::predicate::node> (llvm::CmpInst::Predicate::ICMP_ULE));
	results->extensions->extensions_m [std::wstring (L"ult")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::predicate::node> (llvm::CmpInst::Predicate::ICMP_ULT));
	results->extensions->extensions_m [std::wstring (L"urem")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (block, boost::make_shared <mu::llvm_::instructions::urem> ()));
	results->extensions->extensions_m [std::wstring (L"xor")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (block, boost::make_shared <mu::llvm_::instructions::xor_c> ()));
	results->extensions->extensions_m [std::wstring (L"zext")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (block, boost::make_shared <mu::llvm_::instructions::zext> ()));
}