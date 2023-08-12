#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <time.h>
#include <sys/resource.h>


void Gerador(double **A, double *b, int n)
{
	int i, j; 
	
	srand((unsigned)time(NULL)); //para mudar a semente 
	
	//gerador de números aleatórios 
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			A[i][j] = rand() % 3; 
			
			/*A[0][0] = 1; 
      			A[0][1] = 0; 
      			A[0][2] = 0; 		//Essa parte é para verificar a solução para o caso trivial. 
      			A[1][0] = 0; 
     			A[1][1] = 1; 
     			A[1][2] = 0; 
      			A[2][0] = 0; 
      			A[2][1] = 0; 
      			A[2][2] = 1;*/
      			
			b[i] = rand() % 2;  
		}
	
	}
}

void copia_matriz(double **origem, double **destino, int n)
{
	int i, j;
   
    	//Cópia da Matriz
    	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			destino[i][j] = origem[i][j];
		}
	}

}

void imprime_vetor(double *v, int n)
{
	int i, j;

	for(i=0; i<n; i++)
	{
		printf("%lf\n", v[i]);
	}	
	
	printf("\n");

}

void imprime_matriz(double **matriz, int n)
{
	int i, j; 
		
	//imprimindo matriz	
    	for (i = 0; i<n; i++) 
	{
		for (j = 0; j<n; j++) 
		{
            		printf("%lf\t", matriz[i][j]);
            	}
        	printf("\n");
	}
}


int determinante(double **B, int n, int m) 
{
    
    	if (n != m) 
    	{
        	printf("Erro! A matriz não é quadrada\n");
        	exit(1);
    	}

    	if (n == 1)
        	return B[0][0];

    	else if (n == 2)
        	return (B[0][0] * B[1][1]) - (B[1][0] * B[0][1]);

    	else 
    	{
        	double **menor;
        	int linha_menor, coluna_menor;
        	int primeira_linha; 
        	int sum = 0;
  
        	menor = malloc((n - 1) * sizeof(double*));
        	for (int i = 0; i < n - 1; i++)
        	    menor[i] = malloc((m - 1) * sizeof(double));
  
        	for (primeira_linha = 0; primeira_linha < n; primeira_linha++) 
        	{
        	    linha_menor = 0;
        	    for (int linha = 1; linha < n; linha++) 
        	    {
        	        coluna_menor = 0;
        	        for (int coluna = 0; coluna < m; coluna++) 
        	        {
        	            if (coluna == primeira_linha)
        	                continue;
        	            menor[linha_menor][coluna_menor] = B[linha][coluna];
        	            coluna_menor++;
        	        }
                	
                	linha_menor++;
            	    }
            
            		int menor_n = n - 1;
            		int menor_m = m - 1;
            		
            		if (primeira_linha % 2 == 0)
                		sum += B[0][primeira_linha] * determinante(menor, menor_n, menor_m);
            		else
               	sum -= B[0][primeira_linha] * determinante(menor, menor_n, menor_m);

       	}
	
        return sum;
        free(menor);
    }
}

  

int testeLI(double **A, int n, int m)
{	
	
	if(determinante(A, n, n) != 0)
	{
	
																			
		printf("\n\n\n\nOs vetores coluna são linearmente independentes, podemos utilizar o processo de Gram-Schmidt para obter a Decomposição QR!\n\n\n");
		
		return 0;
 
	}

    	else if(determinante(A, n, m) == 0)
    	{
    		printf("\nOs vetores coluna são linearmente dependentes, pois o determinante é %d.\n", determinante(A, n, m));
    		printf("\n----------NÃO É POSSÍVEL OBTER DECOMPOSIÇÃO QR PARA A MATRIZ-----------\n"); 
    		
    		exit(0); 
    	}

}

int transposta(double **A, double **T, int n)
{
	int i, j;

	
	//calculando transposta
	for(i=0;i<n;i++)
	{	
		for(j=0;j<n;j++)
		{
			T[j][i] = A[i][j];
		}
	}

}

//função que calcula o vetor y=(Q^t)b
void produto_vetor(double **QTransposta, double *b, double *y, int n)
{
	int i, j;
	double soma=0.0; 
    
    
	for(i=0; i<n; i++)
	{   
		soma=0.0; 
		for(j=0; j<n; j++)
        	{
            		soma += QTransposta[i][j] * b[j]; 
       	}
       	
        	y[i] = soma; 
    	}
    
}

