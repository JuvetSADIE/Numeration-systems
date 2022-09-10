/* Includes */
#include <stdio.h>      /* For printf() */
#include <string.h>      /* For memcpy() */
#include <gmp.h>	/* For gmp_xxx big number */

#define NB_MAX_DATA 10000
#define NB_BIT_Max 10000
#define BASE 64
#define N 10
//#define NbMaxFichier 100
char nomFichier[15]="debug.txt";

char secret[1000]="Data hiding";

int decompositionEnBase2(int decomposition[NB_BIT_Max], mpz_t a){
	unsigned long int bas=2, mod;
	int i=-1;
	mpz_t zero;   //declaration of big numbers
	mpz_t b;
	mpz_t q;  
	mpz_t r;
	mpz_init( zero );   //  initialisation
	mpz_init( b );
	mpz_init( q );   //  initialisation
	mpz_init( r );
	mpz_set_ui (b , bas );
	mpz_set_ui (zero , 0 );

	do{
	 
	  // compute division a/b ( a = q * b + r )    
	    mpz_fdiv_qr( q, r, a, b );
	  //printf("\n%s %s %s %s\n", mpz_get_str (NULL, 10, q),mpz_get_str (NULL, 10, r),mpz_get_str (NULL, 10, a),mpz_get_str (NULL, 10, b));

	    mod = mpz_get_ui(r);    
	    decomposition[++i]= (int)mod;
	    //printf("\ni=%d",i);
	    mpz_set(a, q); 
	    
	}while(mpz_cmp(q,zero)!=0);
	// clean memory
	  mpz_clear( a );
	  mpz_clear( b );
	  mpz_clear( q );
	  mpz_clear( r );
	  mpz_clear( zero );
	while((i%8) != 0){
          decomposition[++i]=0;
	}
	return (i);
}

void printChaine2(int chaine[NB_BIT_Max], int index){
	int i;

	for(i=0;i<index;i++){
	      printf("%d",chaine[i]);
	    }
}

int decimalValue(int reconstruction[NB_MAX_DATA], int nbFichier, int decomposition[NB_BIT_Max]){
	mpz_t i, puis, base, val, prod; 
	long int j;
	//char chaine[400];
	int nbBits;
	mpz_init (i);   
	mpz_init (puis);
	mpz_init (base);
	mpz_init (val);
	mpz_init (prod);

	mpz_set_ui (base,1);  	 
	mpz_set_ui (i,0);
	mpz_set_ui (val,0); 
	mpz_set_ui (prod,1);    

	   
	mpz_set_ui (puis,nbFichier);
	j=0;
	while(j<nbFichier){
		//c = chaine[j];
		
		  mpz_mul_ui(prod, base, reconstruction[j]); 	
	       
		mpz_add(val,val,prod);
		//printf("\ni= %s puis= %s base=%s random=%d prod= %s val= %s",mpz_get_str (NULL, 10, i), mpz_get_str (NULL, 10, puis),
				//mpz_get_str (NULL, 10, base),randomValue,mpz_get_str (NULL, 10, prod),mpz_get_str (NULL, 10, val));
		mpz_mul_ui(base, base, BASE); 	
		//mpz_add_ui(i, i, 1); 
		j++;
		//printf("\n[DEBUG] Secret = %s\n", mpz_get_str (NULL, 10, val));
	}
	printf("\n[DEBUG] Secret in decimal = %s", mpz_get_str (NULL, 10, val));
	nbBits = decompositionEnBase2(decomposition,val);

	printf("\n[DEBUG] Secret in base 2, nbBits= %d : ", nbBits);
	printChaine2(decomposition, nbBits);
	//printf("\n[DEBUG] Secret in base %d : nbFichier=%d", BASE, nbFichier);
	return nbBits;
}


