# Native Build

```bash
$ mkdir build
$ cd build
$ cmake -G Xcode -DGTEST_HAS_PTHREAD=1 ../
```

then open the generated Xcode project and build it.

# Emscripten Build

```bash
$ mkdir embuild
$ cd embuild
$ emcmake cmake ..
$ make
```

# Emscripten Build

```
$ mkdir embuild
$ cd embuild
$ emcmake cmake ..
$ make
``` 
