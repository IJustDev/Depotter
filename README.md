# Depotter

Depotter is intended to help you testing your financial strategies.
Depotter lets you create a plain txt file containing all the positions you've got (or would have invested in) and calculates the W/L and performance of each and all positions.

It uses the unoffical Yahoo Finance API.

## Showcase
![Showcase](resources/showcase.png)

## Build from source
Since the application is written in C++ with minimal library dependency you simply need to run
```sh
$ make
```
and the depot should be available to you as binary.

## Prerequisites
1. Install the [`cJSON`][cjson] library and add it to your library path.

## Usage
Create a file called `depot.txt` with following content.

### Sample Depot file
```
# Amount Name Yahoo-Symbol BuyPrice
8.3 Dax ^GDAXI 11003
1.03 MSCI-WLD EUNL.DE 45
```

*NOTE*: See the [`sample_depot_file.txt`](./sample_depot_file.txt) in this repository for a file with more than just two positions.

Then call
```sh
$ ./depot depot.txt
```

You can also use relative paths like
```sh
$ ./depot ../depot.txt
$ # or
$ ./depot ~/depot.txt
```


[cjson]: https://github.com/DaveGamble/cJSON#cmake
