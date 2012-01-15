#pragma once

#include <boost/shared_ptr.hpp>

#include <map>

namespace lambda_p_io
{
	namespace analyzer
	{
		class extension;
	}
}
namespace lambda_p_repl
{
	class api
	{
	public:
		std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extension>> operator () ();
	};
}

