#pragma once

#include <boost/shared_ptr.hpp>

#include <lambda_p_kernel/bind_procedure.h>

#include <iostream>

namespace lambda_p
{
	namespace core
	{
		class routine;
	}
}
namespace lambda_p_repl
{
	class repl;
	class character_stream;
	class entry_routine
	{
	public:
		entry_routine (::lambda_p_repl::repl * repl_a, ::boost::shared_ptr < ::lambda_p_repl::character_stream> in_a, ::std::wostream & out_a);
        entry_routine (::boost::shared_ptr < ::lambda_p_repl::character_stream> in_a, ::std::wostream & out_a);
		~entry_routine (void);
		void operator () ();
	private:
		::boost::shared_ptr < ::lambda_p_repl::character_stream> in;
		::std::wostream & out;
        ::lambda_p_repl::repl * repl;
	};
}

