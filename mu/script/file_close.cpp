#include <mu/script/file_close.h>

#include <mu/core/check.h>
#include <mu/script/context.h>
#include <mu/script/file_node.h>

bool mu::script::file::close::operator () (mu::script::context & context_a)
{
    auto valid (mu::core::check <mu::script::file::node> (context_a));
    if (valid)
    {
        auto file (static_cast <mu::script::file::node *> (context_a.parameters (0)));
        file->stream.close ();
    }
    return valid;
}