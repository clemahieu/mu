#pragma once

#include <boost/shared_ptr.hpp>

#include <map>

namespace mu
{
	namespace core
	{
		class node;
	}
	namespace io
	{
		namespace debugging
		{
			class node;
			class mapping
			{
				std::map <boost::shared_ptr <mu::core::node>, boost::shared_ptr <mu::io::debugging::node>> nodes;
			};
		}
	}
}