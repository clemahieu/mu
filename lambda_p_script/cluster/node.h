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
	class remapping;
	class routine;
	namespace cluster
	{
		class node : public lambda_p_script::fixed
		{
		public:
			node ();
			node (std::vector <boost::shared_ptr <lambda_p_script::routine>> routines_a, boost::shared_ptr <lambda_p_script::remapping> remapping_a);
			node (std::map <std::wstring, size_t> names_a, std::vector <boost::shared_ptr <lambda_p_script::routine>> routines_a, boost::shared_ptr <lambda_p_script::remapping> remapping_a);
			void operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results) override;
			size_t count () override;
			std::map <std::wstring, size_t> names;		
			boost::shared_ptr <lambda_p_script::remapping> remapping;
			std::vector <boost::shared_ptr <lambda_p_script::routine>> routines;
		};
	}
}

