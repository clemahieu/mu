#pragma once

#include <string>

#include <lambda_p/core/node.h>

#include <boost/shared_array.hpp>

namespace lambda_p
{
	namespace core
	{
		class data : public node
		{
		public:
			data(void);
			~data(void);
			::boost::shared_array <uint8_t> item;
            size_t size;
		};
	}
}

