#include "entry_routine.h"

#include <lambda_p/binder/routine_binder.h>
#include <lambda_p/binder/command_list.h>
#include <lambda_p/binder/structure.h>
#include <lambda_p/binder/data_to_string_binder.h>
#include <lambda_p_repl/repl_quit_binder.h>
#include <lambda_p_repl/hello_world_binder.h>
#include <lambda_p_repl/echo_binder.h>
#include <lambda_p/core/routine.h>
#include <lambda_p_repl/routine_input.h>

lambda_p_repl::entry_routine::entry_routine (::std::wistream & in_a, ::std::wostream & out_a)
	: in (in_a),
	out (out_a)
{
}

lambda_p_repl::entry_routine::entry_routine (::boost::shared_ptr < ::lambda_p_repl::repl_quit> quit_a, ::std::wistream & in_a, ::std::wostream & out_a)
	: quit (quit_a),
	in (in_a),
	out (out_a)
{
}

lambda_p_repl::entry_routine::~entry_routine (void)
{
}

void lambda_p_repl::entry_routine::operator () ()
{
	::lambda_p_repl::routine_input input;
	::std::wstring environment (L"main\n ;= environment\n;;\n");
	input (environment);
	out << environment;
	input (in, out);
	if (input.error ())
	{
		out << "Lexing error:\n";
		::std::wstring message;
		input.error_message (message);
		out << message;
		out << '\n';
	}
	else
	{
		out << L">>\n";
        ::std::wstringstream stream;
		::boost::shared_ptr < ::lambda_p::core::routine> routine ((*input.routines.routines)[0]);
        routine->validate (stream);
        ::std::wstring errors (stream.str ());
        if (errors.empty ())
        {
            use_routine (routine);
        }
        else
        {
            out << "Validation error:\n";
            out << errors;
            out << '\n';
        }
	}
}

void lambda_p_repl::entry_routine::use_routine (::boost::shared_ptr < ::lambda_p::core::routine> routine_a)
{	
	::lambda_p::binder::routine_binder routine_binder;
	::boost::shared_ptr < ::lambda_p::binder::structure> dereference_binder (new ::lambda_p::binder::structure);
	::boost::shared_ptr < ::lambda_p::binder::command_list> commands (new ::lambda_p::binder::command_list);
	::boost::shared_ptr < ::lambda_p_repl::hello_world_binder> hello_binder (new ::lambda_p_repl::hello_world_binder (commands));
	::boost::shared_ptr < ::lambda_p_repl::echo_binder> echo_binder (new ::lambda_p_repl::echo_binder (commands));
	::boost::shared_ptr < ::lambda_p::binder::data_to_string_binder> d2s_binder (new ::lambda_p::binder::data_to_string_binder);
	::std::wstring echo_name (L"echo");
	::std::wstring hello_name (L"hello");
	::std::wstring d2s_name (L"d2s");
	dereference_binder->nodes [echo_name] = echo_binder;
	dereference_binder->nodes [hello_name] = hello_binder;
	dereference_binder->nodes [d2s_name] = d2s_binder;
	routine_binder.instances [environment_node (routine_a)] = dereference_binder;
	if (quit.get () != NULL)
	{
		::boost::shared_ptr < ::lambda_p_repl::repl_quit_binder> binder (new ::lambda_p_repl::repl_quit_binder (commands, quit));
		::std::wstring quit_name (L"quit");
		dereference_binder->nodes [quit_name] = binder;
	}
	routine_binder (routine_a);
	if (routine_binder.error ())
	{
		::std::wcout << "Binding error:\n";
		::std::wstring message;
		routine_binder.error_message (message);
		::std::wcout << message;
		::std::wcout << '\n';
	}
	else
	{
		commands->operator() ();
	}
}

::lambda_p::core::node * lambda_p_repl::entry_routine::environment_node (::boost::shared_ptr < ::lambda_p::core::routine> routine)
{
	::lambda_p::core::node * result (routine->statements [0]->arguments [0]);
	return result;
}