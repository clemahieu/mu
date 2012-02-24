#include "parameters.h"

#include <core/visitor.h>

void mu::core::parameters::operator () (mu::core::visitor * visitor_a)
{
	(*visitor_a) (this);
}