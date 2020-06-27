# MineC++

MineC++ is a scalable server backend for Minecraft Java Edition written in C++.
As well as a set of utilities to support Minecraft game files and
 to reflect game mechanics. MineC++ is completely free of any code developed by Mojang AB.
 
## Services

The backend consists of multiple services for scaling. 

+ Front - Receives and maintains tcp connections with players.
+ Engine - Responsible for game mechanics.
+ Chunk Storage - A storage for terrain information and non-player entities.
+ WorldGen - Chunk generator. (PLANNED)

## Dependencies

+ GRPC
+ Google Test
+ Boost
+ Yaml-CPP
+ Spdlog
