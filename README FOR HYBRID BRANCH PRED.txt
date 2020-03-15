The Compilation is done by : gcc hybrid.c -o hybrid.o -lm 

With all recent versions of GCC on GNU/Linux systems like Ubuntu, when you use the math library, you have to explicitly link to it. 
It is not automatically linked to along with the rest of the standard C library.

Hence the linking is done usong -lm at the end of the gcc compile code.


Run using :  ./hybrid.o 

Output : 

Enter predictor size in bits : Press 2 for 2 bit Counter 
2
Hybrid Branch Predictor
Number of incorrect fetches: 1374238
Percentage misprediction rate: 8.371191
Percentage correct prediction rate : 91.628809

4
Hybrid Branch Predictor
Number of incorrect fetches: 1566229
Percentage misprediction rate: 9.540707
Percentage correct prediction rate : 90.459293

6
Hybrid Branch Predictor
Number of incorrect fetches: 1740850
Percentage misprediction rate: 10.604413
Percentage correct prediction rate : 89.395587

8
Hybrid Branch Predictor
Number of incorrect fetches: 1995131
Percentage misprediction rate: 12.153369
Percentage correct prediction rate : 87.846631



