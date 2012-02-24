#pragma once

#include <mu/script/operation.h>

#include <map>

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
				void perform (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results) override;
				std::wstring name () override;
			};
		}
	}
}
