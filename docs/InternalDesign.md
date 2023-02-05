# Internal Design

This document described the internal design of the Mine C++ engine.
Engine functionalities are seperated into systems. Systems are dived based on scope:

+ **Engine Scope System** - Systems that manage the inner-workings of the engine or take care of global game resources.
+ **World Scope System** - Systems that operate within a specific world.

## Engine Scope System

The game recognised the following engine scope systems.

+ **Job System**
+ **Tick System**
+ **Resource System**
+ **World System**

## World Scope System

The game recognised the following world scope systems.

+ **Light System**
+ **Chunk System**
+ **Entity System**