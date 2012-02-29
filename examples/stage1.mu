[
	[context; ctx]
	[loads ctx ` || ` examples/include.mu ;; l1]
	run l1 ctx ` examples/stage2.mu
]