#include <mu/llvm_/api.h>

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
#include <mu/io/keywording_extensions.h>

#include <gc_cpp.h>

void mu::llvm_::api::binding (mu::script::extensions::node *& results, mu::script::values::operation *& context)
{
	results = new (GC) mu::script::extensions::node;
	context = new (GC) mu::script::values::operation;
	auto ctx (new (GC) mu::llvm_::context::node (nullptr));
	context->values.push_back (ctx);
	auto module (new (GC) mu::llvm_::module::node (nullptr));
	context->values.push_back (module);
	auto block (new (GC) mu::llvm_::basic_block::node (nullptr));
	context->values.push_back (block);
    mu::io::keywording::extensions & extensions (*results->extensions);
    extensions.add <mu::llvm_::apint::extension> (mu::string (U"#"));
	extensions (mu::string (U"#i"), [ctx] (mu::io::keywording::keywording & keywording_a) { return new (GC) mu::llvm_::constant_int::extension (keywording_a, ctx); }, false);
	extensions (mu::string (U"`"), [module] (mu::io::keywording::keywording & keywording_a) { return new (GC) mu::llvm_::constant_string::extension (keywording_a, module); }, false);
	extensions (mu::string (U".."), new (GC) mu::llvm_::function_type::divider);
	extensions (mu::string (U"~"), new (GC) mu::script::identity::operation);
	auto function_type (new (GC) mu::script::closure::single (new (GC) mu::llvm_::function_type::create));
	function_type->closed.push_back (ctx);
	extensions (mu::string (U"fun-t"), function_type);
	auto integer_type (new (GC) mu::script::closure::single (new (GC) mu::llvm_::integer_type::create));
	integer_type->closed.push_back (ctx);
	extensions (mu::string (U"int-t"), integer_type);
	auto struct_type (new (GC) mu::script::closure::single (new (GC) mu::llvm_::struct_type::create));
	struct_type->closed.push_back (ctx);
	extensions (mu::string (U"struct-t"), struct_type);
	auto constant_int (new (GC) mu::script::closure::single (new (GC) mu::llvm_::constant_int::create));
	constant_int->closed.push_back (ctx);
	extensions (mu::string (U"int-c"), constant_int);
	extensions (mu::string (U"add"), new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::add));
	extensions (mu::string (U"and"), new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::and_c));
	extensions (mu::string (U"ashr"), new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::ashr));
	extensions (mu::string (U"bitcast"), new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::bitcast));
	auto call (new (GC) mu::llvm_::basic_block::split_return (block, new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::call)));
	extensions (mu::string (U"call"), call);
	extensions (mu::string (U"ccall"), new (GC) mu::llvm_::ccall::operation (block, call));
    extensions (mu::string (U"cmpxchg"), new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::cmpxchg));
	extensions (mu::string (U"eq"), new (GC) mu::llvm_::predicate::node (llvm::CmpInst::Predicate::ICMP_EQ));
	extensions (mu::string (U"icmp"), new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::icmp));
	extensions (mu::string (U"inttoptr"), new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::inttoptr));
	extensions (mu::string (U"load"), new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::load));
	extensions (mu::string (U"lshr"), new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::lshr));
	extensions (mu::string (U"mul"), new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::mul));
	extensions (mu::string (U"ne"), new (GC) mu::llvm_::predicate::node (llvm::CmpInst::Predicate::ICMP_NE));
	extensions (mu::string (U"null"), new (GC) mu::llvm_::null::create);
	extensions (mu::string (U"or"), new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::or_c));
	extensions (mu::string (U"ptr"), new (GC) mu::llvm_::pointer_type::create);
	extensions (mu::string (U"ptrtoint"), new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::ptrtoint));
	extensions (mu::string (U"sdiv"), new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::sdiv));
	extensions (mu::string (U"sext"), new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::sext));
	extensions (mu::string (U"sge"), new (GC) mu::llvm_::predicate::node (llvm::CmpInst::Predicate::ICMP_SGE));
	extensions (mu::string (U"sgt"), new (GC) mu::llvm_::predicate::node (llvm::CmpInst::Predicate::ICMP_SGT));
	extensions (mu::string (U"shl"), new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::shl));
	extensions (mu::string (U"sle"), new (GC) mu::llvm_::predicate::node (llvm::CmpInst::Predicate::ICMP_SLE));
	extensions (mu::string (U"slt"), new (GC) mu::llvm_::predicate::node (llvm::CmpInst::Predicate::ICMP_SLT));
	extensions (mu::string (U"srem"), new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::srem));
	extensions (mu::string (U"store"), new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::store));
	extensions (mu::string (U"sub"), new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::sub));
	extensions (mu::string (U"trunc"), new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::trunc));
	extensions (mu::string (U"udiv"), new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::udiv));
	extensions (mu::string (U"uge"), new (GC) mu::llvm_::predicate::node (llvm::CmpInst::Predicate::ICMP_UGE));
	extensions (mu::string (U"ugt"), new (GC) mu::llvm_::predicate::node (llvm::CmpInst::Predicate::ICMP_UGT));
	extensions (mu::string (U"ule"), new (GC) mu::llvm_::predicate::node (llvm::CmpInst::Predicate::ICMP_ULE));
	extensions (mu::string (U"ult"), new (GC) mu::llvm_::predicate::node (llvm::CmpInst::Predicate::ICMP_ULT));
	extensions (mu::string (U"urem"), new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::urem));
	extensions (mu::string (U"xor"), new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::xor_c));
	extensions (mu::string (U"zext"), new (GC) mu::llvm_::basic_block::instruction_insert (block, new (GC) mu::llvm_::instructions::zext));
}