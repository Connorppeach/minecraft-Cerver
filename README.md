## Minecraft server in C
This is a minecraft server written in C, designed for comfort and low overhead, with reasonable speed.


## todos
### ~~fix packet memory leaks, especially those in length prefixed lists~~
### make nbt library a more modern tape reader one, instead of the current "traditional" one
### remove mallocs from packet parsing
### make a schemad nbt reader and writer for nbt with a known structure using packet macros
### decouple simple_server.c code, break into select code, login handler, and length packet read writer
