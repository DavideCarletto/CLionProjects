cmake_minimum_required(VERSION 3.21)
project(PreparazioneEsame C)

set(CMAKE_C_STANDARD 99)

add_executable(PreparazioneEsame main.c Ricorsione/AlgoritmiOrdinamento.c Ricorsione/AlgoritmiOrdinamento.h Ricorsione/CalcoloCombinatorio.c Ricorsione/CalcoloCombinatorio.h Grafi/Graph.c Grafi/Graph.h Grafi/ST.c Grafi/ST.h Liste/List.c Liste/List.h Item/Item.c Item/Item.h Code/Heap.c Code/Heap.h Code/PQ.c Code/PQ.h BST/Bst.c BST/Bst.h)
