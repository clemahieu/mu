#pragma once

#include <mu/io/debugging/context.h>

#include <vector>

#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace io
	{
		namespace debugging
		{
			class routine;
			class node
			{
			public:
				virtual ~node ();
				node ();
				node (mu::io::debugging::context context_aa);
				mu::io::debugging::context context;
			};
		}
	}
}