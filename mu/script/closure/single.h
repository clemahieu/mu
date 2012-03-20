#pragma once

#include <mu/script/operation.h>

#include <boost/shared_ptr.hpp>

#include <vector>

namespace mu
{
    namespace core
    {
        class node;
    }
	namespace script
	{
		namespace closure
		{
			class single : public mu::script::operation
			{
			public:
				single (boost::shared_ptr <mu::script::operation> operation_a);
				single (std::vector <boost::shared_ptr <mu::core::node>> & closed_a, boost::shared_ptr <mu::script::operation> operation_a);
				bool operator () (mu::script::context & context_a) override;
				std::wstring name () override;
				boost::shared_ptr <mu::script::operation> operation_m;
				std::vector <boost::shared_ptr <mu::core::node>> closed;
			};
		}
	}
}
