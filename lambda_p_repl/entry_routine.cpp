#include "entry_routine.h"

#include <lambda_p_repl/entry_input.h>
#include <lambda_p_llvm/context.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p_repl/api.h>
#include <lambda_p_repl/exec_binder.h>
#include <lambda_p_kernel/package.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p_kernel/apply.h>
#include <lambda_p/errors/error.h>

#include <llvm/Module.h>

#include <sstream>

lambda_p_repl::entry_routine::entry_routine (lambda_p_repl::repl * repl_a, boost::shared_ptr < lambda_p::lexer::character_stream> in_a, std::wostream & out_a)
: repl (repl_a),
in (in_a),
out (out_a)
{
}

lambda_p_repl::entry_routine::entry_routine (boost::shared_ptr < lambda_p::lexer::character_stream> in_a, std::wostream & out_a)
: in (in_a),
out (out_a),
repl (nullptr)
{
}

void lambda_p_repl::entry_routine::operator () ()
{
	lambda_p_repl::api api;
	boost::shared_ptr <lambda_p::binder::node> environment (api ());
	std::vector <std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>>> injected_parameters;
	injected_parameters.push_back (std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>> (std::wstring (L"environment"), environment));	
	boost::shared_ptr <lambda_p_repl::exec_binder> exec_binder (new lambda_p_repl::exec_binder);
	exec_binder->set (environment, exec_binder);
	injected_parameters.push_back (std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>> (std::wstring (L"exec"), exec_binder));
	lambda_p_repl::entry_input input (environment, exec_binder);
    input (in, out);
    if (input.routine.get () != nullptr)
    {
		lambda_p::errors::error_list problems;
		lambda_p_kernel::apply apply;
		lambda_p::binder::list nodes;
		lambda_p::binder::list declarations;
		apply.core (input.routine, nodes, problems, declarations);
		if (!problems.errors.empty ())
		{
			std::wcout << "Binding error:\n";
			std::wstringstream stream;
			for (auto i = problems.errors.begin (); i != problems.errors.end (); ++i)
			{
				(*i)->string (stream);
				stream << L'\n';
			}
			stream.seekg (0);
			std::wstring error (stream.str ());
			std::wcout << error;
			std::wcout << '\n';
		}
    }
}