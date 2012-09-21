#include <mu/script/file_path_from_string.h>

#include <mu/core/check.h>
#include <mu/script/context.h>
#include <mu/script/string_node.h>
#include <mu/script/file_path.h>
#include <mu/core/errors/error_target.h>

#include <boost/filesystem.hpp>

#include <gc_cpp.h>

bool mu::script::file::path_from_string::operator () (mu::script::context & context_a)
{
    auto valid (mu::core::check <mu::script::string::node> (context_a));
    if (valid)
    {
        auto result (core (static_cast <mu::script::string::node *> (context_a.parameters (0))->string));
        if (result != nullptr)
        {
            context_a.push (result);
        }
        else
        {
            context_a.errors (U"Unable to convert string to path");
            valid = false;
        }
    }
    return valid;
}

auto mu::script::file::path_from_string::core (mu::string const & string_a) -> mu::script::file::path *
{
    std::string string_l (string_a.begin (), string_a.end ());
    mu::script::file::path * result (nullptr);
    try
    {
        boost::filesystem::path path (string_l);
        result = new (GC) mu::script::file::path (path);
    }
    catch (boost::filesystem::filesystem_error const & e)
    {
    }
    return result;
}