#pragma once

#include <core/context.h>
#include <core/node.h>

#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace core
	{
		class expression;
		class routine : public mu::core::node
		{
		public:
			routine (mu::core::context context_a);
			routine (boost::shared_ptr <mu::core::expression> body_a);
			void operator () (mu::core::visitor * visitor_a) override;
			std::wstring name () override;
			mu::core::context context;
			boost::shared_ptr <mu::core::expression> body;
		};
	}
}
