#pragma once

#include <vector>

#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace core
	{
		class expression;
	}
	namespace script
	{
		namespace topology
		{
			class node
			{
			public:				
				std::vector <boost::shared_ptr <mu::core::expression>> expressions;
			};
		}
	}
}