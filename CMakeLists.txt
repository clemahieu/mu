set(LLVM_LINK_COMPONENTS
  Core
  MC)

include_directories (${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory (mu/core)
add_subdirectory (mu/io)
add_subdirectory (mu/llvmc)
add_subdirectory (mu/test)
add_subdirectory (mu/muc)
