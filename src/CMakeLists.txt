project( NucleiSegregation )

find_package( OpenCV REQUIRED )

include_directories( src/watershed src/binning )

add_executable( NucleiSegregation nuclei_segregation.cpp opts.cpp image.cpp cropping/cropping.cpp watershed/thresholds.cpp watershed/fg_bg.cpp watershed/watershed.cpp binning/binning.cpp binning/nuclei_spots.cpp binning/gem.cpp)

target_link_libraries( NucleiSegregation ${OpenCV_LIBS} )
