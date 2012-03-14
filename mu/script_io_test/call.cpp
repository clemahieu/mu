#include "call.h"

#include <mu/script_io/expression.h>
#include <mu/script/runtime/call.h>
#include <mu/script/runtime/expression.h>
#include <mu/script/runtime/reference.h>
#include <mu/core/node.h>
#include <mu/core/expression.h>
#include <mu/core/reference.h>
#include <mu/script/runtime/constant.h>
#include <mu/script/cluster/node.h>
#include <mu/script_io/cluster.h>
#include <mu/core/cluster.h>

#include <boost/make_shared.hpp>

void mu::script_io_test::call::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
}

void mu::script_io_test::call::run_1 ()
{
	std::map <boost::shared_ptr <mu::core::expression>, size_t> reservations;
	boost::shared_ptr <mu::script::runtime::call> target (new mu::script::runtime::call (1));
	boost::shared_ptr <mu::core::node> node (new mu::core::node);
	auto remapping (boost::make_shared <mu::script::cluster::node> ());
	mu::script_io::cluster cluster (boost::make_shared <mu::core::cluster> ());
	mu::script_io::expression expression (cluster, reservations, target, node);
	assert (target->arguments.size () == 1);
	auto added (boost::dynamic_pointer_cast <mu::script::runtime::constant> (target->arguments [0]));
	assert (added.get () != nullptr);
	assert (added->value == node);
}

void mu::script_io_test::call::run_2 ()
{
	std::map <boost::shared_ptr <mu::core::expression>, size_t> reservations;
	boost::shared_ptr <mu::script::runtime::call> target (new mu::script::runtime::call (1));
	boost::shared_ptr <mu::core::expression> parameters (new mu::core::expression);
	reservations.insert (std::map <boost::shared_ptr <mu::core::expression>, size_t>::value_type (parameters, 0));
	auto remapping (boost::make_shared <mu::script::cluster::node> ());
	mu::script_io::cluster cluster (boost::make_shared <mu::core::cluster> ());
	mu::script_io::expression expression (cluster, reservations, target, parameters);
	assert (target->arguments.size () == 1);
	auto added (boost::dynamic_pointer_cast <mu::script::runtime::expression> (target->arguments [0]));
	assert (added.get () != nullptr);
	assert (added->index == 0);
}

void mu::script_io_test::call::run_3 ()
{
	std::map <boost::shared_ptr <mu::core::expression>, size_t> reservations;
	boost::shared_ptr <mu::script::runtime::call> target (new mu::script::runtime::call (1));
	boost::shared_ptr <mu::core::expression> parameters (new mu::core::expression);
	reservations.insert (std::map <boost::shared_ptr <mu::core::expression>, size_t>::value_type (parameters, 0));
	boost::shared_ptr <mu::core::reference> reference (new mu::core::reference (parameters, 0));
	auto remapping (boost::make_shared <mu::script::cluster::node> ());
	mu::script_io::cluster cluster (boost::make_shared <mu::core::cluster> ());
	mu::script_io::expression expression (cluster, reservations, target, reference);
	assert (target->arguments.size () == 1);
	auto added (boost::dynamic_pointer_cast <mu::script::runtime::reference> (target->arguments [0]));
	assert (added.get () != nullptr);
	assert (added->expression == 0);
	assert (added->index == 0);
}