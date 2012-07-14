#include <mu/llvm_/instructions/call.h>

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
#include <mu/script/check.h>

#include <llvm/DerivedTypes.h>
#include <llvm/Instructions.h>
#include <llvm/Support/raw_ostream.h>

#include <boost/make_shared.hpp>

#include <sstream>

#include <gc_cpp.h>

bool mu::llvm_::instructions::call::operator () (mu::script::context & context_a)
{
	bool result (true);
	if (context_a.parameters_size () > 0)
	{
		auto one (dynamic_cast <mu::llvm_::value::node *> (context_a.parameters (0)));
		if (one != nullptr)
		{
			auto pointer_type (dynamic_cast <mu::llvm_::pointer_type::node *> (one->type));
			if (pointer_type != nullptr)
			{
				auto function_type (dynamic_cast <mu::llvm_::function_type::node *> (pointer_type->element));
				if (function_type != nullptr)
				{
					auto flat_type (function_type->function_type ());
					if (flat_type->getNumParams () == context_a.parameters_size () - 1)
					{
						std::vector <llvm::Value *> arguments;
						size_t position (0);
						for (auto i (context_a.parameters_begin () + 1), j (context_a.parameters_end () + 0); i != j && !context_a (); ++i, ++position)
						{
							auto value (dynamic_cast <mu::llvm_::value::node *> (*i));
							if (value != nullptr)
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
									context_a.errors (message.str ());
									result = false;
								}
							}
						}
						if (result)
						{
							context_a.push (new (GC) mu::llvm_::instruction::node (llvm::CallInst::Create (one->value (), arguments), function_type->output));
						}
					}
					else
					{
						std::wstringstream message;
						message << L"Number of actual arguments: ";
						message << context_a.parameters_size () - 1;
						message << L" does not match number of formal parameters: ";
						message << flat_type->getNumParams ();
						context_a.errors (message.str ());
						result = false;
					}
				}
				else
				{
					context_a.errors (L"Can only call to a pointer to a function type");
					result = false;
				}
			}
			else
			{
				context_a.errors (L"Can only call to a pointer type");
				result = false;
			}
		}
		else
		{
			mu::script::invalid_type (context_a, context_a.parameters (0), typeid (mu::llvm_::pointer_type::node), 0);
		}
	}
	else
	{
		context_a.errors (L"Call instruction must have at least one argument");
		result = false;
	}
	return result;
}