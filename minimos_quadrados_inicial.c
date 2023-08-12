#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <math.h> 

#define n 3

void Gerador(double A[n][n], double b[n])
{
	int i, j; 
	
	for(i=0; i<n; i++) //gerador de numeros aleatorios 
	{
		for(j=0; j<n; j++)
		{
			A[i][j] = rand() % 5; 
			b[i] = rand() % 5; 
			
		}
	}
}

void matriz_aumentada(double Au[n][n+1], double A[n][n], double b[n])
{
	int i,j;
	
	for(i=0; i<n; i++)
	{
		for(j=0; j<n+1; j++)
		{
			
			if(j == n)
				Au[i][j] = b[i];
			
			else
				Au[i][j] = A[i][j]; 		
			   
		}
	}
	return;			
}


void copia_aumentada(double origem[n][n+1], double destino[n][n+1])
{
	int i, j;
   
    	//Copia da Matriz
    	for(i=0; i<n; i++)
	{
		for(j=0; j<n+1; j++)
		{
			destino[i][j] = origem[i][j];
		}
	}

}

void copia(double origem[n][n], double destino[n][n])
{
	int i, j;
   
    	//Copia da Matriz
    	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			destino[i][j] = origem[i][j];
		}
	}

}

//calcula o determinante
int determinante(double aux[n][n+1], int det)
{
	int i, j;
	
	//calculo do determinante
	for(i=0; i<n; i++)
	{
		det = det * aux[i][i];
	}
	
	return(det); 
}

int testeLI(double A[n][n+1], int det)
{	
		
	if(determinante(A, det) != 0)
	{
	
																			
		printf("\n\n\n\nOs vetores coluna sao linearmente independentes, podemos utilizar o processo de Gram-Schmidt para obter a Decomposicao QR!\n\n\n");
		
		return 0;
 
	}

    	else if(determinante(A, det) == 0)
    	{
    		printf("\nOs vetores coluna nao sao linearmente dependentes, pois o determinante e %d\n.", det);
    		printf("\n----------NAO E POSSIVEL OBTER DECOMPOSICAOO QR PARA A MATRIZ-----------\n"); 
    		
    		exit(0); 
    	}

}

int transposta(double A[n][n], double T[n][n])
{
	int i, j;

	//Copia da Matriz
	//copia(A, T);
 
	//calculando transposta
	for(i=0;i<n;i++)
	{	
		for(j=0;j<n;j++)
		{
			T[j][i] = A[i][j];
		}
	}

}


void imprime_aumentada(double Matriz[n][n+1])
{
	int i, j;

	for(i=0; i<n; i++)
	{
		printf("\n");
	
		for(j=0; j<n+1; j++)
		{
			printf("%lf\t", Matriz[i][j]);

		}
	}
	
	printf("\n");

}


void imprime_vetor(double v[n])
{
	int i, j;

	for(i=0; i<n; i++)
	{
		printf("%lf\n", v[i]);
	}	
	
	printf("\n");

}

//utilizo o metodo de Gauss Pivoteado na decomposicao LU para obter uma matriz triangular superior
void gauss_pivoteado(double aumentada[n][n+1], double l[n][n])
{

	int i, j, p, k; 
	double diagonal, troca; 
	
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			l[i][j] = 0;
		}
	}
	
	for(i=0; i<n; i++)
	{
		if(aumentada[i][i] == 0)
		{
			p = i; 
			
			do
			{
				p++; 
			}while((aumentada[p][i] == 0) & (p<n)); 
			
			for(k=0; k<n+1; k++)
			{
				troca = aumentada[i][k]; 
				aumentada[i][k] = aumentada[p][k];
				aumentada[p][k] = troca; 	
			}
			
			if (aumentada[i][i] == 0)
			{
				printf("Sistema sem solucao"); 
				exit(1); 
			}
			
			for(j=i; j<n+1; j++)
			{
				if(j==i)
				{
					diagonal = aumentada[i][i]; 
				}
				
				aumentada[i][j] = aumentada[i][j] / diagonal; 
			}
	
		}
		
		else
		{
			for(j=i; j<n+1; j++)
			{
				if(j==i)
				{
					diagonal = aumentada[i][i]; 
				}
				
				aumentada[i][j] = aumentada[i][j] / diagonal; 
			}
		}
		
		
		for(k=i;k<n;k++)
			for(j=i;j<n+1;j++)
				if(j<=k)
					l[k][j] = aumentada[k][i]; 
		for(k=i+1;k<n; k++)
		{

			for(j=i; j<n+1; j++)
			{
				if(j==i)
				{	
					
					diagonal = aumentada[k][i]; 		
				}
				
				aumentada[k][j] = aumentada[k][j] - diagonal*aumentada[i][j]; 
				
				
			
			}
			
				
		}
	}
	
	
}

