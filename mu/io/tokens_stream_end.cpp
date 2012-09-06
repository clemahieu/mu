#include <mu/io/tokens_stream_end.h>

#include <mu/io/tokens_visitor.h>

mu::io::tokens::stream_end::stream_end (mu::io::context const & context_a):
mu::io::tokens::token (context_a)
{
}

mu::string mu::io::tokens::stream_end::token_name () const
{
	return mu::string (U"stream end");
}

void mu::io::tokens::stream_end::operator () (mu::io::tokens::visitor * visitor_a)
{
	(*visitor_a) (*this);
}