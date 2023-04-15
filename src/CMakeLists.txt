add_library(pncalculator STATIC PNCalculator.cpp)
target_include_directories(pncalculator PUBLIC .)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE pncalculator)
