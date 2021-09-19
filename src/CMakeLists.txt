# Generic test that uses conan libs

set(src 
        main.cpp 
    )
set(inc
    heuristics.hpp
    chromosome.hpp
    geneticalgorithm.hpp
    population.hpp
    utilities.hpp
    selection.hpp
    )
add_executable(intro ${src} ${inc})
target_link_libraries(
  intro
  PRIVATE project_options
          CONAN_PKG::fmt
          CONAN_PKG::spdlog)
