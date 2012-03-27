#include <mu/io/debugging/file_stream.h>

mu::io::debugging::file_stream::file_stream ()
{
}

mu::io::debugging::file_stream::file_stream (std::wstring const & original_name_a)
	: original_name (original_name_a)
{
}