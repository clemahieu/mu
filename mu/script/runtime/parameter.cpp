#include <mu/script/runtime/parameter.h>

#include <mu/core/check.h>
#include <mu/script/runtime/locals.h>
#include <mu/core/errors/error_target.h>
#include <mu/script/context.h>

mu::script::runtime::parameter::parameter (size_t position_a):
position (position_a)
{
}

bool mu::script::runtime::parameter::operator () (mu::script::context & context_a)
{
    bool valid (mu::core::check <mu::script::runtime::locals> (context_a));
    if (valid)
    {
        auto locals (static_cast <mu::script::runtime::locals *> (context_a.parameters(0)));
        if (position < locals->parameters)
        {
            context_a.push (locals->frame [position]);
        }
        else
        {
            valid = false;
            mu::stringstream message;
            message << U"Trying to get parameter number: ";
            message << position;
            message << U" but only have: ";
            message << locals->parameters;
            message << U" parameters.";
            context_a.errors (message.str ());
        }
    }
    return valid;
}