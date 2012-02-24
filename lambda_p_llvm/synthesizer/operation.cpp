#include "operation.h"

#include <mu/core/errors/error_target.h>
#include <mu/io/ast/cluster.h>
#include <lambda_p_llvm/module/node.h>
#include <lambda_p_llvm/analyzer/operation.h>
#include <lambda_p_script_io/synthesizer.h>
#include <mu/core/cluster.h>
#include <mu/script/cluster/node.h>
#include <mu/script/routine.h>
#include <lambda_p_llvm/function_type/node.h>
#include <lambda_p_llvm/basic_block/node.h>
#include <lambda_p_llvm/context/node.h>
#include <lambda_p_llvm/value/node.h>
#include <lambda_p_llvm/argument/node.h>
#include <lambda_p_llvm/pointer_type/node.h>
#include <lambda_p_llvm/function_type/node.h>
#include <lambda_p_llvm/cluster/node.h>
#include <mu/script/values/operation.h>
#include <lambda_p_llvm/function_type/create.h>
#include <lambda_p_llvm/function/node.h>

#include <llvm/Module.h>
#include <llvm/Instructions.h>
#include <llvm/Constants.h>

#include <boost/make_shared.hpp>

#include <utility>
#include <set>

void lambda_p_llvm::synthesizer::operation::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results_a)
{
	auto one (boost::dynamic_pointer_cast <mu::io::ast::cluster> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <lambda_p_llvm::module::node> (parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			std::vector <boost::shared_ptr <mu::core::node>> arguments;
			std::vector <boost::shared_ptr <mu::core::node>> results;
			arguments.push_back (one);
			analyzer (errors_a, arguments, results);
			if (!(*errors_a) ())
			{
				analyzer.context.context_m->context = &two->module->getContext ();
				analyzer.context.module->module = two->module;
				auto cluster (boost::static_pointer_cast <mu::core::cluster> (results [0]));
				lambda_p_script_io::synthesizer synthesizer;
				std::vector <boost::shared_ptr <mu::core::node>> arguments;
				std::vector <boost::shared_ptr <mu::core::node>> results;
				arguments.push_back (cluster);
				synthesizer (errors_a, arguments, results);
				std::vector <std::pair <llvm::Function *, boost::shared_ptr <lambda_p_llvm::function_type::node>>> functions;
				if (!(*errors_a) ())
				{
					auto cluster (boost::static_pointer_cast <mu::script::cluster::node> (results [0]));
					auto result (boost::make_shared <lambda_p_llvm::cluster::node> ());
					results_a.push_back (result);
					if (!cluster->routines.empty ())
					{
						std::map <boost::shared_ptr <mu::core::node>, boost::shared_ptr <mu::core::node>> remap;
						for (auto i (cluster->routines.begin ()), j (cluster->routines.end ()); i != j && ! (*errors_a) (); ++i)
						{
							auto argument_routine (*i);
							std::vector <boost::shared_ptr <mu::core::node>> a1;
							std::vector <boost::shared_ptr <mu::core::node>> r1;
							argument_routine->perform (errors_a, a1, r1);
							if (!(*errors_a) ())
							{
								++i;
								if (i != j)
								{
									auto result_routine (*i);
									std::vector <boost::shared_ptr <mu::core::node>> a2;
									std::vector <boost::shared_ptr <mu::core::node>> r2;
									result_routine->perform (errors_a, a2, r2);
									if (!(*errors_a) ())
									{
										++i;
										if (i != j)
										{
											auto arguments (boost::make_shared <mu::script::values::operation> ());
											for (auto i (r1.begin ()), j (r1.end ()); i != j; ++i)
											{
												arguments->values.push_back (*i);
											}
											auto results (boost::make_shared <mu::script::values::operation> ());
											for (auto i (r2.begin ()), j (r2.end ()); i != j; ++i)
											{
												results->values.push_back (*i);
											}
											auto function_type_create (boost::make_shared <lambda_p_llvm::function_type::create> ());
											std::vector <boost::shared_ptr <mu::core::node>> a3;
											std::vector <boost::shared_ptr <mu::core::node>> r3;
											a3.push_back (analyzer.context.context_m);
											a3.push_back (arguments);
											a3.push_back (results);
											function_type_create->perform (errors_a, a3, r3);
											if (!(*errors_a) ())
											{
												auto function_type (boost::dynamic_pointer_cast <lambda_p_llvm::function_type::node> (r3 [0]));
												if (function_type.get () != nullptr)
												{
													auto function (llvm::Function::Create (function_type->function_type (), llvm::GlobalValue::PrivateLinkage));
													two->module->getFunctionList ().push_back (function);
													auto fun (boost::make_shared <lambda_p_llvm::function::node> (function, boost::make_shared <lambda_p_llvm::pointer_type::node> (function_type)));
													result->routines.push_back (fun);
													functions.push_back (std::pair <llvm::Function *, boost::shared_ptr <lambda_p_llvm::function_type::node>> (function, function_type));
													auto body_routine (*i);
													remap [body_routine] = fun;
												}
												else
												{
													(*errors_a) (L"Signature routine did not return a function_type");
												}
											}
										}
										else
										{
											(*errors_a) (L"Function does not have body routine");
										}
									}
								}
								else
								{
									(*errors_a) (L"Function does not have results routine");
								}
							}
						}
						result->set_names (cluster, remap);
						cluster->remap (remap);
						size_t position (0);
						for (auto i (cluster->routines.begin ()), j (cluster->routines.end ()); i != j && ! (*errors_a) (); ++i, ++position)
						{
							++i;
							++i;
							auto signature_routine (*i);
							auto function (functions [position]);
							assert (function.first->getBasicBlockList ().size () == 0);
							auto block (llvm::BasicBlock::Create (function.first->getContext ()));
							function.first->getBasicBlockList ().push_back (block);
							analyzer.context.block->block = block;
							std::vector <boost::shared_ptr <mu::core::node>> arguments;
							{
								auto k (function.second->parameters.begin ());
								auto l (function.second->parameters.end ());
								for (auto i (function.first->arg_begin ()), j (function.first->arg_end ()); i != j; ++i, ++k)
								{
									llvm::Argument * argument (i);
									arguments.push_back (boost::make_shared <lambda_p_llvm::argument::node> (argument, *k));
								}
							}
							std::vector <boost::shared_ptr <mu::core::node>> results;
							signature_routine->perform (errors_a, arguments, results);						
							if (!(*errors_a) ())
							{
								std::vector <llvm::Type *> types;
								std::vector <llvm::Value *> values;
								for (auto i (results.begin ()), j (results.end ()); i != j; ++i)
								{
									auto value (boost::dynamic_pointer_cast <lambda_p_llvm::value::node> (*i));
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
										(*errors_a) (L"Body routine returned something that wasn't a value");
									}
								}
								if (!(*errors_a) ())
								{
									if (values.size () == 0)
									{
										analyzer.context.block->block->getInstList ().push_back (llvm::ReturnInst::Create (two->module->getContext ()));
									}
									else if (values.size () == 1)
									{
										analyzer.context.block->block->getInstList ().push_back (llvm::ReturnInst::Create (two->module->getContext (), values [0]));
									}
									else
									{
										auto ret_type (llvm::StructType::get (two->module->getContext (), types));
										llvm::Value * result (llvm::UndefValue::get (ret_type));
										size_t position (0);
										for (auto i (values.begin ()), j (values.end ()); i != j; ++i, ++position)
										{
											auto instruction (llvm::InsertValueInst::Create (result, *i, position));
											result = instruction;
											analyzer.context.block->block->getInstList ().push_back (instruction);
										}
										analyzer.context.block->block->getInstList ().push_back (llvm::ReturnInst::Create (two->module->getContext (), result));
									}
								}
							}
						}
					}
				}
			}
		}
		else
		{
			invalid_type (errors_a, parameters [1], 1);
		}
	}
	else
	{
		invalid_type (errors_a, parameters [0], 0);
	}
}

size_t lambda_p_llvm::synthesizer::operation::count ()
{
	return 2;
}