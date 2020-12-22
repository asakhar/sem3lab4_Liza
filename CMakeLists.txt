cmake_minimum_required(VERSION 3.12)
project(Library LANGUAGES CXX)


add_executable(Lib main.cpp BookEdition.cpp FictionEdition.cpp LearningEdition.cpp ScientificEdition.cpp Table.cpp)
