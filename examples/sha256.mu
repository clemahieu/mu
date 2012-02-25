[~	
	[.load
		` libs/llvm/core.mu
	; llvm/core]
	[.load
		` libs/llvm/libc.mu
	; llvm/libc]
	[.apply
		[llvm/core
			` add_function
		]
		context
		module
		synthesizer
	; add_function]
	[[llvm/libc
		` initialize]
		add_function
		context
	;; libc]
	[llvm/compile/operation
		[.() verify print]
		module
		`a temp/sha256
	]
	[script/print/operation
		[llvm/module/print
			module
		]		
	;; print]
	[llvm/module/verify
		[.() sha256]
		module
	;; verify]
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
		[.() added_bits libc]
		synthesizer
		module
	; sha256]
	[llvm/module/create
		[llvm/context/create
		; context]
		context
	; module]
]

[synthesizer
	[script/ast/read_from_file ` examples/bits.mu]
	module
	[:~
	; synthesizer module]
;; add_bits]

[~
	[.() ]
	cluster	
	[synthesizer
		[script/ast/read_from_file ` examples/sha256_llvm.mu]
		module
	; cluster]
	[llvm/cluster/get
		cluster
		` entry
	; start]
	[llvm/value/set_name
		start
		`a main
	]
	[llvm/global_value/set_linkage
		start
		llvm/linkage_types/external
	]
	[:~
	; synthesizer module]
;; add_sha256]