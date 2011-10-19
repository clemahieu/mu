#include "target_not_bindable.h"

lambda_p::errors::error_id lambda_p::errors::target_not_bindable::error_type ()
{
	return lambda_p::errors::error_target_not_bindable;
}

void lambda_p::errors::target_not_bindable::string (std::wostream & stream)
{
	stream << L"Target of statement is not bindable";
}
