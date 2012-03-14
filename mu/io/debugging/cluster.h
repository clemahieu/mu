#pragma once

#include <mu/io/debugging/context.h>
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
				mu::io::debugging::context context;
				mu::io::debugging::hash hash;
				std::map <std::wstring, boost::shared_ptr <mu::io::debugging::routine>> names;
				std::vector <boost::shared_ptr <mu::io::debugging::routine>> routines;
			};
		}
	}
}