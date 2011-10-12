#pragma once

namespace lambda_p
{
	namespace parser
	{
		class association_target
		{
		public:
			virtual size_t * sink_result (size_t declaration) = 0;
			virtual size_t * sink_argument (size_t argument) = 0;
		};
	}
}

