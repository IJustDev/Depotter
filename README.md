# Depotter

Depotter is intended to help you testing your financial strategies.
Depotter lets you create a plain txt file containing all the positions you've got (or would have invested in) and calculates the W/L and performance of each and all positions.

## Showcase
![Showcase](resources/showcase.png)

## Build from source
Since the application is written in C++ with minimal library dependency you simply need to run
```sh
$ make
```
and the depot should be available to you as binary.

## Usage
Create a file called `depot.txt` with following content.

### Sample Depot file
```
# This is a comment
1 AcmeInc 20 25
2 Google 30 10
```
```
1 -> Amount
AcmeInc -> Company
20 -> Buy Price
25 -> Current Value
```

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

