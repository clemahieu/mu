extern char const * const generate_add_expected = R"%%%(
define i1 @0(i1) {
  %2 = add i1 %0, %0
  ret i1 %2
                                                  ; No predecessors!
  unreachable
}
)%%%";

extern char const * const generate_two_return_expected = R"%%%(
%0 = type { i1, i1 }

define %0 @0(i1) {
  %2 = insertvalue %0 undef, i1 %0, 0
  %3 = insertvalue %0 %2, i1 %0, 1
  ret %0 %3
                                                  ; No predecessors!
  unreachable
}
)%%%";

extern char const * const generate_if_expected = R"%%%(
define i8 @0(i1) {
  switch i1 %0, label %2 [
    i1 false, label %3
    i1 true, label %4
  ]

; <label>:2                                       ; preds = %1
  unreachable

; <label>:3                                       ; preds = %1
  ret i8 1

; <label>:4                                       ; preds = %1
  ret i8 0
}
)%%%";

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