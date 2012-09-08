#include <mu/script/file_node.h>

mu::script::file::node::node (boost::filesystem3::path const & path):
stream (path)
{
}