# Branch_Predictor

Implement a branch predictor that combine the benefits of Gshare and Two-Level Local Branch Predictor or even a new branch predictor that outperform Gshare and Two Level Local Branch Predictors.  

Explore the effectiveness of branch direction prediction (taken vs not taken) on an actual program. 
The trace is of 16 million conditional branches. These are the conditional branches from an execution of the program GCC (Gnu C Compiler) from the SPECint2000 benchmark suite. As unconditional branches are always taken, they are excluded from the trace. Each line of the trace file has two fields. Below are the first four lines of a trace file:

3086629576 T

3086629604 T

3086629599 N

3086629604 T

The first field is the address of the branch instruction. The second field is the character "T" or "N" for branch taken or not taken. 

    A) Assume 1K (1024) entry for Pattern History Table (PHT) with 2-bit Counter per entry (predictor index size of 2 bits), implement and compare the mis-prediction of the following branch predictors:
    One level branch Prediction
    Two Level Global Branch Prediction
    Two Level Gshare Branch Predictor
    Two Level Local Branch Prediction (assume 128 entry for Local History Register Table)

Plotting the mis-prediction results across branch predictions and analyze the achieved results.  

Varying the n-bit Counter, with size of 2 bits, 4 bits, 6 bits, 8 bits for Gshare and Two-Level Local Branch Predictors. 

Plotting the results over variable entry size (n-bit Counter) with size of 2 bits, 4 bits, 6 bits, 8 bits for Gshare and Two-Level Local Branch Predictors.

