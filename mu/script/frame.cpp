#include <mu/script/frame.h>

#include <mu/script/context.h>
#include <mu/script/location.h>

#include <boost/make_shared.hpp>

mu::script::frame::frame (mu::script::context & context_a)
	: context (context_a)
{
	context_a.stack.push_back (boost::make_shared <mu::script::location> (context_a.frame_begin));
	context_a.slide ();
}

mu::script::frame::~frame ()
{
	assert (boost::dynamic_pointer_cast <mu::script::location> (context.stack [context.frame_begin - 1]) != nullptr);
	context.drop ();
	auto location (boost::static_pointer_cast <mu::script::location> (context.stack [context.frame_begin - 1]));
	context.frame_begin = location->position;
	context.stack.resize (context.stack.size () - 1);
}