void binaryToChar(int decomposition[NB_BIT_Max], int nbBits){
	int i, puis=0, val;
	
	while(nbBits >0){
	    val=0;
	    puis=1;
	    for(i=8;i>0;i--){
	      val += decomposition[nbBits-i] * puis;
	      puis = puis*2;
	    }
	    nbBits = nbBits - 8;
	    printf("%c", val);
	}

}
void decoding(int reconstruction[NB_MAX_DATA], int nbFichier){
	int chaine[NB_BIT_Max];
	int nbBits;
	int decomposition[NB_BIT_Max];   
	/*reconstruction[0]=778 ;
	reconstruction[1]=795;
	reconstruction[2]=710;
	reconstruction[3]=405;
	reconstruction[4]=104;
	nbFichier=5;*/
	printf("\n-------------------------------SECRET EXTRACTION-------------------------------");
	nbBits = decimalValue(reconstruction, nbFichier,decomposition);
	printf("\n[DEBUG] Secret : ");
	binaryToChar(decomposition, nbBits);
	printf("\n-------------------------------SECRET EXTRACTION-------------------------------");
}


//-----------------------------------------------------------------------------------------------------------------------------------
void charToBinary(char nombre, int reste[8]){
	FILE* fichier;
	int i,j,a,b,r,q;
	a=nombre;
	b=2;
	i=8;
	r=a%b;
	q=a/b;
	reste[--i]=r;
	//printf("%d",r);
	while(q!=0){
		a=q;
		q=a/b;
		r=a%b;
		reste[--i]=r;
		//printf("%d",r);
	}
	if(i>0){
		for(j=0;j<i;j++){
			reste[j]=0;
			//printf("0");
		}
	}

	fichier = fopen(nomFichier, "a+");
	if (fichier == NULL)    {
	  /* Drop error message */
	  perror("fopen()");
	  /* Return with error */
	}else{
	  fprintf(fichier, "\n%c = ", nombre);
	  for(j=0;j<8;j++){
		fprintf(fichier, "%d", reste[j]);	
	  } 
	fclose(fichier);
	}
}

void printChaine(int chaine[NB_BIT_Max], int index){
	int i;
//printf("\n nombre de bits : %d\n", index+1);
	for(i=0;i<=index;i++){
	      printf("%d",chaine[i]);
	    }
}


int decompositionEnBase(int decomposition[NB_MAX_DATA], mpz_t a){
	unsigned long int bas=BASE, mod;
	int i=-1, sizeMax=0;
	mpz_t zero;   // Déclare deux variables grands entiers.
	mpz_t b;
	mpz_t q;  // Déclare deux autres  variables "grands entiers".
	mpz_t r;
	mpz_init( zero );   // Les initialise (nécessaire)
	mpz_init( b );
	mpz_init( q );   // Les initialise (nécessaire)
	mpz_init( r );
	mpz_set_ui (b , bas );
	mpz_set_ui (zero , 0 );

	do{
	 
	  // Calcule la division de a par b ( a = q * b + r )    
	    mpz_fdiv_qr( q, r, a, b );
	  //printf("\n%s %s %s %s\n", mpz_get_str (NULL, 10, q),mpz_get_str (NULL, 10, r),mpz_get_str (NULL, 10, a),mpz_get_str (NULL, 10, b));

	    mod = mpz_get_ui(r);    
	    decomposition[++i]= (int)mod;
	    sizeMax+=mod;
	    //printf("\ni=%d",i);
	    mpz_set(a, q); 
	    
	}while(mpz_cmp(q,zero)!=0);
	//printf("\n[DEBUG] Min file size: %d", sizeMax);
	// Libère la mémoire
	  mpz_clear( a );
	  mpz_clear( b );
	  mpz_clear( q );
	  mpz_clear( r );
	  mpz_clear( zero );
	return (i+1);
}

