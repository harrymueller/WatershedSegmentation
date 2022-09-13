project(NucleiSegregation)
include_directories( inc inc/cropping inc/watershed inc/binning )
set(CMAKE_CXX_STANDARD 17)
add_subdirectory( src )
