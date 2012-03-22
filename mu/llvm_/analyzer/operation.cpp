#include <mu/llvm_/analyzer/operation.h>

#include <mu/io/ast/expression.h>
#include <mu/io/analyzer/analyzer.h>
#include <mu/core/routine.h>
#include <mu/io/analyzer/extensions/extensions.h>
#include <mu/io/analyzer/extensions/global.h>
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
#include <mu/llvm_/apint/extension.h>
#include <mu/script/string/extension.h>
#include <mu/io/ast/end.h>
#include <mu/io/ast/cluster.h>
#include <mu/llvm_/value/get_type.h>
#include <mu/io/builder.h>
#include <mu/llvm_/basic_block/insert.h>
#include <mu/llvm_/basic_block/node.h>
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
#include <mu/io/ast/expression.h>
#include <mu/io/ast/identifier.h>
#include <mu/script/values/operation.h>
#include <mu/llvm_/function_type/node.h>
#include <mu/llvm_/pointer_type/node.h>
#include <mu/llvm_/function/node.h>
#include <mu/llvm_/argument/node.h>
#include <mu/llvm_/cluster/node.h>
#include <mu/script/check.h>

#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

#include <llvm/ADT/APInt.h>
#include <llvm/Function.h>
#include <llvm/Module.h>
#include <llvm/BasicBlock.h>
#include <llvm/Constants.h>

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
	extensions->extensions_m [std::wstring (L"and")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (context.block, boost::make_shared <mu::llvm_::instructions::and_c> ()));
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
	extensions->extensions_m [std::wstring (L"or")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (context.block, boost::make_shared <mu::llvm_::instructions::or_c> ()));
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
	extensions->extensions_m [std::wstring (L"xor")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (context.block, boost::make_shared <mu::llvm_::instructions::xor_c> ()));
	extensions->extensions_m [std::wstring (L"zext")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::basic_block::instruction_insert> (context.block, boost::make_shared <mu::llvm_::instructions::zext> ()));
}

bool mu::llvm_::analyzer::operation::operator () (mu::script::context & context_a)
{
	bool valid (mu::script::check <mu::llvm_::context::node, mu::llvm_::module::node, mu::io::ast::cluster> () (context_a));
	if (valid)
	{
		auto context_l (boost::static_pointer_cast <mu::llvm_::context::node> (context_a.parameters (0)));
		auto module (boost::static_pointer_cast <mu::llvm_::module::node> (context_a.parameters (1)));
		auto cluster (boost::static_pointer_cast <mu::io::ast::cluster> (context_a.parameters (2)));
		context.context_m->context = context_l->context;
		context.module->module = module->module;
		std::vector <boost::shared_ptr <mu::llvm_::function::node>> types;		
		std::vector <std::pair <boost::shared_ptr <mu::llvm_::function::node>, boost::shared_ptr <mu::llvm_::function_type::node>>> functions;
		auto function (boost::bind (&mu::llvm_::analyzer::operation::finish_types, this, boost::ref (context_a), boost::ref (valid), boost::ref (functions), boost::ref (types), _1, _2));
		{
			mu::io::analyzer::analyzer analyzer (function, context_a.errors.target, extensions);
			auto i (cluster->expressions.begin ());
			auto j (cluster->expressions.end ());
			while (i != j && valid)
			{
				auto value (*i);
				if (value->individual_names.empty () && value->full_name->string.empty ())
				{
					analyzer.input (*i);
					++i;
					if (i != j)
					{
						auto value (*i);
						if (value->individual_names.empty () && value->full_name->string.empty ())
						{
							analyzer.input (*i);
							++i;
							if (i != j)
							{
								++i;
							}
							else
							{
								context_a.errors (L"There is not a body routine for every argument/result pair");
								valid = false;
							}
						}
						else
						{
							context_a.errors (L"Result routines cannot have names");
							valid = false;
						}
					}
					else
					{
						context_a.errors (L"There is not a result routine for every argument routine");
						valid = false;
					}
				}
				else
				{
					context_a.errors (L"Argument routines cannot have names");
					valid = false;
				}
			}
			mu::io::debugging::context context;
			if (cluster->expressions.size () > 0)
			{
				context = mu::io::debugging::context (cluster->expressions [cluster->expressions.size () - 1]->context.last, cluster->expressions [cluster->expressions.size () - 1]->context.last);
			}
			analyzer.input (boost::make_shared <mu::io::ast::end> (context));
		}
		{
			auto function (boost::bind (&mu::llvm_::analyzer::operation::finish_bodies, this, boost::ref (context_a), boost::ref (valid), boost::ref (functions), _1, _2));
			mu::io::analyzer::analyzer analyzer (function, context_a.errors.target, extensions);
			auto i (cluster->expressions.begin ());
			auto j (cluster->expressions.end ());
			while (i != j)
			{
				++i;
				++i;
				analyzer.input (*i);
				++i;
			}
			mu::io::debugging::context context;
			if (cluster->expressions.size () > 0)
			{
				context = mu::io::debugging::context (cluster->expressions [cluster->expressions.size () - 1]->context.last, cluster->expressions [cluster->expressions.size () - 1]->context.last);
			}
			analyzer.input (boost::make_shared <mu::io::ast::end> (context));
		}
	}
	return valid;
}

