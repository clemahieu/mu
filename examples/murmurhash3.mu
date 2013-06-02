function rotl32
[int32 x int32 r]
[
	let result [or [shl x r] [lshr x [sub cint32 #32 r]]]
]
[[int32 result]]

function rotl64
[int64 x int64 r]
[
	let result [or [shl x r] [lshr x [sub cint64 #64, r]]]
]
[[int64 result]]