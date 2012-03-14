#pragma once

#include <mu/core/errors/error_target.h>

namespace mu
{
	namespace io
	{
		namespace lexer
		{
			class lexer;
			class error_target : public mu::core::errors::error_target
			{
			public:
				error_target (mu::io::lexer::lexer & lexer_a, boost::shared_ptr <mu::core::errors::error_target> target_a);
				void operator () (boost::shared_ptr <mu::core::errors::error> error) override;
				bool operator () () override;
                void print (std::wostream & target) override;
				mu::io::lexer::lexer & lexer;
				boost::shared_ptr <mu::core::errors::error_target> target;
			};
		}
	}
}