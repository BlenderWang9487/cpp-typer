# Cpp Typer

A proof-of-concept library that implement a interface to auto generate cli from an annotated struct

Inspired by [typer](https://github.com/fastapi/typer)

## Third party libraries

- [reflect-cpp v0.14.1](https://github.com/getml/reflect-cpp/releases/tag/v0.14.1)
- [CLI11 Version 2.4.2](https://github.com/CLIUtils/CLI11/releases/tag/v2.4.2)

## Usage

see [example.cpp](example.cpp)

run command:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config=Release

./bin/example --help
```

## Limitations

- Currently the struct type T that use for `cpp_typer::Typer<T>::parse_cli` can't inherit other type
- Unlike our inspiration, typer, cpp_typer can't use function signature to generate cli
- the `cpp_typer::Annotated` isn't as powerful as typer Annotated
