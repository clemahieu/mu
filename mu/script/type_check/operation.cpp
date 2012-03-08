#include <mu/script/type_check/operation.h>

#include <mu/core/errors/error_target.h>

#include <sstream>
#include <typeinfo>

mu::script::type_check::operation::operation (boost::shared_ptr <mu::script::operation> target_a)
: target (target_a)
{
}

void mu::script::type_check::operation::perform (mu::script::context & context_a)
{
    if (context_a.parameters.size () == type_ids.size ())
    {
        auto i (context_a.parameters.begin ());
        auto j (context_a.parameters.end ());
        auto k (type_ids.begin ());
        auto l (type_ids.end ());
        size_t position (0);
        bool good (true);
        while (i != j)
        {
			std::type_info const & info (typeid (*i->get ()));
			std::type_info const & expected (**k);
			if (info != expected)
            {
                good = false;
                std::wstringstream message;
                message << L"In operation: ";
                message << target->name ();
                message << L" invalid node type: ";
				message << info.name ();
                message << L" at position: ";
                message << position;
				message << L" expecting: ";
				message << expected.name ();
                (*context_a.errors) (message.str ());
            }
			++i;
			++k;
			++position;
        }
        if (good)
        {
			target->perform (context_a);
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
		message << context_a.parameters.size ();
		(*context_a.errors) (message.str ());
    }
}