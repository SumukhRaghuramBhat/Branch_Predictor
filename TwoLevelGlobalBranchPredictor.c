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
    pc = strtok(line, " ");
    branch_takenNotTaken = strtok(NULL, " ");

    while(byte != -1) {

        if (*branch_takenNotTaken == 'T') {
            if (PHT[GHR] < 2) {
                misprediction++;
            }
            PHT[GHR]++;
			
            if (PHT[GHR] >= 3)
                PHT[GHR] = 3;

            GHR = (GHR<<1) |0x01;
            GHR = GHR & 0x0000003FF;
        }

        if (*branch_takenNotTaken == 'N'){
            if(PHT[GHR] >= 2){
                misprediction++;
            }
            PHT[GHR]--;
            if (PHT[GHR] <= 0)
                PHT[GHR] = 0;

            GHR = (GHR<<1) & 0x0000003FE;
            GHR = GHR & 0x0000003FF;
        }

        byte = getline(&line,&nb,tracefd);
        pc = strtok(line, " ");
        branch_takenNotTaken = strtok(NULL, " ");
        total++;

    }

    percent =  100*((float)misprediction)/((float)total);
    printf(" total misprediction: %ld\n",misprediction);
    printf(" total branches encountered: %ld\n",total);
    printf(" total percent of misprecition: %f\n\n",percent);

}