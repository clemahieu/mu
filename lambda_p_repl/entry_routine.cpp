#include "entry_routine.h"

#include <lambda_p_repl/routine_input.h>
#include <lambda_p_repl/entry_input.h>
#include <lambda_p_repl/entry_environment.h>
#include <lambda_p_llvm/context.h>
#include <lambda_p_llvm/generation_context.h>

#include <llvm/Module.h>

lambda_p_repl::entry_routine::entry_routine (lambda_p_repl::repl * repl_a, boost::shared_ptr < lambda_p_repl::character_stream> in_a, std::wostream & out_a)
: repl (repl_a),
in (in_a),
out (out_a)
{
}

lambda_p_repl::entry_routine::entry_routine (boost::shared_ptr < lambda_p_repl::character_stream> in_a, std::wostream & out_a)
: in (in_a),
out (out_a),
repl (nullptr)
{
}

lambda_p_repl::entry_routine::~entry_routine (void)
{
}

void lambda_p_repl::entry_routine::operator () ()
{
    lambda_p_repl::entry_input input;
    input (in, out);
    if (input.routine.get () != nullptr)
    {
		boost::shared_ptr <lambda_p_llvm::context> context_instance (new lambda_p_llvm::context);
		std::string module_name_string ("llvm_repl");
		llvm::StringRef module_name (module_name_string);
		llvm::Module * module (new llvm::Module (module_name, context_instance->context_m));
		boost::shared_ptr <lambda_p_llvm::generation_context> context (new lambda_p_llvm::generation_context (context_instance->context_m, module, nullptr));
        lambda_p_repl::entry_environment environment (repl, context_instance, context, input.routine);
		environment.run ();
    }
}