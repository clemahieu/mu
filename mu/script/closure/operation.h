#pragma once

#include <mu/script_runtime/operation.h>

#include <boost/shared_ptr.hpp>

#include <vector>

namespace mu
{
	namespace script
	{
		namespace closure
		{
			class operation : public mu::script_runtime::operation
			{
			public:
				operation (size_t count_a, boost::shared_ptr <mu::script_runtime::operation> operation_a);
				operation (boost::shared_ptr <mu::script_runtime::operation> operation_a, std::vector <size_t> & open_a, std::vector <boost::shared_ptr <mu::core::node>> & closed_a);
				bool operator () (mu::script_runtime::context & context_a) override;
				std::wstring name () override;
				boost::shared_ptr <mu::script_runtime::operation> operation_m;
				std::vector <size_t> open;
				std::vector <boost::shared_ptr <mu::core::node>> closed;
			};
		}
	}
}