//funcaoo que calcula o vetor y=(Q^t)b
void produto_vetor(double QTransposta[n][n], double b[n], double y[n])
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

void verifica_solucao(double A[n][n], double x[n], double resultado_Ax[n])
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

//funcao que soluciona o sistema Rx = y, onde R e a triangular superior
void substituicao_regressiva(double R[n][n], double y[n], double x[n])
{
    int i, j; 
    
	for(i=n-1; i>=0; i--)
	{
		for(j=i; j<n; j++)
        	{
            		x[i] = (y[i] - R[i][j] * y[j]) / R[i][i]; 
        	}
	}
}


void decomposicaoQR(double a[][n], double q[][n], double r[][n])
{
	int i, j, k; 
	double norma; 
		
	for(k=0; k<n; k++)
	{
		r[k][k]=0; 
		
		for(i=0; i<n; i++)
		{
			r[k][k] = r[k][k] + a[i][k] * a[i][k];
			r[k][k] = sqrt(r[k][k]); 		
		}	
		
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


void produto_matriz(double QR[n][n], double q[n][n], double r[n][n])
{
	int i, j, k; 
	
	for (i=0; i<n; i++) 
	{
        	for (j=0; j<n; j++) 
        	{
           		 QR[i][j] = 0;
           		
           		 for (k=0; k<n; k++)
           		 {
               	 	QR[i][j] += q[i][k] * r[k][j];
               	 }          	
               }
	}
}

void imprime_matriz(double matriz[n][n])
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

void residuo(double resultado_Ax[n], double b[n], double vetor_residuo[n])
{

	int i;
	 	
	for(i=0; i<n; i++)
	{
		printf("ax: %lf\n", resultado_Ax[i]);
		vetor_residuo[i] = abs(abs(resultado_Ax[i])- (b[i])); 
		printf("b: %lf\n", b[i]); 
		printf("residuo: %lf\n", vetor_residuo[i]); 
	}
	
	 
}

void main()
{
	int  i, j, det=1; 
	
	double A[n][n], A_copia[n][n], aumentada[n][n+1], A_escalonada[n][n+1], QTransposta[n][n], l[n][n], Q[n][n], R[n][n], QR[n][n];
	double b[n], x[n], y[n], resultado_Ax[n], vetor_residuo[n], I[n][n], Q_normal[n][n], norma[n]; 

    	Gerador(A, b); //gera a matriz A e o vetor b 
    	
    	
    	printf("\n\n--------------------MATRIZ A------------------------------\n\n");
    	imprime_matriz(A); //imprimindo matriz A inicial
    	copia(A, A_copia);
    	
    	
    	matriz_aumentada(aumentada, A, b); //funcao que concatena A e b    	
    	copia_aumentada(aumentada, A_escalonada);  //copia aumentada para A_escolanada antes de escalonar    	
	gauss_pivoteado(A_escalonada, l);  //obtem a matriz escalonada e triangular superior	
	testeLI(A_escalonada, det);  //testa se os vetores coluna sao LI. 
	
	
	printf("\n\n--------------------------MATRIZ QR---------------------------------\n\n"); 		
	decomposicaoQR(A, Q, R); //obtem a decomposicao QR para a matriz A]
	produto_matriz(QR, Q, R); //faz o produto de Q por R	
	imprime_matriz(QR); //pra verificar se e igual a matriz A
	
		
	
	transposta(Q, QTransposta); 	
	produto_matriz(I, QTransposta, Q); //verificando de Q^tQ = I	
	produto_vetor(QTransposta, b, y); //calcula o vetor y = (Q^t)b	
	//printf("\n\n\nvetor y\n\n\n"); 
	//imprime_vetor(y);
	substituicao_regressiva(R, y, x); //soluciona o sistema linear Rx=y
	
	
	printf("\n\n-----------------------Solucao do sistema linear apos a Decomposicao QR (vetor x)-----------------------------\n\n"); 
	imprime_vetor(x); 
		
	
	//printf("\n\ncopia de A: \n\n"); 
	//imprime_matriz(A_copia); 
	printf("\n\n--------------------------PRODUTO Ax---------------------------------\n\n"); 
	verifica_solucao(A_copia, x, resultado_Ax); //faz o produto de A pelo vetor solucao x
	imprime_vetor(resultado_Ax); 
	
	
	printf("\n\n--------------------------VETOR b---------------------------------\n\n"); 
	imprime_vetor(b); 
	
	
	printf("\n\n--------------------------VETOR RESIDUO (|Ax - b|)---------------------------------\n\n"); 
	residuo(resultado_Ax, b, vetor_residuo); 
	imprime_vetor(vetor_residuo); 
	
		
   	exit(0);
   
}

