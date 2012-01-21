#pragma once

#include <boost/shared_ptr.hpp>

#include <map>

namespace lambda_p_io
{
	namespace analyzer
	{
		namespace extensions
		{
			class extension;
		}
	}
}
namespace lambda_p_llvm_wrapper
{
	class api
	{
	public:
		api ();
		std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>> extensions;
	};
}

