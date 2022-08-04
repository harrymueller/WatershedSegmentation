project(NucleiSegregation)
include_directories( inc inc/cropping inc/watershed inc/binning )
add_subdirectory( src )
set(CMAKE_CXX_STANDARD 17)