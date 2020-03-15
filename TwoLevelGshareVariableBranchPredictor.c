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
    int  bits;
    int down_limit,up_limit;
    FILE *tracefd;
    int PHT[1023];

    for (bits = 2; bits <= 8; bits = bits + 2) {
		
        misprediction = 0;
        total =0;
        percent = 0;

        for(i = 0; i<=1023; i++) {
            PHT[i]=00;
        }

        tracefd = fopen("branch-trace-gcc.trace","r");

        if (tracefd == NULL) { 
			printf("file can not be opened");
			exit(1);
        }
        byte = getline(&line,&nb,tracefd);
        pc = strtok(line, " ");
        branch_takenNotTaken = strtok(NULL, " ");
        down_limit = (0x000000001 << (bits-1));
        up_limit = ((0x000000001 << bits) - 1);

        while(byte != -1) {

            if (*branch_takenNotTaken == 'T'){

                if (PHT[address] < down_limit){
                    misprediction++;
                }
                PHT[address]++;
                if (PHT[address] >= up_limit)
                    PHT[address] = up_limit;

                GHR = (GHR<<1) |0x01;

            }

            if (*branch_takenNotTaken == 'N'){

                if(PHT[address] >= down_limit){
                    misprediction++;
                }
                PHT[address]--;

                if (PHT[address] <= 0)
                    PHT[address] = 0;
                GHR = (GHR<<1) & 0xFFFFFFFE;

            }

            byte = getline(&line,&nb,tracefd);
            pc = strtok(line, " ");
            branch_takenNotTaken = strtok(NULL, " ");
            PC = atoi(pc);
            address = (PC) ^ (GHR);
            address = (address & 0x000003FF);
            total++;

        }

        percent =  100*((float)misprediction)/((float)total);
        printf(" \nBITS: %d percent:%f\n",bits,percent);
        fclose(tracefd);

    }
}