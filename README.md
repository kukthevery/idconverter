idconverter
===========

IdConverter converts identifier which is sequence of tokens from next list
"A1, ..., Z9, A1-A1, A1-A2, ..., Z9-Z9" into output sequence
by followinng algorithm: if for example a token = "A9", it will be
converted to token "B1" and so on, if the token = "Z9" then it
will be converted to "A1-A1" and so on.
Notes:
a) not allowed digit 0 and characters "D", "F", "G", "J", "M", "Q", "V" in ids
b) max length of input id is 10 tokens of 2 symbols
