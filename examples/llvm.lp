[
	[[llvm/context/create]; context]
	[`a |%|
		define i32 @main ()
		{
			ret i32 42
		}
	%; text]
	[[llvm/module/assemble context text]; module]
	[[llvm/execution_engine/create_jit module]; engine]
	[[llvm/module/get_function module `a main]; function]
	[llvm/execution_engine/run_function engine function]
]