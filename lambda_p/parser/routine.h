#pragma once

#include <boost/shared_ptr.hpp>

#include <lambda_p/parser/state.h>
#include <lambda_p/parser/association_target.h>

#include <map>
#include <string>
#include <vector>

namespace lambda_p
{
	namespace binder 
	{
		class node;
	}
	namespace core
	{
		class routine;
	}
	namespace parser
	{
		class routine : public state, public lambda_p::parser::association_target
		{
		public:
			routine (std::vector <std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>>> & injected_parameters, std::vector <std::wstring> & injected_returns);
			state_id state_type ();
			boost::function <void (size_t)> sink_declaration () override;
			boost::function <void (size_t)> sink_argument () override;
			boost::shared_ptr <lambda_p::core::routine> routine_m;
			bool have_surface;
			std::multimap <std::wstring, boost::function <void (size_t)>> unresolved_references;
			std::map <std::wstring, size_t> positions;
			bool parsed_routine;
		};
	}
}

