#include "node.h"

#include <mu/io/analyzer/extensions/extensions.h>

#include <boost/make_shared.hpp>

mu::script::extensions::node::node ()
	: extensions (boost::make_shared <mu::io::analyzer::extensions::extensions> ())
{
}