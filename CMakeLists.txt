# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

project ("CMakeProject1")

add_executable(sb src/main.cpp src/BNode.cpp src/BNode.h src/BTree.cpp src/BTree.h)
