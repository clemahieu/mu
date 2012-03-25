#include <mu/llvm_/synthesizer/operation.h>

#include <mu/script/context.h>
#include <mu/script/check.h>
#include <mu/core/cluster.h>
#include <mu/llvm_/module/node.h>
#include <mu/llvm_/cluster/node.h>
#include <mu/script/builder.h>
#include <mu/script/synthesizer/operation.h>
#include <mu/script/cluster/node.h>
#include <mu/script/runtime/routine.h>
#include <mu/llvm_/function_type/node.h>
#include <mu/llvm_/function/node.h>
#include <mu/llvm_/pointer_type/node.h>
#include <mu/core/routine.h>
#include <mu/core/expression.h>
#include <mu/script/cluster/remap.h>
#include <mu/llvm_/basic_block/node.h>
#include <mu/llvm_/argument/node.h>
#include <mu/script/values/operation.h>

#include <boost/make_shared.hpp>
#include <boost/tuple/tuple.hpp>

#include <llvm/Function.h>
#include <llvm/Module.h>
#include <llvm/BasicBlock.h>
#include <llvm/Argument.h>
#include <llvm/Instructions.h>
#include <llvm/Constants.h>

bool mu::llvm_::synthesizer::operation::operator () (mu::script::context & context_a)
{
	bool valid (mu::script::check <mu::core::cluster, mu::script::values::operation> () (context_a));
	if (valid)
	{
		auto cluster (boost::static_pointer_cast <mu::core::cluster> (context_a.parameters (0)));
		auto context_l (boost::static_pointer_cast <mu::script::values::operation> (context_a.parameters (1)));
		assert (boost::dynamic_pointer_cast <mu::llvm_::module::node> (context_l->values [1]).get () != nullptr);
		auto module (boost::static_pointer_cast <mu::llvm_::module::node> (context_l->values [1]));
		auto block (boost::static_pointer_cast <mu::llvm_::basic_block::node> (context_l->values [2]));
		context_a.reserve (4);
		auto result (boost::make_shared <mu::llvm_::cluster::node> ());
		context_a.locals (0) = result;
		auto type_cluster (boost::make_shared <mu::core::cluster> ());
		context_a.locals (1) = type_cluster;
		auto body_cluster (boost::make_shared <mu::core::cluster> ());
		context_a.locals (2) = body_cluster;
		auto remap (boost::make_shared <mu::script::cluster::remap> ());
		context_a.locals (3) = remap;
		if (cluster->routines.size () % 2 == 0)
		{
			for (auto i (cluster->routines.begin ()), j (cluster->routines.end ()); i != j; ++i)
			{
				type_cluster->routines.push_back (*i);
				++i;
				body_cluster->routines.push_back (*i);
			}
			context_a.push (boost::make_shared <mu::script::synthesizer::operation> ());
			context_a.push (type_cluster);
			valid = context_a ();
			assert (context_a.working_size () == 1);
			assert (boost::dynamic_pointer_cast <mu::script::cluster::node> (context_a.working (0)).get () != nullptr);
			auto cluster_l (boost::static_pointer_cast <mu::script::cluster::node> (context_a.working (0)));
			std::vector <boost::tuple <boost::shared_ptr <mu::llvm_::function::node>, boost::shared_ptr <mu::llvm_::function_type::node>>> functions;
			context_a.slide ();
			{
				auto k (body_cluster->routines.begin ());
				auto l (body_cluster->routines.end ());
				for (auto i (cluster_l->routines.begin ()), j (cluster_l->routines.end ()); i != j; ++i, ++k)
				{
					context_a.push (*i);
					auto valid_l (context_a ());
					valid = valid && valid_l;
					if (valid_l)
					{
						assert (context_a.working_size () == 1);
					}
					auto function_type (boost::dynamic_pointer_cast <mu::llvm_::function_type::node> (context_a.working (0)));
					if (function_type.get () != nullptr)
					{
						auto function (boost::make_shared <mu::llvm_::function::node> (llvm::Function::Create (function_type->function_type (), llvm::GlobalValue::PrivateLinkage), boost::make_shared <mu::llvm_::pointer_type::node> (function_type)));
						module->module->getFunctionList ().push_back (function->function ());
						remap->mapping [*k] = function;
						functions.push_back (boost::tuple <boost::shared_ptr <mu::llvm_::function::node>, boost::shared_ptr <mu::llvm_::function_type::node>> (function, function_type));
					}
					else
					{
						valid = false;
						context_a.errors (L"Type routine returned something that wasn't a function type");
					}
					context_a.drop ();
				}
			}
			if (valid)
			{
				context_a.push (remap);
				context_a.push (body_cluster);
				valid = context_a ();
				if (valid)
				{
					assert (context_a.working_size () == 1);
					assert (boost::dynamic_pointer_cast <mu::core::cluster> (context_a.working (0)));
					auto remapped_cluster (boost::static_pointer_cast <mu::core::cluster> (context_a.working (0)));
					context_a.slide ();
					context_a.push (boost::make_shared <mu::script::synthesizer::operation> ());
					context_a.push (remapped_cluster);
					valid = context_a ();
					if (valid)
					{
						assert (context_a.working_size () == 1);
						assert (boost::dynamic_pointer_cast <mu::script::cluster::node> (context_a.working (0)));
						auto body_cluster (boost::static_pointer_cast <mu::script::cluster::node> (context_a.working (0)));
						{
							context_a.slide ();
							auto i (functions.begin ());
							auto j (functions.end ());
							for (auto k (body_cluster->routines.begin ()), l (body_cluster->routines.end ()); k != l; ++k)
							{
								result->routines.push_back ((*i).get <0> ());
								auto llvm_block (llvm::BasicBlock::Create (module->module->getContext ()));
								(*i).get <0> ()->function ()->getBasicBlockList ().push_back (llvm_block);
								block->block = llvm_block;
								context_a.push (*k);
								{
									auto o ((*i).get <1> ()->parameters.begin ());
									auto p ((*i).get <1> ()->parameters.end ());
									for (auto m ((*i).get <0> ()->function ()->arg_begin ()), n ((*i).get <0> ()->function ()->arg_end ()); m != n; ++m, ++o)
									{
										llvm::Argument * argument (m);
										context_a.push (boost::make_shared <mu::llvm_::argument::node> (argument, *o));
									}
								}
								auto valid_l (context_a ());
								valid = valid && valid_l;
								if (valid_l)
								{		
									auto valid_l (true);
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
											valid_l = false;
											valid = false;
										}
									}
									context_a.drop ();
									if (valid_l)
									{
										if (values.size () == 0)
										{
											block->block->getInstList ().push_back (llvm::ReturnInst::Create (module->module->getContext ()));
										}
										else if (values.size () == 1)
										{
											block->block->getInstList ().push_back (llvm::ReturnInst::Create (module->module->getContext (), values [0]));
										}
										else
										{
											auto ret_type (llvm::StructType::get (module->module->getContext (), types));
											llvm::Value * result (llvm::UndefValue::get (ret_type));
											size_t position (0);
											for (auto i (values.begin ()), j (values.end ()); i != j; ++i, ++position)
											{
												auto instruction (llvm::InsertValueInst::Create (result, *i, position));
												result = instruction;
												block->block->getInstList ().push_back (instruction);
											}
											block->block->getInstList ().push_back (llvm::ReturnInst::Create (module->module->getContext (), result));
										}
									}
								}
								else
								{
									context_a.errors (L"Error running body routine");
								}
								context_a.drop ();
							}
						}
						context_a.push (result);
					}
					else
					{
						context_a.errors (L"Unable to synthesize body routines");
					}
				}
				else
				{
					context_a.errors (L"Unable to remap cluster");
				}
			}
		}
		else
		{
			context_a.errors (L"Cluster does not contain a signature routine for every body routine");
			valid = false;
		}
	}
	return valid;
}