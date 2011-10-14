#pragma once

namespace lambda_p
{
	namespace parser
	{
		class association_target
		{
		public:
			virtual void sink_result (size_t * & declaration) = 0;
			virtual void sink_argument (size_t * & argument) = 0;
		};
	}
}