void mu::llvm_::analyzer::operation::finish_bodies (mu::script::context & context_a, bool & valid_a, std::vector <std::pair <boost::shared_ptr <mu::llvm_::function::node>, boost::shared_ptr <mu::llvm_::function_type::node>>> & functions, boost::shared_ptr <mu::core::cluster> cluster_a, boost::shared_ptr <mu::io::debugging::mapping> cluster_info_a)
{	
	size_t position (0);
	auto result (boost::make_shared <mu::llvm_::cluster::node> ());
	for (auto i (cluster_a->routines.begin ()), j (cluster_a->routines.end ()); i != j; ++i, ++position)
	{
		auto signature_routine (*i);
		auto function (functions [position]);
		auto function_node (function.first);
		result->routines.push_back (function_node);
		assert (function_node->function ()->getBasicBlockList ().size () == 0);
		auto block (llvm::BasicBlock::Create (function_node->function ()->getContext ()));
		function_node->function ()->getBasicBlockList ().push_back (block);
		context.block->block = block;
		context_a.push (signature_routine);
		{
			auto k (function.second->parameters.begin ());
			auto l (function.second->parameters.end ());
			for (auto i (function_node->function ()->arg_begin ()), j (function_node->function ()->arg_end ()); i != j; ++i, ++k)
			{
				llvm::Argument * argument (i);
				context_a.push (boost::make_shared <mu::llvm_::argument::node> (argument, *k));
			}
		}
		valid_a = context_a ();
		if (valid_a)
		{
			std::vector <llvm::Type *> types;
			std::vector <llvm::Value *> values;
			for (auto i (context_a.working_begin ()), j (context_a.working_end ()); i != j; ++i)
			{
				auto value (boost::dynamic_pointer_cast <mu::llvm_::value::node> (*i));
				if (value.get () != nullptr)
				{
					auto value_l (value->value ());
					if (!value_l->getType ()->isVoidTy ())
					{
						types.push_back (value->type->type ());
						values.push_back (value->value ());
					}
				}
				else
				{
					context_a.errors (L"Body routine returned something that wasn't a value");
					valid_a = false;
				}
			}
			context_a.drop ();
			if (valid_a)
			{
				if (values.size () == 0)
				{
					context.block->block->getInstList ().push_back (llvm::ReturnInst::Create (context.module->module->getContext ()));
				}
				else if (values.size () == 1)
				{
					context.block->block->getInstList ().push_back (llvm::ReturnInst::Create (context.module->module->getContext (), values [0]));
				}
				else
				{
					auto ret_type (llvm::StructType::get (context.module->module->getContext (), types));
					llvm::Value * result (llvm::UndefValue::get (ret_type));
					size_t position (0);
					for (auto i (values.begin ()), j (values.end ()); i != j; ++i, ++position)
					{
						auto instruction (llvm::InsertValueInst::Create (result, *i, position));
						result = instruction;
						context.block->block->getInstList ().push_back (instruction);
					}
					context.block->block->getInstList ().push_back (llvm::ReturnInst::Create (context.module->module->getContext (), result));
				}
			}
		}
		context_a.drop ();
	}
	std::map <boost::shared_ptr <mu::core::routine>, boost::shared_ptr <mu::llvm_::function::node>> mapping;
	for (size_t i (0), j (cluster_a->routines.size ()); i != j; ++i)
	{
		mapping [cluster_a->routines [i]] = functions [i].first;
	}
	for (auto i (cluster_a->names.begin ()), j (cluster_a->names.end ()); i != j; ++i)
	{
		auto existing (mapping.find (i->second));
		assert (existing != mapping.end ());
		result->names [i->first] = existing->second;
	}
	context_a.push (result);
}

void mu::llvm_::analyzer::operation::finish_types (mu::script::context & context_a, bool & valid_a, std::vector <std::pair <boost::shared_ptr <mu::llvm_::function::node>, boost::shared_ptr <mu::llvm_::function_type::node>>> & functions, std::vector <boost::shared_ptr <mu::llvm_::function::node>> & types, boost::shared_ptr <mu::core::cluster> cluster_a, boost::shared_ptr <mu::io::debugging::mapping> cluster_info_a)
{
	assert (cluster_a->routines.size () % 2 == 0);
	assert (cluster_a->names.empty ());	
	for (auto i (cluster_a->routines.begin ()), j (cluster_a->routines.end ()); i != j; ++i)
	{
		context_a.push (*i);
		valid_a = context_a ();
		if (valid_a)
		{
			++i;
			auto arguments (boost::make_shared <mu::script::values::operation> ());
			for (auto i (context_a.working_begin ()), j (context_a.working_end ()); i != j; ++i)
			{
				arguments->values.push_back (*i);
			}
			context_a.drop ();
			context_a.push (*i);
			valid_a = context_a ();
			if (valid_a)
			{
				auto results (boost::make_shared <mu::script::values::operation> ());
				for (auto i (context_a.working_begin ()), j (context_a.working_end ()); i != j; ++i)
				{
					results->values.push_back (*i);
				}
				auto function_type_create (boost::make_shared <mu::llvm_::function_type::create> ());
				context_a.drop ();
				context_a.push (function_type_create);
				context_a.push (context.context_m);
				context_a.push (arguments);
				context_a.push (results);
				valid_a = context_a ();
				if (valid_a)
				{
					auto function_type (boost::dynamic_pointer_cast <mu::llvm_::function_type::node> (context_a.working (0)));
					if (function_type.get () != nullptr)
					{
						auto function (llvm::Function::Create (function_type->function_type (), llvm::GlobalValue::PrivateLinkage));
						context.module->module->getFunctionList ().push_back (function);
						auto fun (boost::make_shared <mu::llvm_::function::node> (function, boost::make_shared <mu::llvm_::pointer_type::node> (function_type)));
						functions.push_back (std::pair <boost::shared_ptr <mu::llvm_::function::node>, boost::shared_ptr <mu::llvm_::function_type::node>> (fun, function_type));
						types.push_back (fun);
					}
					else
					{
						context_a.errors (L"Signature routine did not return a function_type");
						valid_a = false;
					}
				}
			}
		}	
		context_a.drop ();
	}
}