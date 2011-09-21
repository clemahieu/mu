#pragma once

#include <boost/shared_ptr.hpp>

#include <lambda_p/binder/routine_binder.h>

#include <iostream>

namespace lambda_p
{
	namespace core
	{
		class routine;
		class node;
	}
	namespace binder
	{
		class structure;
	}
}
namespace lambda_p_repl
{
	class repl;
	class entry_routine
	{
	public:
		entry_routine (::lambda_p_repl::repl * repl_a, ::std::wistream & in_a, ::std::wostream & out_a);
        entry_routine (::std::wistream & in_a, ::std::wostream & out_a);
		~entry_routine (void);
		void operator () ();
	private:
		::std::wistream & in;
		::std::wostream & out;
        ::lambda_p_repl::repl * repl;
	};
}

