#include "generator.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p_kernel/routine.h>
#include <lambda_p/binder/node_list.h>
#include <lambda_p_llvm/type.h>
#include <lambda_p_llvm/fo_value.h>
#include <lambda_p/core/routine.h>
#include <lambda_p_llvm/so_value.h>
#include <lambda_p_llvm/function_binder.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p_kernel/bind_procedure.h>
#include <lambda_p/binder/list.h>

#include <llvm/Function.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Module.h>
#include <llvm/Instructions.h>

#include <sstream>

lambda_p_llvm::generator::generator (lambda_p_llvm::generation_context & context_a)
	: context (context_a)
{
}

void lambda_p_llvm::generator::bind (lambda_p::core::statement * statement, lambda_p::binder::node_list & nodes, lambda_p::errors::error_list & problems)
{
	size_t position;
	check_count (1, 3, statement, problems);
	if (problems.errors.empty ())
	{
		auto routine (boost::dynamic_pointer_cast <lambda_p_kernel::routine> (nodes [statement->association->parameters [0]]));
		if (routine.get () != nullptr)
		{
			auto return_type (boost::dynamic_pointer_cast < lambda_p_llvm::type> (nodes [statement->association->parameters [1]]));
			if (return_type.get () != nullptr)
			{
				auto argument_list (boost::dynamic_pointer_cast <lambda_p::binder::list> (nodes [statement->association->parameters [2]]));
				if (argument_list.get () != nullptr)
				{
					if (argument_list->nodes.size () == routine->routine_m->surface->results.size ())
					{
						lambda_p::binder::node_list nodes_l;
						std::vector <size_t> open_positions;
						std::vector <llvm::Type const *> parameters;
						position = 0;
						llvm::BasicBlock * block (llvm::BasicBlock::Create (context.context));
						lambda_p_llvm::generation_context context_l (context.context, context.module, block);
						for (auto i = argument_list->nodes.begin (); i != argument_list->nodes.end (); ++i, ++position)
						{
							auto instance (*i);
							auto type (boost::dynamic_pointer_cast <lambda_p_llvm::type> (instance));
							if (type.get () != nullptr)
							{
								parameters.push_back (type->type_m);
								open_positions.push_back (position);
							}
							else
							{
								auto value (boost::dynamic_pointer_cast <lambda_p_llvm::fo_value> (instance));
								if (value.get () != nullptr)
								{
									llvm::Function * function (llvm::dyn_cast <llvm::Function> (value->value));
									if (function != nullptr)
									{
										nodes_l [position] = boost::shared_ptr <lambda_p_llvm::function_binder> (new lambda_p_llvm::function_binder (context_l, function));
									}
									else
									{
										nodes_l [position] = value;
									}
								}
								else
								{
									unexpected_binder_type_error (position, std::wstring (L"type or fo_value"), problems);
								}
							}
						}
						if (problems.errors.empty ())
						{
							llvm::Function * function (llvm::Function::Create (llvm::FunctionType::get (return_type->type_m, parameters, false), llvm::GlobalValue::ExternalLinkage));
							function->getBasicBlockList ().push_back (block);
							llvm::Function::arg_iterator i (function->arg_begin ());
							std::vector <size_t >::iterator j (open_positions.begin ());
							for (; i != function->arg_end (); ++i, ++j)
							{
								nodes_l [*j] = boost::shared_ptr <lambda_p_llvm::fo_value> (new lambda_p_llvm::fo_value (&(*i)));
							}
							lambda_p_kernel::bind_procedure procedure (routine->routine_m, nodes_l);
							procedure (problems);
							if (problems.errors.empty ())
							{
								auto return_value (boost::dynamic_pointer_cast <lambda_p_llvm::fo_value> (nodes_l [routine->routine_m->surface->parameters [0]]));
								if (return_value.get () != nullptr)
								{
									llvm::ReturnInst * ret (llvm::ReturnInst::Create (context_l.context, return_value->value));
									context_l.block->getInstList ().push_back (ret);
									context.module->getFunctionList ().push_back (function);
									boost::shared_ptr <lambda_p_llvm::fo_value> value (new lambda_p_llvm::fo_value (function));
									nodes [statement->association->results [0]] = value;
								}
								else
								{
									add_error (std::wstring (L"result value is not an llvm value"), problems);
								}
							}
						}
					}
					else
					{
						std::wstringstream message;
						message << L"Unexpected number of arguments, have: ";
						message << argument_list->nodes.size ();
						message << L" expect: ";
						message << routine->routine_m->surface->parameters.size ();
						add_error (message.str (), problems);
					}
				}
				else
				{
					unexpected_binder_type_error (2, std::wstring (L"group"), problems);
				}
			}
			else
			{
				unexpected_binder_type_error (1, std::wstring (L"type"), problems);
			}
		}
		else
		{
			unexpected_binder_type_error (0, std::wstring (L"routine"), problems);
		}
	}
}

std::wstring lambda_p_llvm::generator::binder_name ()
{
	return std::wstring (L"generator");
}
