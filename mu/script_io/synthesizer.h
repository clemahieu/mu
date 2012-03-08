#pragma once

#include <mu/script/fixed.h>

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
		class synthesizer : public mu::script::fixed
		{
		public:
			void operator () (mu::script::context & context_a) override;
			size_t count () override;
			std::wstring name () override;
		};
	}
}
