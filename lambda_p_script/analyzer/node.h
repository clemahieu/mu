#pragma once

#include <core/node.h>
#include <io/analyzer/analyzer.h>

namespace lambda_p_script
{
	namespace analyzer
	{
		class node : public mu::core::node
		{
		public:
			mu::io::analyzer::analyzer analyzer;
		};
	}
}

