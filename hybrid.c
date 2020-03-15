#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#define Pa_hist_tb 2048

int funct(int value, char chrct, float n)
{
if(chrct == 'T')
{
if(value == (int)(pow(2,n)-1))
value = (int)(pow(2,n)-1);
else
value = value + 1;
}
else if(chrct == 'N')
{
if(value == 0)
value = 0;
else
value = value - 1;
}
return(value);
}
int main()
{
long int first[Pa_hist_tb], second[Pa_hist_tb], third[Pa_hist_tb];
FILE *trace;
size_t read, bits = 0;
long int addr, addr1, addr2, addr3, addr4, addr5;
char chrct;
long int value = 0;
bool bit1 = 0, bit2 = 0;
long int correct = 0, incorrect = 0, incorrect1 = 0, incorrect2 = 0, sum = 0;
float percent = 0, percent1 = 0, percent2 = 0;
char *line;
long int Gl_hist_tb;
long int Lo_hist_tb[Pa_hist_tb];
float counter_value;
trace = fopen("branch-trace-gcc.trace", "r");
if (ferror(trace)) {
printf("File not available");
exit(1);
}
printf("Enter predictor size in bits : Press 2 for 2 bit Counter \n");
scanf("%f", &counter_value);
memset(Lo_hist_tb, 0, sizeof Lo_hist_tb);
memset(first, 0, sizeof first);
memset(second, 0, sizeof second);
memset(third, 0, sizeof third);
read = getline(&line,&bits,trace);
while(read != -1)
{
fscanf(trace, "%ld %c", &addr, &chrct);
addr1 = addr & 0x000003FF;
addr2 = addr & 0x0000007F;
addr4 = Lo_hist_tb[addr1] & 0x000003FF;
if(chrct == 'T')
{
if(first[addr4] < (int)pow(2,counter_value)/2)
{
incorrect1++;
bit1 = 1;
}
first[addr4] = funct(first[addr4], chrct, counter_value);
Lo_hist_tb[addr1] = Lo_hist_tb[addr1] & 0xFFFFFFFF;
Lo_hist_tb[addr1] = Lo_hist_tb[addr1] << 1;
Lo_hist_tb[addr1] = Lo_hist_tb[addr1] + 1;
Lo_hist_tb[addr1] = Lo_hist_tb[addr1] & 0xFFFFFFFF;
addr4 = Lo_hist_tb[addr1] & 0x000003FF;
}
if(chrct == 'N')
{
if(first[addr4] >= (int)pow(2,counter_value)/2)
{
incorrect1++;
bit1 = 1;
}
first[addr4] = funct(first[addr4], chrct, counter_value);
Lo_hist_tb[addr1] = Lo_hist_tb[addr1] & 0xFFFFFFFF;
Lo_hist_tb[addr1] = Lo_hist_tb[addr1] << 1;
Lo_hist_tb[addr1] = Lo_hist_tb[addr1] + 0;Lo_hist_tb[addr1] = Lo_hist_tb[addr1] & 0xFFFFFFFF;
addr4 = Lo_hist_tb[addr1] & 0x000003FF;
}
if(chrct == 'T')
{
if(second[addr3] < (int)pow(2,counter_value)/2)
{
incorrect2++;
bit2 = 1;
}
second[addr3] = funct(second[addr3], chrct, counter_value);
Gl_hist_tb = Gl_hist_tb & 0xFFFFFFFF;
Gl_hist_tb = Gl_hist_tb << 1;
Gl_hist_tb = Gl_hist_tb + 1;
Gl_hist_tb = Gl_hist_tb & 0xFFFFFFFF;
addr5 = Gl_hist_tb ^ addr;
addr5 = addr5 & 0x000003FF;
addr3 = addr5;
}
if(chrct == 'N')
{
if(second[addr3] >= (int)pow(2,counter_value)/2)
{
incorrect2++;
bit2 = 1;
}
second[addr3] = funct(second[addr3], chrct, counter_value);
Gl_hist_tb = Gl_hist_tb & 0xFFFFFFFF;
Gl_hist_tb = Gl_hist_tb << 1;
Gl_hist_tb = Gl_hist_tb + 0;
Gl_hist_tb = Gl_hist_tb & 0xFFFFFFFF;
addr5 = Gl_hist_tb ^ addr;
addr5 = addr5 & 0x000003FF;
addr3 = addr5;
}
if(bit1 == 1)
{
if(bit2 == 0)
{
if(third[addr2] < (int)pow(2,counter_value)/2)
incorrect2++;
third[addr2] = funct(third[addr2], chrct, counter_value);
}
bit1 = 0;
bit2 = 0;
}
else if(bit1 == 0)
{
if(bit2 == 1)
{
if(third[addr2] >= (int)pow(2,counter_value)/2)
incorrect++;
third[addr2] = funct(third[addr2], chrct, counter_value);
}bit1 = 0;
bit2 = 0;
}
read = getline(&line,&bits,trace);
sum++;
}

printf("Hybrid Branch Predictor\n");
printf("Number of incorrect fetches: %ld\n", incorrect);
percent = (float)((float)incorrect/(float)sum)*100;
printf("Percentage misprediction rate: %f\n", percent);
printf("Percentage correct prediction rate : %f\n", 100.00-percent);
}
