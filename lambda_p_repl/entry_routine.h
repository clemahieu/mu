#pragma once

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

#include <lambda_p/binder/bind_procedure.h>

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
	class entry_routine
	{
	public:
		entry_routine (::lambda_p_repl::repl * repl_a, ::boost::function <wchar_t ()> in_a, ::std::wostream & out_a);
        entry_routine (::boost::function <wchar_t ()> in_a, ::std::wostream & out_a);
		~entry_routine (void);
		void operator () ();
	private:
		::boost::function <wchar_t ()> in;
		::std::wostream & out;
        ::lambda_p_repl::repl * repl;
	};
}

