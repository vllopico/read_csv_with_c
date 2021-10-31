#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define LLINEA 512

int main(void)
{
	clock_t  begin = clock();
	
    FILE* file = fopen("data.csv", "r");
    
    if(file == NULL) {
      printf("Error en el fitxer!");   
      exit(1);             
	}
	    
    char line[LLINEA];
    char *tok;
    char *endv;
    
    double valor;
    double vd;
    
    //Variables fila
    double sumfila = 0.0;
    double avgfila = 0.0;
    int elsfila;
    int numfila = 0;
    double maxfila = 0.0;
    double minfila = 0.0;
    
    
    //Variables totals
    double sumtotal = 0.0;
    double avgtotal = 0.0;
    int elstotal = 0;
    double maxtotal = 0.0;
    double mintotal = 0.0;
    
    printf("\n");
	printf("%-15s %-15s %-15s %-15s %-15s %-15s\n","Fila","Elements","Sumatori","Mitja","Max","Min");
	printf("=================================================================================================\n");
	
    while (fgets(line, sizeof(line), file)) {

		if(line[0] != '\r' && line[0] != '\n'){
	    	
			sumfila = 0.0;
	    	elsfila = 0;
	    	
			tok = strtok(line,";");
			
			valor = strtod(tok,&endv);
			if (tok != endv){
				
				maxfila = valor;
				minfila = valor;
			
				if (numfila == 0){
					maxtotal = maxfila;
					mintotal = minfila;
				}
			
				while (tok != NULL){
					valor = strtod(tok,&endv);
					if (tok != endv){
					
						elsfila = elsfila + 1;
						elstotal = elstotal + 1;
			
						sumfila = sumfila + valor;
						sumtotal = sumtotal + valor;
			
			
						if (valor > maxfila){
							maxfila = valor;
						}
						if (valor < minfila){
							minfila = valor;
						}
					}
					tok = strtok(NULL,";");
				}
			
				if (elsfila == 0){
					avgfila = 0.0;
				}
				else {
					avgfila = sumfila / elsfila;
				}
				printf("%-15d %-15d %-15f %-15f %-15f %-15f\n",numfila,elsfila,sumfila,avgfila,maxfila,minfila);
			}
		}
		
		if (maxfila > maxtotal){
			maxtotal = maxfila;
		}
		if (minfila < mintotal){
			mintotal = minfila;
		}
		
		numfila = numfila + 1;
		
    }
    if (elstotal == 0){
    	avgtotal = 0.0;
	}
	else {
		avgtotal = sumtotal / elstotal;
	}
    
    printf("=================================================================================================\n");
    
    printf("\nTOTALS\n\n");
    printf("%-15s %-15s %-15s %-15s %-15s %-15s\n","Files","Elements","Sumatori","Mitja","Max","Min");
	printf("=================================================================================================\n");
	printf("%-15d %-15d %-15f %-15f %-15f %-15f\n",numfila,elstotal,sumtotal,avgtotal,maxtotal,mintotal);
	printf("=================================================================================================\n");
    
    fclose(file);
    clock_t end = clock();
    double time_spent = (double)(end-begin) / CLOCKS_PER_SEC;
	printf("\nTEMPS SCRIPT: %lf segons\n", time_spent);
    
	return 0;
}