//soluciona o sistema liner Rx=y (A é a matriz aumentada, o vetor b é a última coluna dessa matriz) 

void substituicao_regressiva(double **M, int m, double *b, double *y) 
{
	double sum;
	int i, j;

	//y = malloc(m * sizeof(double));

	for (i = m - 1; i >= 0; i--) {
		sum = 0;
		for (j = i + 1; j <= m - 1; j++)
			sum += M[i][j] * y[j];

		y[i] = (b[i] - sum) / M[i][i];
	}
		
	
}

void VerificaResultado(double **M, double *resultado, double *vetorB, int m)
{
  
  	int i, j;
  	double soma = 0, *provaReal;
  
  	provaReal = (double *)malloc(m*sizeof(double));
  
  	for(j = 0; j < m; j++)
  	{
    
    		for(i = 0; i < m; i++)
      			soma += M[j][i]*resultado[i];
    
    		provaReal[j] = soma;
    		soma = 0;
  	}
  
  	for(i = 0; i < m; i++)
    		soma += provaReal[i] - vetorB[i];

  	if(soma > 3)
    		printf("\n\nResultado Errado \n");
    
  	else
  	{
    		printf("\n\nCorreto, pois: \n");
    		imprime_vetor(provaReal, m);
    
  	}
  
}


void decomposicaoQR(double **a, double **q, double **r, int n)
{
	int i, j, k; 
	double norma; 
	
	

	for(k=0; k<n; k++)
	{
		r[k][k]=0; 
		
		
		
		for(i=0; i<n; i++)
		{
			r[k][k] = r[k][k] + a[i][k] * a[i][k];
		}
		
		r[k][k] = sqrt(r[k][k]); 	
		
		
		for(i=0; i<n; i++)
			q[i][k] = a[i][k]/r[k][k]; 		
		
		
		for(j=k+1; j<n; j++)
		{
			r[k][j] = 0;
			
			for(i=0; i<n; i++)
				r[k][j] += q[i][k] * a[i][j]; 			
			
			
			for(i=0; i<n; i++)
				a[i][j] = a[i][j] - r[k][j]*q[i][k];
		}
	}
	
			
}


void produto_matriz(double **QR, double **q, double **r, int n)
{
	int i, j, k; 
	double soma = 0;
	
	
	

	for (i=0; i<n; i++) 
	{
        	for (j=0; j<n; j++) 
        	{
           		 soma = 0;
           		
           		 for (k=0; k<n; k++)
           		 {
               	 	soma += q[i][k] * r[k][j];
               	 }
               	 QR[i][j] = soma  ;        	
               }
	}
}


void verifica_solucao(double **A, double *x, double *resultado_Ax, int n)
{
	int i, j;
	double soma=0.0; 
    
    
	for(i=0; i<n; i++)
	{   
		soma=0.0; 
        
        	for(j=0; j<n; j++)
        	{
            		soma += A[i][j] * x[j]; 
        	}
        
        	resultado_Ax[i] = soma; 
    	}
    
}

void residuo(double *resultado_Ax, double *b, double *vetor_residuo, int n)
{

	int i;
	 	
	for(i=0; i<n; i++)
	{
		//printf("ax: %lf\n", resultado_Ax[i]);
		vetor_residuo[i] = fabs(resultado_Ax[i] - b[i]); 
		//printf("b: %lf\n", b[i]); 
		//printf("residuo: %lf\n", vetor_residuo[i]); 
	}
	
	 
}


