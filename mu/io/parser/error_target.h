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
				error_target (mu::io::parser::parser & parser_a, boost::shared_ptr <mu::core::errors::error_target> target_a);
				void operator () (boost::shared_ptr <mu::core::errors::error> error, mu::core::context context_a) override;
				bool operator () () override;
                void print (std::wostream & target) override;
				mu::io::parser::parser & parser;
				boost::shared_ptr <mu::core::errors::error_target> target;
			};
		}
	}
}