[
	[llvm_io/synthesizer
		=>
			[
				[:~; add_v v1 v2]
				add_v [v1] [v2]
			]
		module
		[llvm/value/get_type add_v]
		[llvm/value/get_type v1]
		[llvm/value/get_type v2]
	]
	[script/package/get
		package
		` v1
	; v1]
	[script/package/get
		package
		` v2
	; v2]
	[script/package/get
		package
		` add_v
	; add_v]
	[llvm/module/get_package
		module
		`a ||
	; package]
	[llvm/module/assemble 
		[llvm/context/create]
		`a
			|!|
				define i32 @v1 ()
				{
					ret i32 1000
				}
				define i32 @v2 ()
				{
					ret i32 500
				}
				define i32 @add_v (i32, i32)
				{
					%3 = add i32 %0, %1
					ret i32 %3
				}
			!
	; module]
]