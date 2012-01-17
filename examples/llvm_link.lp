[
	llvm/execution_engine/run_function engine function				:- Run the main function
	[llvm/context/create; context]									:- Create llvm context
	[llvm/module/assemble context									:- Create module 1 which has @main function and declares @fun
		`a |!|
		declare i32 @fun ()
		define i32 @main ()
		{
			%1 = call i32 @fun ()
			ret i32 %1
		}
	!; module1]
	[llvm/module/assemble context 									:- Create module 2 which has the definition of @fun
		`a |!|
		define i32 @fun ()
		{
			ret i32 42
		}
	!; module2]
	[llvm/module/create context; module]							:- Create top level module
	[llvm/linker/link_modules module module1;; link1]				:- Merge module 1 in to top level module
	[llvm/linker/link_modules module module2;; link2]				:- Merge module 2 in to top level module
	[llvm/execution_engine/create_jit module; engine]				:- Create JIT engine over top level module
	[llvm/module/get_function module `a main link1 link2; function]	:- Get the `main' function out of top level module, after module 1 and module 2 have been linked in.
]