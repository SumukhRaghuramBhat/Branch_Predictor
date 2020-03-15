#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    size_t byte, nb = 0,i;
    char *pc,*branch_takenNotTaken;
    int PC;
    char *line;
    long int misprediction = 0;
    long int total =0;
    float percent;
    int GHR = 0x0000000000;
    int address = 0;
    FILE *tracefd;
    int PHT[1023];

    for(i = 0; i<=1023; i++) {
        PHT[i]=00;
    }

    tracefd = fopen("branch-trace-gcc.trace","r");

    if (tracefd == NULL) { 
		printf("file can not be opened");
		exit(1);
    }
    byte = getline(&line,&nb,tracefd);

    while(byte != -1) {
		
        pc = strtok(line, " ");
        branch_takenNotTaken = strtok(NULL, " ");
        PC = atoi(pc);
        address = (PC) ^ (GHR);
        address = (address & 0x000003FF);

        if (*branch_takenNotTaken == 'T'){

            if (PHT[address] < 2){
                misprediction++;
            }
            PHT[address]++;
            if (PHT[address] >= 3)
                PHT[address] = 3;

            GHR = (GHR<<1) |0x01;

        }

        if (*branch_takenNotTaken == 'N'){

            if(PHT[address] >= 2){
                misprediction++;
            }
            PHT[address]--;

            if (PHT[address] <= 0)
                PHT[address] = 0;
            GHR = (GHR<<1) & 0xFFFFFFFE;

        }

        byte = getline(&line,&nb,tracefd);
        total++;

    }

    percent =  100*((float)misprediction)/((float)total);
    printf(" total misprediction: %ld\n",misprediction);
    printf(" total branches encpuntered: %ld\n",total);
    printf(" total percent of misprediction: %f\n\n",percent);

}