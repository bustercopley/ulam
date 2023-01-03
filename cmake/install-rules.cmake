install(
    TARGETS ulam_exe
    RUNTIME COMPONENT ulam_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
