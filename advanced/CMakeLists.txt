cmake_minimum_required(VERSION 3.15)
project(advanced)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
set(CMAKE_C_FLAGS -O3)

add_executable(advanced main.cpp Machine.cpp Machine.h Task.cpp Task.h tabu/TabooSolver.cpp tabu/TabooSolver.h tabu/Solution.cpp tabu/Solution.h tabu/generation/BaseInitialGenerationStrategy.h tabu/neighbourhood/BaseNeighbourhoodGenerationStrategy.h tabu/generation/MyInitialGenerationStrategy.cpp tabu/generation/MyInitialGenerationStrategy.h tabu/generation/WoodpeckerInitialGenerationStrategy.cpp tabu/generation/WoodpeckerInitialGenerationStrategy.h tabu/generation/EDDInitialGenerationStrategy.cpp tabu/generation/EDDInitialGenerationStrategy.h tabu/generation/ERTInitialGenerationStrategy.cpp tabu/generation/ERTInitialGenerationStrategy.h tabu/generation/ImprovedInitialGenerationStrategy.cpp tabu/generation/ImprovedInitialGenerationStrategy.h tabu/generation/JustInTimeInitialGenerationStrategy.cpp tabu/generation/JustInTimeInitialGenerationStrategy.h tabu/Operation.cpp tabu/Operation.h tabu/neighbourhood/FirstNeighbourhoodGenerationStrategy.cpp tabu/neighbourhood/FirstNeighbourhoodGenerationStrategy.h tabu/generation/BestOfTwoGenerationStrategy.cpp tabu/generation/BestOfTwoGenerationStrategy.h)