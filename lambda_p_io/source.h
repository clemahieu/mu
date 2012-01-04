#pragma once

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

namespace lambda_p_io
{
	namespace lexer
	{
		class character_stream;
	}
	class source
	{
	public:
		source (boost::function <void (wchar_t char_a)> target_a);
		void operator () ();
		void operator () (wchar_t char_a);
		void operator () (std::wstring & string);
		void operator () (wchar_t const * string);
		void operator () (boost::shared_ptr <lambda_p_io::lexer::character_stream> source);
		void operator << (boost::shared_ptr <lambda_p_io::lexer::character_stream> source);
		boost::function <void (wchar_t char_a)> target;
	};
}

