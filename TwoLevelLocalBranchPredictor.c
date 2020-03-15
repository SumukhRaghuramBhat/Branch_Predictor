#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    FILE *tracefd;
    size_t byte, nb = 0,i;
    char *pc,*branch_takenNotTaken;
    int PC = 0;
    char *line;
    long int misprediction = 0;
    long int total =0;
    float percent;
    int addr = 0;
    int LHR[128];
	int PHT[1023];

    for(i = 0; i<128; i++){
        LHR[i]=0x00000000;
    }

    for(i = 0; i<=1023; i++){
        PHT[i]=00;
    }

    tracefd = fopen("branch-trace-gcc.trace","r");

    if (tracefd == NULL){
        printf("file can not be opened");
        exit(1);
    }

    byte = getline(&line,&nb,tracefd);

    while(byte != -1){
        pc = strtok(line, " ");
        branch_takenNotTaken = strtok(NULL, " ");
        PC = (atoi(pc) & 0x0000007F);
        addr = LHR[PC];

        if (*branch_takenNotTaken == 'T'){
            if (PHT[addr] < 2){
                misprediction++;
            }
            PHT[addr]++;
            if (PHT[addr] >= 3)
                PHT[addr] = 3;

            LHR[PC] = (LHR[PC]<<1) | 0x00000001;
            LHR[PC] = LHR[PC] & 0x0000003FF;
            addr = LHR[PC];
        }

        if (*branch_takenNotTaken == 'N'){
            if(PHT[addr] >= 2){
                misprediction++;
            }
			
            PHT[addr]--;
			
			if (PHT[addr] <= 0)
                PHT[addr] = 0;

            LHR[PC] = (LHR[PC]<<1) & 0xFFFFFFFE;
            LHR[PC] = LHR[PC] & 0x0000003FF;
            addr = LHR[PC];
        }

        byte = getline(&line,&nb,tracefd);
        total++;
    }

    percent =  100*((float)misprediction)/((float)total);
    printf(" total misprediction: %ld\n",misprediction);
    printf(" total branches encountered: %ld\n",total);
    printf(" total percent of misprediction: %f\n\n",percent);

}