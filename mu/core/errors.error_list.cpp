#include "errors.error_list.h"

#include <mu/core/errors.error.h>

#include <iostream>

void mu::core::errors::error_list::operator () (boost::shared_ptr <mu::core::errors::error> error, mu::core::context context_a)
{
	errors.push_back (std::pair <boost::shared_ptr <mu::core::errors::error>, mu::core::context> (error, context_a));
}

bool mu::core::errors::error_list::operator () ()
{
	return !errors.empty ();
}

void mu::core::errors::error_list::print ()
{
    for (auto i (errors.begin ()), j (errors.end ()); i != j; ++i)
    {
        i->first->string (std::wcout);
    }
}
