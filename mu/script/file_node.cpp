#include <mu/script/file_node.h>

mu::script::file::node::node (boost::filesystem::path const & path):
stream (path)
{
}

mu::script::file::node::~node ()
{
    stream.close ();
}