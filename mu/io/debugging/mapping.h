#pragma once

#include <mu/core/node.h>

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
			class stream;
			class mapping : public mu::core::node
			{
			public:
				mapping (boost::shared_ptr <mu::io::debugging::stream> stream_a);
				boost::shared_ptr <mu::io::debugging::stream> stream;
				std::map <boost::shared_ptr <mu::core::node>, boost::shared_ptr <mu::io::debugging::node>> nodes;
			};
		}
	}
}