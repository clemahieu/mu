#pragma once

#include <boost/shared_ptr.hpp>

#include <lambda_p/parser/reference_identifiers.h>

namespace lambda_p
{
	namespace core
	{
		class reference;
	}
	namespace parser
	{
		class production_target
		{
		public:
			virtual void sink_reference (::lambda_p::parser::reference_identifiers reference);
		};
	}
}

