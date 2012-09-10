[	[	loadb
		[	create
		;	ctx]
		`script
		`mu/script_binary/Debug/libmu_script_binary.dylib
	;	load]
	[	exec
		load :- nil
		ctx
		`mu/test/test1/stage2.mu
		`hash
		`mu/test/test1/input.txt
		`mu/test/test1/output.txt]
]
		