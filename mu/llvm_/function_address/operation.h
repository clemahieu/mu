#pragma once

#include <mu/script/fixed.h>

#include <map>

namespace mu
{
	namespace llvm_
	{
		namespace function
		{
			class node;
		}
		namespace function_address
		{
			class operation : public mu::script::fixed
			{
			public:
				void operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results) override;
				size_t count () override;
				std::map <std::wstring, boost::shared_ptr <mu::llvm_::function::node>> remap;
			};
		}
	}
}

