extern char const * const generate_if_value_expected = R"%%%(
%0 = type { i32, i32, i8 }

define %0 @0(i1) {
  switch i1 %0, label %2 [
    i1 false, label %3
    i1 true, label %6
  ]

; <label>:2                                       ; preds = %1
  unreachable

; <label>:3                                       ; preds = %1
  %4 = insertvalue %0 undef, i32 4, 1
  %5 = insertvalue %0 %4, i8 1, 2
  ret %0 %5

; <label>:6                                       ; preds = %1
  %7 = insertvalue %0 undef, i32 4, 0
  %8 = insertvalue %0 %7, i8 0, 2
  ret %0 %8
}
)%%%";