void main(int argc, char **argv)
{
	int  i, j, n=4, det=1; 
	
	double **A, **A_copia,**QTransposta, **Q, **R, **QR, **I; 
	double *b, *x, *y, *resultado_Ax, *vetor_residuo; 
	int z; 
	
	struct timespec begin, end;
	double elapsed;
	long seconds, nanoseconds;
	
		
    	b = malloc(n * sizeof(double)); //alocando memoria para o vetor b
	x = malloc(n * sizeof(double)); //alocando memoria para o vetor solução
	y = malloc(n * sizeof(double)); //alocando memoria para o vetor b
	resultado_Ax = malloc(n * sizeof(double)); //alocando para o vetor Ax
	vetor_residuo = malloc(n * sizeof(double)); 
	
	
	
	A = malloc(n * sizeof(double*)); //alocando linhas da matriz 
	for(i=0; i<n; i++)
		A[i] = malloc (n * sizeof(double)); //alocando colunas da matriz 
	
		
	A_copia = malloc(n * sizeof(double*)); //alocando linhas da matriz 	
	for(i=0; i<n; i++)
		A_copia[i] = malloc (n * sizeof(double)); //alocando colunas da matriz 
	
	
	QTransposta = malloc(n * sizeof(double*)); 
	for(i=0; i<n; i++)
		QTransposta[i] = malloc (n * sizeof(double)); //alocando colunas da matriz 
    	
    	  	
       Q = malloc(n * sizeof(double*)); //alocando linhas da matriz 
	for(i=0; i<n; i++)
		Q[i] = malloc (n * sizeof(double)); //alocando colunas da matriz 
    	
    	R = malloc(n * sizeof(double*)); //alocando linhas da matriz 
	for(i=0; i<n; i++)
		R[i] = malloc (n * sizeof(double)); //alocando colunas da matriz 
    	
    	
    	QR = malloc(n * sizeof(double*)); //alocando linhas da matriz 
	for(i=0; i<n; i++)
		QR[i] = malloc (n * sizeof(double)); //alocando colunas da matriz 
    	
    	
    	I = malloc(n * sizeof(double*)); //alocando linhas da matriz 
	for(i=0; i<n; i++)
		I[i] = malloc (n * sizeof(double)); //alocando colunas da matriz 
    	
    	 
	clock_gettime(CLOCK_REALTIME,&begin);
    	Gerador(A, b, n); //gera a matriz A e o vetor b 
    	
    	
    	//printf("\n\n--------------------MATRIZ A------------------------------\n\n");
    	//imprime_matriz(A, n); //imprimindo matriz A inicial
    	copia_matriz(A, A_copia, n);
    	
    	    	
    	testeLI(A, n, n) ;  //testa se os vetores coluna são LI. 
	
	//printf("\n\n--------------------------DECOMPOSIÇÃO QR---------------------------------\n\n"); 		
	decomposicaoQR(A, Q, R, n); //obtém a decomposição QR para a matriz A
	produto_matriz(QR, Q, R, n); //faz o produto de Q por R	
	//printf("\n\nmatriz QR: \n\n"); 
	//imprime_matriz(QR, n); //pra verificar se é igual a matriz A
	//printf("\n\nmatriz R: \n\n");
	//imprime_matriz(R, n);
	//printf("\n\nmatriz Q: \n\n");
	//imprime_matriz(Q, n);	
	
		
	transposta(Q, QTransposta, n); 	
	//produto_matriz(I,QTransposta, Q, n); //verificando de Q^tQ = I
	//printf("\n\n--------------------------Matriz identidade--------------------------: \n\n"); 	
	//imprime_matriz(I, n); 
	produto_vetor(QTransposta, b, y, n); //calcula o vetor y = (Q^t)
	//printf("\n\n\n--------------------------vetor y--------------------------\n\n\n"); 
	//imprime_vetor(y, n);
	substituicao_regressiva(R, n, y, x); //soluciona o sistema linear Rx=y
		
	
	
	//printf("\n\n-----------------------Solução do sistema linear após a Decomposição QR (vetor x)-----------------------------\n\n"); 
	//imprime_vetor(x, n);
	
		
	
	//printf("\n\n--------------------------PRODUTO Ax---------------------------------\n\n"); 
	verifica_solucao(A_copia, x, resultado_Ax, n); //faz o produto de A pelo vetor solução x
	//imprime_vetor(resultado_Ax, n); 
	
	
	
	//printf("\n\n--------------------------VETOR b---------------------------------\n\n"); 
	//imprime_vetor(b, n); 
	
	
	
	printf("\n\n--------------------------VETOR RESÍDUO (|Ax - b|)---------------------------------\n\n"); 
	residuo(resultado_Ax, b, vetor_residuo, n); 
	imprime_vetor(vetor_residuo, n); 
	
	//printf("\n\nverifica solução: \n\n");
	//VerificaResultado(A_copia, x, b, n);
	    	
   	
   	
   	
   	free(A);
   	free(A_copia);
   	free(QTransposta);
   	free(Q);
   	free(R);
   	free(QR);
   	free(b);
   	free(x);
   	free(y);
   	free(resultado_Ax);
   	free(vetor_residuo); 
   
}


