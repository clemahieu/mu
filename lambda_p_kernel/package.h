#pragma once

#include <lambda_p/binder/binder.h>

#include <boost/enable_shared_from_this.hpp>

#include <map>

namespace lambda_p
{
    namespace binder
    {        
		class data;
		class node_list;
    }
}
namespace lambda_p_kernel
{
    class package : public lambda_p::binder::binder, public boost::enable_shared_from_this <lambda_p_kernel::package>
    {
    public:
        virtual void bind (lambda_p::core::statement * statement, lambda_p::binder::node_list & nodes, lambda_p::errors::error_list & problems) override;
		std::map <std::wstring, boost::shared_ptr <lambda_p::binder::node>> nodes;
		std::wstring binder_name () override;
	private:
		void parse_one (lambda_p::binder::node_list & nodes, boost::shared_ptr <lambda_p::binder::data> node, size_t result, lambda_p::errors::error_list & problems);
    };
}
