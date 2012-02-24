#pragma once

#include <core/visitor.h>

#include <set>
#include <vector>

#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace core
	{
		class reference;
		class node;
		class expression;
		class order : public mu::core::visitor
		{
		public:
			order (boost::shared_ptr <mu::core::expression> expression_a);
			void operator () (boost::shared_ptr <mu::core::expression> expression_a);
			void operator () (mu::core::expression * expression_a) override;
			void operator () (mu::core::parameters * parameters_a) override;
			void operator () (mu::core::reference * reference_a) override;
			void operator () (mu::core::node * node_a) override;
			void operator () (mu::core::routine * routine_a) override;
			boost::shared_ptr <mu::core::node> current;
			std::set <boost::shared_ptr <mu::core::expression>> already;
			std::vector <boost::shared_ptr <mu::core::expression>> expressions;
		};
	}
}
