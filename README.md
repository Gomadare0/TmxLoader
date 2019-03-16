# TmxLoader
Tmx File (Tiled Map Editor's Map file) Loader based on Tinyxml2.

## Feature
 - Read TMX, TSX and TX. (currently supporting version 1.1 - https://doc.mapeditor.org/en/stable/reference/tmx-map-format)
 - Hardly depending on STL.
 - Utilities for OpenSiv3D(Require C++17).

## Usage
Clone this repository and add source files in your project.
Then, just include "TmxLoader.h".

(This project does not provide CMake Files or Makefiles,
so please prepare your own build environment by yourself.)

TmxLoader::ParseTMX() returns TmxLoader::Map, which contains all data.

## Thanks
This library consists of grate projects below.

 - Tinyxml-2 - Copyright (c) 2018 leethomason (https://github.com/leethomason/tinyxml2)

### Todo
 - Add zlib, gzlp decompression.
 - Inspect behavior.
 - TMX Exporting.
