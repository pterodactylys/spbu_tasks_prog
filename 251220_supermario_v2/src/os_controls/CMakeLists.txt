add_subdirectory(os_api)

if(WIN32)
    add_subdirectory(windows)
elseif(UNIX)
    add_subdirectory(unix)
endif()