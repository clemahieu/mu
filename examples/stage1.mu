[
	[context; ctx]
	[~
		[loads ctx ` || ` examples/include.mu]
		[exec ` mu/source/script.mu ctx]
	;; load_l]
	run load_l ctx ` examples/stage2.mu
]