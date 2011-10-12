#include "routine_application.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/core/routine.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p_llvm/literal_value.h>

#include <llvm/Function.h>
#include <llvm/DerivedTypes.h>
#include <llvm/GlobalValue.h>
#include <llvm/Argument.h>

lambda_p_llvm::routine_application::routine_application (::lambda_p::core::routine * routine_a)
	: routine (routine_a),
	indirection (routine->surface->results.size (), ~0),
	arguments (routine->surface->results.size (), NULL)
{
	for (size_t i = 0; i < routine->surface->results.size (); ++i)
	{
		indirection [i] = i;
	}
}

void lambda_p_llvm::routine_application::apply (::std::vector < ::lambda_p_llvm::value *> arguments_a)
{
	size_t argument_count (arguments_a.size ());
	assert (argument_count <= indirection.size ());
	for (size_t i = argument_count - 1; i < argument_count; --i)
	{
		::lambda_p_llvm::value * value (arguments_a [i]);
		if (value != NULL)
		{
			arguments [indirection [i]] = value;
			erase (i);
		}
	}
}

void lambda_p_llvm::routine_application::erase (size_t i_a)
{
	for (size_t i = i_a; i < indirection.size () - 1; ++i)
	{
		indirection [i] = indirection [i + 1];
	}
	indirection.resize (indirection.size () - 1);
}

::llvm::Function * lambda_p_llvm::routine_application::generate (::lambda_p_llvm::generation_context & context, ::std::vector < ::llvm::Type const *> open_types, ::std::vector < ::llvm::Type const *> results, ::std::vector < ::lambda_p::errors::error *> & problems)
{
	assert (open_types.size () == indirection.size ());
	::llvm::Type const * result_type;
	if (results.size () == 0)
	{
		result_type = ::llvm::Type::getVoidTy (context.context);
	}
	else if (results.size () == 1)
	{
		result_type = results [0];
	}
	else
	{
		result_type = ::llvm::StructType::get (context.context, results);
	}
	::llvm::Function * result (::llvm::Function::Create (::llvm::FunctionType::get (result_type, open_types, false), ::llvm::GlobalValue::ExternalLinkage));
	::llvm::Function::arg_iterator parameters (result->arg_begin ());
	::std::vector < size_t>::iterator open_parameters (indirection.begin ());
	while (parameters != result->arg_end ())
	{
		::lambda_p_llvm::literal_value * value (new ::lambda_p_llvm::literal_value (&(*parameters)));
		arguments [indirection [*open_parameters]] = value;
		++parameters;
		++open_parameters;
	}
	for (::std::vector < ::lambda_p::core::statement *>::iterator i = routine->statements.begin (); i != routine->statements.end (); ++i)
	{
		::lambda_p::core::statement * current (*i);
	}
	return result;
}