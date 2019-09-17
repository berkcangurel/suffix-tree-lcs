This program finds the [Longest Common Substring](https://en.wikipedia.org/wiki/Longest_common_substring_problem) of multiple strings by using a [Generalized Suffix Tree](https://en.wikipedia.org/wiki/Generalized_suffix_tree).

###### Usage

`./SuffixTree inputfile`

*inputfile* is a .txt file that contains the strings. The first line should always contain the total number of strings. All other lines should contain a single string.

The output of the program will be written to a .txt file called *lcs.txt*. The first line will contain the length of the longest common substring whereas the second line will contain the actual lcs itself. Following lines will contain the starting index of the lcs with respect to the current string. If no such lcs exists, *-1* will be the sole output of the file.

###### Example

For the given input file:

```
4
BANANA
ANA
NA
NAN
```

The program will output:

```
2
NA
2
1
0
0
```