int convertToDecimal(int chaine[NB_BIT_Max], int nbits, int decomposition[NB_MAX_DATA], int b){
    
    mpz_t i, puis, base, val, prod;
    //unsigned long int op=2;
    FILE* fichier;
    int nbFichier;
    char caractereActuel,c;
    long int pos,j;
    int randomValue,n;
    //char chaine[400];

    mpz_init (i);   
    mpz_init (puis);
    mpz_init (base);
    mpz_init (val);
    mpz_init (prod);

    mpz_set_ui (base,1);  	 
    mpz_set_ui (i,0);
    mpz_set_ui (val,0); 
    mpz_set_ui (prod,1);    
   
   
	//printf("Entrer la chaine binaire :  ");
        //scanf("%s", chaine);
        //nbits = strlen(chaine);
        //printf("n=%ld", nbits);
	mpz_set_ui (puis,nbits);
        j=nbits;
        while(j>=0){
                //c = chaine[j];
                if(chaine[j]==1)		
		  mpz_mul_ui(prod, base, 1); 	
                else
		  mpz_mul_ui(prod, base, 0);	
		mpz_add(val,val,prod);//i++
		//printf("\ni= %s puis= %s base=%s random=%d prod= %s val= %s",mpz_get_str (NULL, 10, i), mpz_get_str (NULL, 10, puis),
				//mpz_get_str (NULL, 10, base),randomValue,mpz_get_str (NULL, 10, prod),mpz_get_str (NULL, 10, val));
		mpz_mul_ui(base, base, b); 	
		//mpz_add_ui(i, i, 1); 
                j--;
	}
	printf("\n[DEBUG] Secret in decimal: %s", mpz_get_str (NULL, 10, val));
   
	

	//printf("\n[DEBUG] Secret in base %d : nbFichier=%d", BASE, nbFichier);
	fichier = fopen(nomFichier, "a+");
	if (fichier == NULL)    {
	  /* Drop error message */
	  perror("fopen()");
	  /* Return with error */
	}else{
	  //gmp_fprintf(fichier, , mpz_get_str (NULL, 10, val));
	  gmp_fprintf(fichier, "\n[DEBUG] Secret in decimal: "); mpz_out_str (fichier , 10 , val); 
	fclose(fichier);
	}
	
	nbFichier = decompositionEnBase(decomposition, val);
        return nbFichier;
}

void printInBase(int decomposition[NB_MAX_DATA], int nbFichier){
	FILE* fichier;	
	int i;
	fichier = fopen(nomFichier, "a+");
	if (fichier == NULL)    {
	  /* Drop error message */
	  perror("fopen()");
	  /* Return with error */
	}else{
	  fprintf(fichier, "\n[DEBUG] Secret in base %d :", BASE);
	  for(i=0;i<nbFichier;i++){
	      printf("%d ",decomposition[i]);
	      fprintf(fichier, "%d ", decomposition[i]);
	}
	fclose(fichier);
	}

	}



void  encoding(){
	FILE* fichier;
	char caractereActuel;
	int index=-1,i,j;
	int reste[8];
	int chaine[NB_BIT_Max];
	int decomposition[NB_MAX_DATA], nbFichier;
	int reconstruction[NB_MAX_DATA];
	int nbBits;
	
	int binair[NB_BIT_Max]; 

	//Secret secret;
	printf("-------------------------------SECRET PROCESSING-------------------------------\n");
	printf("[DEBUG] Processing the secret\n");
	/*fichier = fopen("secret.txt", "r");
	if (fichier == NULL)    {
	  
	  perror("fopen()");
	 
	}else{

	printf("[DEBUG] Secret Message : ");
	do{	     
	  caractereActuel = fgetc(fichier); // On lit le caractère
	  if(caractereActuel != -1){
	    printf("%c",caractereActuel); 
	    charToBinary(caractereActuel, reste);
	    for(i=0;i<8;i++){
	      chaine[++index] = reste[i];
	    }
	  }
	}while (caractereActuel != EOF); 
	fclose(fichier);
	*/
	
	for(j=0;j<strlen(secret);j++){
	  if(secret[j] != -1){
	    printf("%c",secret[j]); 
	    charToBinary(secret[j], reste);
	    for(i=0;i<8;i++){
	      chaine[++index] = reste[i];
	    }
	  }
        }
	
	printf("\n[DEBUG] Secret in Binary : ");	
	printChaine(chaine, index);

	nbFichier = convertToDecimal(chaine, index, decomposition, 2);

	printf("\n[DEBUG] Secret in base %d : ", BASE);
	printInBase(decomposition, nbFichier);

	printf("\n[DEBUG] Number of discrete values : %d  \n", nbFichier);
	//memcpy( secret.data_size, decomposition, sizeof( int ) * nbFichier );
	//secret.index = nbFichier;
	
	printf("------------------------------- END SECRET ROCESSING-------------------------------\n");

	printf("\n\n\n-------------------------------SECRET EXTRACTION-------------------------------");
	nbBits = decimalValue(decomposition, nbFichier,binair);
	printf("\n[DEBUG] Secret : ");
	binaryToChar(binair, nbBits);
	printf("\n-------------------------------END SECRET EXTRACTION-------------------------------\n\n");
}



int main(int argc, const char **argv) {

	encoding();
	return 1;
}

