include(FetchContent)

FetchContent_Declare(
	googletest 
	URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
	)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
	asyncLogerTest
	asyncLogerTest.cc)

target_link_libraries(
	asyncLogerTest
	gtest_main
	AsyncLog
)

include(GoogleTest)
gtest_discover_tests(asyncLogerTest)
