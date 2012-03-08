[
	[context; ctx]
	[~
		[loads ctx ` || ` examples/include.mu]
                [loadb ctx ` llvm/ ` mu/llvm_binary/Debug/mu_llvm_binary.dll]
		[exec ` mu/source/script.mu ctx]
	;; load_l]
        run
        load_l
        ctx
        ` examples/stage2.mu
]
