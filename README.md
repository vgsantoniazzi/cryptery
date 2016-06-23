## Welcome to cryptery

this is a C algorithm to decrypt w/ brute-force hashes

This branch uses Intel cilkplus

## Getting Started

Compiling with Clang

```
clang cryptery.c -o cryptery -std=c11 -fcilkplus -lcilkrts -lpthread -lcrypto
```

## Usage

```
CILK_NWORKERS=1 ./cryptery __HASH__
```

## Contributing

I :heart: Open source!

[Follow github guides for forking a project](https://guides.github.com/activities/forking/)

[Follow github guides for contributing open source](https://guides.github.com/activities/contributing-to-open-source/#contributing)

## Code status

## License

Cryptery is released under the [MIT license](http://opensource.org/licenses/MIT).
