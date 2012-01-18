#pragma once

#include <map>

#include <boost/shared_ptr.hpp>

namespace lambda_p_io
{
	namespace analyzer
	{
		namespace extensions
		{
			class extension;
			class extensions
			{
			public:
				extensions ();
				extensions (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>> extensions_a);
				std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>> extensions_m;
			};
		}
	}
}

