#pragma once

#include <lambda_p/binder/binder.h>

#include <boost/enable_shared_from_this.hpp>

namespace lambda_p
{
    namespace binder
    {        
		class data;
		class routine_instances;
    }
}
namespace lambda_p_kernel
{
    class package : public lambda_p::binder::binder, public boost::enable_shared_from_this <lambda_p_kernel::package>
    {
    public:
        package (void);
        ~package (void);
        virtual void bind (lambda_p::core::statement * statement, lambda_p::binder::routine_instances & instances, lambda_p::errors::error_list & problems) override;
		std::map <std::wstring, boost::shared_ptr <lambda_p::binder::instance> > nodes;
		std::wstring binder_name () override;
	private:
		void parse_one (lambda_p::binder::routine_instances & instances, boost::shared_ptr <lambda_p::binder::data> node, size_t result, lambda_p::errors::error_list & problems);
    };
}
