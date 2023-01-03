include(cmake/folders.cmake)

add_custom_target(
    run-exe
    COMMAND ulam_exe
    VERBATIM
)
add_dependencies(run-exe ulam_exe)

include(cmake/lint-targets.cmake)

add_folders(Project)
