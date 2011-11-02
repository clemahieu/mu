#pragma once

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace core
	{
		class routine;
	}
	namespace lexer
	{
		class character_stream;
	}
}
namespace lambda_p_repl
{
	class repl;
	class entry_routine
	{
	public:
		entry_routine (lambda_p_repl::repl * repl_a, boost::shared_ptr <lambda_p::lexer::character_stream> in_a, std::wostream & out_a);
        entry_routine (boost::shared_ptr <lambda_p::lexer::character_stream> in_a, std::wostream & out_a);
		void operator () ();
	private:
		boost::shared_ptr <lambda_p::lexer::character_stream> in;
		std::wostream & out;
        lambda_p_repl::repl * repl;
	};
}

