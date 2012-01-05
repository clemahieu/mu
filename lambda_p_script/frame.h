#pragma once

#include <map>
#include <vector>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class node;
	namespace errors
	{
		class error_target;
	}
}
namespace lambda_p_script
{
	class frame
	{
		frame (boost::shared_ptr <lambda_p::errors::error_target> errors_a);
	public:
		void operator () (std::wstring name, std::vector <boost::shared_ptr <lambda_p::node>> & values_a);
		std::vector <boost::shared_ptr <lambda_p::node>> & operator () (std::wstring name);
	private:
		boost::shared_ptr <lambda_p::errors::error_target> errors;
		std::map <std::wstring, std::vector <boost::shared_ptr <lambda_p::node>>> values;
	};
}

