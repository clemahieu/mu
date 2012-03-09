#pragma once

#include <mu/script/operation.h>

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace script
	{
		class routine;
	}
	namespace script_io
	{
		class synthesizer : public mu::script::operation
		{
		public:
			void operator () (mu::script::context & context_a) override;
			std::wstring name () override;
		};
	}
}
