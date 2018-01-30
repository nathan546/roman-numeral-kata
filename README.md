# Roman Numeral Calculator Kata
This is a programming exercise which demonstrates how to add and subtract roman numeral values from each other using a test driven development process.  This program incorporates the use of check unit testing framework ( https://libcheck.github.io/check/ ) for doing test driven development.

### Installation
This exercise requires
* Ubuntu Linux 14.04 (or similar)
* GNU GCC compiler tool chain
* GNU Make
* Check unit testing framework ( https://libcheck.github.io/check/ )
* git
* other required dependences for the tools listed above


On my system, I had to install these dependencies:

```sh
$ sudo apt-get install check subunit libsubunit-dev
```

If any of these libraries are missing from your system, they must be located and installed:
* libcheck
* libsubunit  
* libm
* librt
* libpthread


### Downloading/Building Instructions
Open a terminal

```sh
$ git clone https://github.com/nathan546/roman-numeral-kata.git
$ cd roman-numeral-kata/
$ make
$ cd build
$ ./romanNumeralCalculator
```
Note: The romanNumeralCalculator binary must be run with the following files in the same directory:
complete_induction.equations, story_addition.equations, and story_subtraction.equations


### Software Architecture
[![N|Solid](https://cldup.com/dTxpPi9lDf.thumb.png)](https://nodesource.com/products/nsolid)

## Roman Numeral rules:

* Roman numerals consist of the following letters: I, V, X, L, C, D, and M which mean one, five, ten, fifty, hundred, five hundred and one thousand respectively.
* An example would be "XIV" + "LX" = "LXXIV" 
* Numerals can be concatenated to form a larger numeral ("XX" + "II" = "XXII").
* If a lesser numeral is put before a bigger it means subtraction of the lesser from the bigger ("IV" means four, "CM" means ninehundred).
* If the numeral is I, X or C you can't have more than three ("II" + "II" = "IV" not “IIII”).
* If the numeral is V, L or D you can't have more than one ("D" + "D" = "M" not “DD”)
* The maximum roman numeral is 3999 (MMMCMXCIX) 

## Stories

### User Story: Addition
As a Roman bookkeeper, I want to be able to add two numbers together; so that I can do my work faster with fewer mathematical errors.  

### User Story: Subtraction 
As a Roman bookkeeper, I want to be able to subtract one number from another; so that I can do my work faster and with fewer mathematical errors.