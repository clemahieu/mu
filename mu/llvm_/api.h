#pragma once

#include <boost/shared_ptr.hpp>

#include <map>

namespace mu
{
	namespace io
	{
		namespace analyzer
		{
			namespace extensions
			{
				class extension;
			}
		}
	}
	namespace llvm_
	{
		class api
		{
		public:
			api ();
			std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>> extensions;
		};
	}
}

