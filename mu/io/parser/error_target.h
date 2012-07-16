#include <mu/core/errors/error_target.h>

namespace mu
{
	namespace io
	{
		namespace parser
		{
			class parser;
			class error_target : public mu::core::errors::error_target
			{
			public:
				error_target (mu::io::parser::parser & parser_a, mu::core::errors::error_target * target_a);
				void operator () (mu::core::errors::error * error) override;
				bool operator () () override;
                void print (mu::ostream & target) override;
				mu::io::parser::parser & parser;
				mu::core::errors::error_target * target;
			};
		}
	}
}