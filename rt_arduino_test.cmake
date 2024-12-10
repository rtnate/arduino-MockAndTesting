function(fetch_google_test)
    include(FetchContent)

    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )

    set(gtest_fource_shared_crt ON CACHE BOOL "" FORCE)

    FetchContent_MakeAvailable(googletest)
endfunction()

function(rt_create_test_suite TEST_SUITE_NAME) 
    fetch_google_test()
    
    if (NOT COMMAND gtest_discover_tests)
        fetch_google_test()
    endif()

    message("Adding Sources: ${ARGN}")
    add_executable(${TEST_SUITE_NAME} ${ARGN})

    target_link_libraries(
        ${TEST_SUITE_NAME}
        PRIVATE 
            GTest::gtest_main
    )

    target_compile_definitions(
        ${TEST_SUITE_NAME}
        PUBLIC
            RT_UNIT_TEST=1
    )
endfunction()