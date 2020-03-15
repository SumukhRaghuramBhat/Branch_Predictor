#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main()
{	
	FILE *tracefd; 
	size_t byte, nb = 0,i;
	char *pc,*branch_takenNotTaken;
	int PC;
	char *line;
	long int misprediction = 0;
	long int total =0;
	float percent;
	 
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
			
		PC = (atoi(pc) & 0x0000003FF);

		if (*branch_takenNotTaken == 'T') {
		  
			if (PHT[PC] < 2) {
				misprediction++;
			}

			PHT[PC]++;
				if (PHT[PC] >= 3)
					PHT[PC] = 3;
		}

		if (*branch_takenNotTaken == 'N') {

			if(PHT[PC] >= 2) {
				misprediction++;
			}
			
			PHT[PC]--;
				if (PHT[PC] <= 0)
				PHT[PC] = 0;
		}
		
		byte = getline(&line,&nb,tracefd);       
		total++;
		
	}

	percent =  100*((float)misprediction)/((float)total);	
	printf(" total misprediction: %ld\n",misprediction);
	printf(" total branches encountered: %ld\n",total);
	printf(" total percent of misprediction: %f\n\n",percent);
}