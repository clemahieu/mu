#pragma once

#include <lambda_p_script/fixed.h>

namespace lambda_p
{
	class routine;
}
namespace lambda_p_io
{
	namespace analyzer
	{
		namespace extensions
		{
			class extensions;
		}
	}
}
namespace lambda_p_llvm
{
	namespace analyzer
	{
		class operation : public lambda_p_script::fixed
		{
		public:
			operation ();
			void operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results) override;
			size_t count () override;
			void add (std::vector <boost::shared_ptr <lambda_p::node>> & results, boost::shared_ptr <lambda_p::routine> routine_a);
			boost::shared_ptr <lambda_p_io::analyzer::extensions::extensions> extensions;
		};
	}
}

