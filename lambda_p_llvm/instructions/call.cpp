#include "call.h"

#include <lambda_p_llvm/value/node.h>
#include <lambda_p_llvm/type/node.h>
#include <mu/script/values/operation.h>
#include <lambda_p_llvm/pointer_type/node.h>
#include <mu/core/errors/error_target.h>
#include <lambda_p_llvm/function_type/node.h>
#include <lambda_p_llvm/instruction/node.h>
#include <lambda_p_llvm/type/build.h>
#include <lambda_p_llvm/context/node.h>
#include <lambda_p_llvm/void_type/node.h>

#include <llvm/DerivedTypes.h>
#include <llvm/Instructions.h>
#include <llvm/Support/raw_ostream.h>

#include <boost/make_shared.hpp>

#include <sstream>

void lambda_p_llvm::instructions::call::perform (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	if (parameters.size () > 0)
	{
		auto one (boost::dynamic_pointer_cast <lambda_p_llvm::value::node> (parameters [0]));
		if (one.get () != nullptr)
		{
			auto pointer_type (boost::dynamic_pointer_cast <lambda_p_llvm::pointer_type::node> (one->type));
			if (pointer_type.get () != nullptr)
			{
				auto function_type (boost::dynamic_pointer_cast <lambda_p_llvm::function_type::node> (pointer_type->element));
				if (function_type.get () != nullptr)
				{
					auto flat_type (function_type->function_type ());
					if (flat_type->getNumParams () == parameters.size () - 1)
					{
						std::vector <llvm::Value *> arguments;
						size_t position (0);
						for (auto i (parameters.begin () + 1), j (parameters.end () + 0); i != j && !(*errors_a) (); ++i, ++position)
						{
							auto value (boost::dynamic_pointer_cast <lambda_p_llvm::value::node> (*i));
							if (value.get () != nullptr)
							{
								auto expected (flat_type->getParamType (position));
								auto actual (value->type->type ());
								if (actual == expected)
								{
									arguments.push_back (value->value ());
								}
								else
								{
									std::string expected_str;
									std::string actual_str;
									{
										llvm::raw_string_ostream expected_stream (expected_str);
										expected->print (expected_stream);
										llvm::raw_string_ostream actual_stream (actual_str);
										actual->print (actual_stream);
									}
									std::wstringstream message;
									message << L"Expected type: ";
									message << std::wstring (expected_str.begin (), expected_str.end ());
									message << L" does match actual type: ";
									message << std::wstring (actual_str.begin (), actual_str.end ());
									(*errors_a) (message.str ());
								}
							}
						}
						if (! (*errors_a) ())
						{
							results.push_back (boost::make_shared <lambda_p_llvm::instruction::node> (llvm::CallInst::Create (one->value (), arguments), function_type->output));
						}
					}
					else
					{
						std::wstringstream message;
						message << L"Number of actual arguments: ";
						message << parameters.size () - 1;
						message << L" does not match number of formal parameters: ";
						message << flat_type->getNumParams ();
						(*errors_a) (message.str ());
					}
				}
				else
				{
					(*errors_a) (L"Can only call to a pointer to a function type");
				}
			}
			else
			{
				(*errors_a) (L"Can only call to a pointer type");
			}
		}
		else
		{
			invalid_type (errors_a, parameters [0], 0);
		}
	}
	else
	{
		(*errors_a) (L"Call instruction must have at least one argument");
	}
}