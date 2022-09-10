# -Numeration-systems
Numeration systems are used to discretize a data in a given base B. The information is first covert in binary then split into blocks of bits. Each block corresponds to a discrete value between 0 and B-1 in decimal.

Conversion in numeration systems is implemented in C language under the name numeration.c in the Linux environment.

We make use of the gmp library to handle large numbers at high precision. Before execution, two constants must be initialized: the secret and the base.

The compile command and the generation of the executable are as follows : gcc -o numeration numeration.c -lgmp -lm

The execution of the executable is done as follows : ./numeration

an example of execution gives this with secret="Data hiding" and BASE=64:

-------------------------------SECRET PROCESSING-------------------------------

[DEBUG] Processing the secret

"Data hiding"

[DEBUG] Secret in Binary : 0100010001100001011101000110000100100000011010000110100101100100011010010110111001100111

[DEBUG] Secret in decimal: 82667172103654312572972647

[DEBUG] Secret in base 64 : 39 57 22 26 36 37 6 26 32 4 6 29 33 17 4 

[DEBUG] Number of discrete values : 15  

------------------------------- END SECRET ROCESSING-------------------------------


-------------------------------SECRET EXTRACTION-------------------------------

[DEBUG] Secret in decimal = 82667172103654312572972647

[DEBUG] Secret in base 2, nbBits= 88 : 1110011001110110100101100010011010010110000101100000010010000110001011101000011000100010

[DEBUG] Secret : Data hiding

-------------------------------END SECRET EXTRACTION-------------------------------

The proposed code performs both base decomposition and then reconstitution of the secret. This code is used to color a text. In this example, we assume that we want to hide the secret "Data hiding" in a text. The conversion gives the following 15 discrete values: 39 57 22 26 36 37 6 26 32 4 6 29 33 17 4.

Considering that we have 64 colors varying from 0 to 63, it will be possible to color the first 15 characters of the text with the colors corresponding to the numbers obtained after conversion.
