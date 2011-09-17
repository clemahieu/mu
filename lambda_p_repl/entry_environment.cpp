//
//  entry_environment.cpp
//  lambda_p_repl
//
//  Created by Colin LeMahieu on 9/16/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <lambda_p_repl/entry_environment.h>

#include <lambda_p/binder/routine_binder.h>
#include <lambda_p/binder/command_list.h>
#include <lambda_p/binder/structure.h>
#include <lambda_p/binder/data_to_string_binder.h>
#include <lambda_p_repl/repl_quit_binder.h>
#include <lambda_p_repl/hello_world_binder.h>
#include <lambda_p_repl/echo_binder.h>
#include <lambda_p/core/routine.h>
#include <lambda_p_repl/stream_read_entry_routine_binder.h>

lambda_p_repl::entry_environment::entry_environment (::boost::shared_ptr < ::lambda_p_repl::repl_quit> quit_binder_a)
: quit (quit_binder_a)
{    
}

lambda_p_repl::entry_environment::entry_environment ()
{
}

void lambda_p_repl::entry_environment::operator () (::boost::shared_ptr < ::lambda_p::core::routine> routine_a)
{	
	::lambda_p::binder::routine_binder routine_binder;
	::boost::shared_ptr < ::lambda_p::binder::structure> dereference_binder (new ::lambda_p::binder::structure);
	::boost::shared_ptr < ::lambda_p::binder::command_list> commands (new ::lambda_p::binder::command_list);
	::boost::shared_ptr < ::lambda_p_repl::hello_world_binder> hello_binder (new ::lambda_p_repl::hello_world_binder (commands));
	::boost::shared_ptr < ::lambda_p_repl::echo_binder> echo_binder (new ::lambda_p_repl::echo_binder (commands));
	::boost::shared_ptr < ::lambda_p::binder::data_to_string_binder> d2s_binder (new ::lambda_p::binder::data_to_string_binder);
	::boost::shared_ptr < ::lambda_p_repl::stream_read_entry_routine_binder> read_binder (new ::lambda_p_repl::stream_read_entry_routine_binder);
	::std::wstring echo_name (L"echo");
	::std::wstring hello_name (L"hello");
	::std::wstring d2s_name (L"d2s");
	::std::wstring read_name (L"read");
	dereference_binder->nodes [echo_name] = echo_binder;
	dereference_binder->nodes [hello_name] = hello_binder;
	dereference_binder->nodes [d2s_name] = d2s_binder;
	dereference_binder->nodes [read_name] = read_binder;
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

::lambda_p::core::node * lambda_p_repl::entry_environment::environment_node (::boost::shared_ptr < ::lambda_p::core::routine> routine)
{
	::lambda_p::core::node * result (routine->statements [0]->arguments [0]);
	return result;
}