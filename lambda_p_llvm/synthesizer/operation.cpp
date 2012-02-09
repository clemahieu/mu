#include "operation.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_io/ast/cluster.h>
#include <lambda_p_llvm/module/node.h>
#include <lambda_p_llvm/analyzer/operation.h>
#include <lambda_p_script_io/synthesizer.h>
#include <lambda_p/cluster.h>
#include <lambda_p_script/cluster/node.h>
#include <lambda_p_script/routine.h>
#include <lambda_p_llvm/function_type/node.h>
#include <lambda_p_llvm/basic_block/node.h>
#include <lambda_p_llvm/context/node.h>
#include <lambda_p_llvm/value/node.h>
#include <lambda_p_llvm/argument/node.h>

#include <llvm/Module.h>
#include <llvm/Instructions.h>
#include <llvm/Constants.h>

#include <boost/make_shared.hpp>

#include <utility>

void lambda_p_llvm::synthesizer::operation::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_io::ast::cluster> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <lambda_p_llvm::module::node> (parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			lambda_p_llvm::analyzer::operation analyzer;
			std::vector <boost::shared_ptr <lambda_p::node>> arguments;
			std::vector <boost::shared_ptr <lambda_p::node>> results;
			arguments.push_back (one);
			analyzer (errors_a, arguments, results);
			if (!(*errors_a) ())
			{
				analyzer.context.context_m->context = &two->module->getContext ();
				auto cluster (boost::static_pointer_cast <lambda_p::cluster> (results [0]));
				lambda_p_script_io::synthesizer synthesizer;
				std::vector <boost::shared_ptr <lambda_p::node>> arguments;
				std::vector <boost::shared_ptr <lambda_p::node>> results;
				arguments.push_back (cluster);
				synthesizer (errors_a, arguments, results);
				std::vector <std::pair <llvm::Function *, boost::shared_ptr <lambda_p_llvm::function_type::node>>> functions;
				if (!(*errors_a) ())
				{
					auto cluster (boost::static_pointer_cast <lambda_p_script::cluster::node> (results [0]));
					if (!cluster->routines.empty ())
					{
						for (auto i (cluster->routines.begin ()), j (cluster->routines.end ()); i != j && ! (*errors_a) (); ++i)
						{
							auto signature_routine (*i);
							std::vector <boost::shared_ptr <lambda_p::node>> arguments;
							std::vector <boost::shared_ptr <lambda_p::node>> results;
							signature_routine->perform (errors_a, arguments, results);
							if (!(*errors_a) ())
							{
								if (results.size () == 1)
								{
									auto function_type (boost::dynamic_pointer_cast <lambda_p_llvm::function_type::node> (results [0]));
									if (function_type.get () != nullptr)
									{
										auto function (llvm::Function::Create (function_type->function_type (), llvm::GlobalValue::ExternalLinkage));
										two->module->getFunctionList ().push_back (function);
										functions.push_back (std::pair <llvm::Function *, boost::shared_ptr <lambda_p_llvm::function_type::node>> (function, function_type));
									}
									else
									{
										(*errors_a) (L"Signature routine did not return a function_type");
									}
								}
								else
								{
									(*errors_a) (L"Signature routine did not return exactly one argument");
								}
							}
							++i;
							if (i == j)
							{
								(*errors_a) (L"Signature doesn't have an associated routine");
							}
						}
						size_t position (0);
						for (auto i (cluster->routines.begin ()), j (cluster->routines.end ()); i != j && ! (*errors_a) (); ++i, ++position)
						{
							++i;
							if (i != j)
							{
								auto signature_routine (*i);
								auto function (functions [position]);
								assert (function.first->getBasicBlockList ().size () == 0);
								auto block (llvm::BasicBlock::Create (function.first->getContext ()));
								function.first->getBasicBlockList ().push_back (block);
								analyzer.context.block->block = block;
								std::vector <boost::shared_ptr <lambda_p::node>> arguments;
								{
									auto k (function.second->parameters.begin ());
									auto l (function.second->parameters.end ());
									for (auto i (function.first->arg_begin ()), j (function.first->arg_end ()); i != j; ++i, ++k)
									{
										llvm::Argument * argument (i);
										arguments.push_back (boost::make_shared <lambda_p_llvm::argument::node> (argument, *k));
									}
								}
								std::vector <boost::shared_ptr <lambda_p::node>> results;
								signature_routine->perform (errors_a, arguments, results);						
								if (!(*errors_a) ())
								{
									if (results.size () == 0)
									{
										analyzer.context.block->block->getInstList ().push_back (llvm::ReturnInst::Create (two->module->getContext ()));
									}
									else if (results.size () == 1)
									{
										auto value (boost::dynamic_pointer_cast <lambda_p_llvm::value::node> (results [0]));
										if (value.get () != nullptr)
										{
											analyzer.context.block->block->getInstList ().push_back (llvm::ReturnInst::Create (two->module->getContext (), value->value ()));
										}
										else
										{
											(*errors_a) (L"Body routine didn't return a value");
										}
									}
									else
									{
										std::vector <llvm::Type *> types;
										std::vector <llvm::Value *> values;
										for (auto i (results.begin ()), j (results.end ()); i != j; ++i)
										{
											auto value (boost::dynamic_pointer_cast <lambda_p_llvm::value::node> (*i));
											if (value.get () != nullptr)
											{
												types.push_back (value->type->type ());
												values.push_back (value->value ());
											}
											else
											{
												(*errors_a) (L"Body routine didn't return a value");
											}
										}
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
							else
							{
								(*errors_a) (L"Signature routine doesn't have associated body routine");
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