#pragma once

#include <lambda_p_script/fixed.h>

#include <vector>
#include <map>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class routine;
}
namespace lambda_p_script
{
	class routine;
	namespace cluster
	{
		class node : public lambda_p_script::fixed
		{
		public:
			node ();
			node (std::vector <boost::shared_ptr <lambda_p_script::routine>> routines_a, std::map <boost::shared_ptr <lambda_p::routine>, boost::shared_ptr <lambda_p::node>> mapping_a);
			node (std::map <std::wstring, boost::shared_ptr <lambda_p::routine>> names_a, std::vector <boost::shared_ptr <lambda_p_script::routine>> routines_a, std::map <boost::shared_ptr <lambda_p::routine>, boost::shared_ptr <lambda_p::node>> mapping_a);
			void operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results) override;
			size_t count () override;
			void remap (std::map <boost::shared_ptr <lambda_p::node>, boost::shared_ptr <lambda_p::node>> & remap_a);
			std::map <std::wstring, boost::shared_ptr <lambda_p::routine>> names;
			std::map <boost::shared_ptr <lambda_p::routine>, boost::shared_ptr <lambda_p::node>> mapping;
			std::vector <boost::shared_ptr <lambda_p_script::routine>> routines;
		};
	}
}

