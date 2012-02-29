[
	[context; ctx]
	[~
		[loads ctx ` || ` examples/include.mu]
	;; load_l]
	run load_l ctx ` examples/stage2.mu
]