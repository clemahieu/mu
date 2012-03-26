#pragma once

#include <boost/noncopyable.hpp>

namespace mu
{
	namespace script
	{
		class context;
		class frame : boost::noncopyable
		{
		public:
			frame (mu::script::context & context_a);
			~frame ();
			mu::script::context & context;
		};
	}
}