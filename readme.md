# MineCPP

MineCPP is a set of utilities and services written in C++ to support MineCraft game files and
 reflect game mechanics. MineCPP is completely free of any code developed by Mojang AB.
 
The goal of the project is to create high capacity server backend for the game.

## Backend services

+ Front - Receives and maintains tcp connections with players
+ Engine - Reflects the game mechanics of the game
+ Chunk Storage - A storage for terrain information, entities and players

These services depend on kafka for game events and redis for caching.

## Dependencies

+ GRPC
+ Google Test
+ Boost
+ Spdlog
