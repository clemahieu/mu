#pragma once

#include <mu/core/node.h>
#include <mu/io/analyzer/analyzer.h>

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

