#include "call.h"

#include <mu/llvm_/value/node.h>
#include <mu/llvm_/type/node.h>
#include <mu/script/values/operation.h>
#include <mu/llvm_/pointer_type/node.h>
#include <mu/core/errors/error_target.h>
#include <mu/llvm_/function_type/node.h>
#include <mu/llvm_/instruction/node.h>
#include <mu/llvm_/type/build.h>
#include <mu/llvm_/context/node.h>
#include <mu/llvm_/void_type/node.h>

#include <llvm/DerivedTypes.h>
#include <llvm/Instructions.h>
#include <llvm/Support/raw_ostream.h>

#include <boost/make_shared.hpp>

#include <sstream>

void mu::llvm_::instructions::call::perform (mu::script::context & context_a)
{
	if (context_a.parameters.size () > 0)
	{
		auto one (boost::dynamic_pointer_cast <mu::llvm_::value::node> (context_a.parameters [0]));
		if (one.get () != nullptr)
		{
			auto pointer_type (boost::dynamic_pointer_cast <mu::llvm_::pointer_type::node> (one->type));
			if (pointer_type.get () != nullptr)
			{
				auto function_type (boost::dynamic_pointer_cast <mu::llvm_::function_type::node> (pointer_type->element));
				if (function_type.get () != nullptr)
				{
					auto flat_type (function_type->function_type ());
					if (flat_type->getNumParams () == context_a.parameters.size () - 1)
					{
						std::vector <llvm::Value *> arguments;
						size_t position (0);
						for (auto i (context_a.parameters.begin () + 1), j (context_a.parameters.end () + 0); i != j && !(*context_a.errors) (); ++i, ++position)
						{
							auto value (boost::dynamic_pointer_cast <mu::llvm_::value::node> (*i));
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
									(*context_a.errors) (message.str ());
								}
							}
						}
						if (! (*context_a.errors) ())
						{
							context_a.results.push_back (boost::make_shared <mu::llvm_::instruction::node> (llvm::CallInst::Create (one->value (), arguments), function_type->output));
						}
					}
					else
					{
						std::wstringstream message;
						message << L"Number of actual arguments: ";
						message << context_a.parameters.size () - 1;
						message << L" does not match number of formal parameters: ";
						message << flat_type->getNumParams ();
						(*context_a.errors) (message.str ());
					}
				}
				else
				{
					(*context_a.errors) (L"Can only call to a pointer to a function type");
				}
			}
			else
			{
				(*context_a.errors) (L"Can only call to a pointer type");
			}
		}
		else
		{
			invalid_type (context_a.errors, context_a.parameters [0], 0);
		}
	}
	else
	{
		(*context_a.errors) (L"Call instruction must have at least one argument");
	}
}