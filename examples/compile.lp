[llvm/compile/operation
	[llvm/module/assemble 
		[llvm/context/create]
		`a
			|!|
				declare i8 * @GetModuleHandleW (i8 *)
				declare void @ExitProcess (i32) noreturn
				define void @_start () noreturn
				{
					%1 = call i8 * @GetModuleHandleW (i8 * null)
					call void @ExitProcess (i32 0)
					ret void
				}
			!
	]
	`a temp/test
]