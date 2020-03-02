# Entity Component System

## Problems of the classic approach

1. Data is scattered and loading from memory to cache is very slow.

A game object is just a container of references to memory locations which contain references to other memory locations and so on.

2. A bunch of extra data provided.

Not everything inside a class is needed. For example moving only needs speed and transform values but in this case up, right, forward, euler angles etc. are also loaded, even if not required.

