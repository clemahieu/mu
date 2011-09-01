#pragma once

#include <string>

#include <lambda_p/core/node.h>

#include <boost/cstdint.hpp>
#include <boost/shared_array.hpp>

namespace lambda_p
{
	namespace core
	{
		class routine;
		class data : public node
		{
		public:
			data (::boost::shared_array <uint8_t> item_a, size_t size_a, ::lambda_p::core::routine & routine_a, size_t statement_a, size_t index_a);
			~data (void);
            void validate (::std::iostream & problems);
		private:
			::boost::shared_array <uint8_t> item;
            size_t size;
			::lambda_p::core::routine & routine;
			size_t statement;
			size_t index;
		};
	}
}

