#include <lambda_p_kernel/nodes/data.h>

#include <lambda_p/core/routine.h>

lambda_p_kernel::nodes::data::data(std::wstring string_a)
	: string_m (string_a)
{
}

std::wstring lambda_p_kernel::nodes::data::string () const
{
    return string_m;
}