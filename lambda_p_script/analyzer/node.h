#pragma once

#include <lambda_p/node.h>
#include <lambda_p_io/analyzer/analyzer.h>

namespace lambda_p_script
{
	namespace analyzer
	{
		class node : public lambda_p::node
		{
		public:
			lambda_p_io::analyzer::analyzer analyzer;
		};
	}
}

