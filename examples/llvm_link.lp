[
	llvm/execution_engine/run_function engine function
	[llvm/context/create; context]
	[llvm/module/assemble context `a |!|
		declare i32 @fun ()
		define i32 @main ()
		{
			%1 = call i32 @fun ()
			ret i32 %1
		}
	!; module1]
	[llvm/module/assemble context `a |!|
		define i32 @fun ()
		{
			ret i32 42
		}
	!; module2]
	[llvm/module/create context; module]
	[llvm/linker/link_modules module module1;; link1]
	[llvm/linker/link_modules module module2;; link2]
	[llvm/execution_engine/create_jit module; engine]
	[llvm/module/get_function module `a main link1 link2; function]
]