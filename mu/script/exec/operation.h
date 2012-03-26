#pragma once

#include <mu/script/operation.h>

#include <map>

#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace io
	{
		namespace analyzer
		{
			namespace extensions
			{
				class extensions;
				class extension;
			}
		}
	}
	namespace script
	{
		namespace exec
		{
			class operation : public mu::script::operation
			{
			public:
				operation (boost::shared_ptr <mu::io::analyzer::extensions::extensions> extensions_a);
				boost::shared_ptr <mu::io::analyzer::extensions::extensions> extensions;
				bool operator () (mu::script::context & context_a) override;
				std::wstring name () override;
			};
		}
	}
}
