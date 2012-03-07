#include <mu/script/type_check/operation.h>

#include <mu/core/errors/error_target.h>

#include <sstream>
#include <typeinfo>

mu::script::type_check::operation::operation (boost::shared_ptr <mu::script::operation> target_a)
: target (target_a)
{
}

void mu::script::type_check::operation::perform (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
    if (parameters.size () == type_ids.size ())
    {
        auto i (parameters.begin ());
        auto j (parameters.end ());
        auto k (type_ids.begin ());
        auto l (type_ids.end ());
        size_t position (0);
        bool good (true);
        while (i != j)
        {
			if (typeid (i->get ()) != **k)
            {
                good = false;
                std::wstringstream message;
                message << L"In operation: ";
                message << target->name ();
                message << L" invalid node type";
                message << L" at position: ";
                message << position;
                (*errors_a) (message.str ());
            }
			++i;
			++k;
			++position;
        }
        if (good)
        {
			target->perform (errors_a, parameters, results);
        }
    }
    else
    {
		std::wstringstream message;
		message << L"In operation: ";
		message << target->name ();
		message << L" expecting: ";
		message << type_ids.size ();
		message << L" arguments, have: ";
		message << parameters.size ();
		(*errors_a) (message.str ());
    }
}