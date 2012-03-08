#pragma once

#include <mu/script/operation.h>

namespace mu
{
	namespace script
	{
		class fixed : public mu::script::operation
		{
		public:
			void perform (mu::script::context & context_a) override;
			virtual void operator () (mu::script::context & context_a) = 0;
			virtual size_t count () = 0;
		};
	}
}
