#pragma once

#include <core/node.h>
#include <lambda_p_io/analyzer/analyzer.h>

namespace lambda_p_script
{
	namespace analyzer
	{
		class node : public mu::core::node
		{
		public:
			lambda_p_io::analyzer::analyzer analyzer;
		};
	}
}

