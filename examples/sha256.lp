[~	
	[llvm/compile/operation
		[.() verify]
		module
		`a temp/sha256
	]
	[llvm/module/verify
		[.() sha256]
		module
	;; verify]
	[add_abort
		context
		module
		synthesizer
	;; abort]
	[add_bits
		synthesizer
		module
	; bits]
	[llvm/synthesizer/create		
	; synthesizer]
	[llvm/synthesizer/merge
		synthesizer
		` bits/
		bits
	;; added_bits]
	[add_sha256
		[.() added_bits abort]
		synthesizer
		module
	; sha256]
	[llvm/module/create
		[llvm/context/create
		; context]
		context
	; module]
]

[.()
	add
	linkage
	name
	[llvm/global_value/set_linkage
		abort_function
		llvm/linkage_types/external
	;; linkage]
	[llvm/function/create
		[llvm/function_type/create
			context
			[{ ]
			[{ ]
		]
	; abort_function]
	[llvm/value/set_name
		abort_function
		`a abort
	;; name]
	[llvm/synthesizer/add
		synthesizer
		` abort
		abort_function
		[llvm/module/add_function
			module
			abort_function
		]
	;; add]
	[:~; context module synthesizer]
;; add_abort]

[synthesizer
	[script/ast/read_from_file ` examples/bits.lp]
	module
	[:~
	; synthesizer module]
;; add_bits]

[~
	[.() ]
	cluster	
	[synthesizer
		[script/ast/read_from_file ` examples/sha256_llvm.lp]
		module
	; cluster]
	[llvm/cluster/get
		cluster
		` _start
	; start]
	[llvm/value/set_name
		start
		`a _start
	]
	[llvm/global_value/set_linkage
		start
		llvm/linkage_types/external
	]
	[:~
	; synthesizer module]
;; add_sha256]