#include <mu/core/errors/error_list.h>

#include <mu/core/errors/error.h>

#include <iostream>

void mu::core::errors::error_list::operator () (mu::core::errors::error * error)
{
	errors.push_back (error);
}

bool mu::core::errors::error_list::operator () ()
{
	return !errors.empty ();
}

void mu::core::errors::error_list::print (std::wostream & target)
{
    for (auto i (errors.begin ()), j (errors.end ()); i != j; ++i)
    {
        (*i)->string (target);
        target << L'\n';
    }
}