#pragma once

namespace mu
{
	namespace core
	{
		class reference;
		class node;
		class expression;
		class parameters;
		class routine;
		class visitor
		{
		public:
			virtual void operator () (mu::core::expression * expression_a) = 0;
			virtual void operator () (mu::core::parameters * parameters_a) = 0;
			virtual void operator () (mu::core::reference * reference_a) = 0;
			virtual void operator () (mu::core::node * node_a) = 0;
			virtual void operator () (mu::core::routine * routine_a) = 0;
		};
	}
}
