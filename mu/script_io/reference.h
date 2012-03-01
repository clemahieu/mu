#pragma once

#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace core
	{
		class node;
		class routine;
	}
	namespace script_io
	{
		class reference
		{
		public:
			virtual boost::shared_ptr <mu::core::node> operator () (boost::shared_ptr <mu::core::routine> routine_a) = 0;
		};
	}
}

