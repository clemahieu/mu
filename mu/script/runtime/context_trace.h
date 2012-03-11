namespace mu
{
	namespace core
	{
		class context;
	}
	namespace script
	{
		class context;
		namespace runtime
		{
			class context_trace
			{
			public:
				context_trace (mu::script::context & context_a, mu::core::context ctx_a);
				~context_trace ();
				mu::script::context & context;
			};
		}
	}
}