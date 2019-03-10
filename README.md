# TmxLoader
Tmx File (Tiled Map Editor's Map file) Loader based on Tinyxml2.

## Feature
 - Read TMX and TSX. (currently supports version 1.1 - https://doc.mapeditor.org/en/stable/reference/tmx-map-format)
 - Hardly depending on STL.

## Usage
Clone this repository and add source files in your project.
Then, just include "TmxLoader.h".

(This project does not include CMake Files or Makefiles,
so please configure your own build environment by yourself.)

TmxLoader::ParseTMX() returns TmxLoader::Map, which contains all data.

## Thanks
This library consists of some grateful projects below.

Tinyxml-2 - Copyright (c) 2018 leethomason (https://github.com/leethomason/tinyxml2)
single header base64 encoder/decoder - Copyright (c) 2016 tomykaira (https://gist.github.com/tomykaira/f0fd86b6c73063283afe550bc5d77594)

### Todo
 - Support template.
 - Add zlib, gzlp decompression.
 - Add Base64 decoder.
 - Make include file dependencies tidy.
 - Inspect behavior.
