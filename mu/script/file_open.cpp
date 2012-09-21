#include <mu/script/file_open.h>

#include <mu/core/check.h>
#include <mu/script/context.h>
#include <mu/script/file_path.h>
#include <mu/script/file_node.h>
#include <mu/core/errors/error_target.h>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include <gc_cpp.h>

bool mu::script::file::open::operator () (mu::script::context & context_a)
{
    auto valid (mu::core::check <mu::script::file::path> (context_a));
    if (valid)
    {
        auto path (static_cast <mu::script::file::path *> (context_a.parameters (0)));
        auto result (core (path->path_m));
        if (result != nullptr)
        {
            if (result->stream.is_open ())
            {
                context_a.push (result);
            }
            else
            {
                context_a.errors (U"Unable to open file");
                valid = false;
            }
        }
        else
        {
            context_a.errors (U"Unable to open file");
            valid = false;
        }
    }
    return valid;
}

auto mu::script::file::open::core (boost::filesystem::path const & path_a) -> mu::script::file::node *
{
    auto valid (true);
    mu::script::file::node * result (nullptr);
    auto path_l (boost::filesystem::absolute (path_a));
    auto current (boost::filesystem::current_path ());
    auto i (current.begin ());
    auto j (current.end ());
    auto k (path_l.begin ());
    auto l (path_l.end ());
    for (; i != j && k != l && valid; ++i, ++k)
    {
        auto i_l (*i);
        auto k_l (*k);
        valid = i_l == k_l;
    }
    // Check if path ends before current_path
    if (k == l && i != j)
    {
        valid = false;
    }
    if (valid)
    {
        result = new (GC) mu::script::file::node (path_l);
    }
    return result;
}