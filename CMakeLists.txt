cmake_minimum_required(VERSION 3.25)
project(1_Data_Structures)

set(CMAKE_CXX_STANDARD 17)

add_executable(1_Data_Structures main.cpp utilities.h UnsortedArray.h UnsortedArray.cpp SortedArray.cpp SortedArray.h BinarySearchTree.cpp BinarySearchTree.h AVLTree.cpp AVLTree.h HashTable.cpp HashTable.h DataStructure.cpp DataStructure.h)
