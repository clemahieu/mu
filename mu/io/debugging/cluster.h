#pragma once

#include <mu/core/context.h>
#include <mu/io/debugging/hash.h>

#include <vector>
#include <map>

#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace core
	{
		class routine;
	}
	namespace io
	{
		namespace debugging
		{
			class routine;
			class cluster
			{
			public:
				mu::core::context context;
				mu::io::debugging::hash hash;
				std::vector <mu::io::debugging::routine *> routines;
				std::map <boost::shared_ptr <mu::core::routine>, mu::io::debugging::routine *> mapping;
			};
		}
	}
}