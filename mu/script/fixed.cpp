#include "fixed.h"

void mu::script::fixed::perform (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	if (check_count (errors_a, parameters, count ()))
	{
		(*this) (errors_a, parameters, results);
	}
}