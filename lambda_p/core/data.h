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
			data (::boost::shared_array <uint8_t> item_a, size_t size_a, ::lambda_p::core::routine * routine_a, size_t self_statement_a, size_t self_argument_a);
			~data (void);
            void validate (::std::iostream & problems) const;
            ::boost::shared_array <uint8_t> item () const;
			node_id node_type () const;
			::std::wstring node_type_name () const;
		private:
			::boost::shared_array <uint8_t> item_m;
            size_t size;
			::lambda_p::core::routine * routine;
			size_t self_statement;
			size_t self_argument;
		};
	}
}

