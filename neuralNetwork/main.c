#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define NUMEX 4
#define NUM1  2
#define NUM2 2
#define NUM3 1

double getRandomDouble()
{
    /*return (double)((rand()%max-min+1.0)+1.0);*/
    return (double)rand()/(RAND_MAX);
}

void initWeight(int numberUnitsFirst,int numberUnitsSecond,
double weight[][numberUnitsSecond],double deltaWeight[][numberUnitsSecond])
{
    for (int j = 1; j <= numberUnitsSecond; j++) {
        for (int i = 0; i <= numberUnitsFirst; i++) {
            deltaWeight[i][j]=0.0;
            weight[i][j]=2.0 * ( getRandomDouble() - 0.5 ) * 0.5;
        }
    }
}

int main()
{
    srand(time(NULL));
    //int e=0;
    int numberUnits1= NUM1, numberUnits2=NUM2,numberUnits3=NUM3;
    int numberExemple=NUMEX;
    /*double Layer1Out[NUM1+1];*/
    int tour=0;
    double Layer2In[NUMEX+1][NUM2+1];
    double Layer2InBackProp[NUM2+1];
    double Layer2Out[NUMEX+1][NUM2+1];
    double Layer3In[NUMEX+1][NUM3+1];
    double Layer3Out[NUMEX+1][NUM3+1];
    double weight12[NUM1+1][NUM2+1];
    double weight23[NUM2+1][NUM3+1];
    double deltaWeight12[NUM1+1][NUM2+1];
    double deltaWeight23[NUM2+1][NUM3+1];
    double deltaLayer3[NUM3+1];
    double deltaLayer2[NUM2+1];
    //double trainingArray[4][3]={{0,0,0},{0,1,1},{1,0,1},{1,1,0}};
    double layer1Out[NUMEX+1][NUM1+1] =
    { {0, 0, 0}, { 0, 0, 0},{  0, 1, 0},{  0, 0, 1} ,{  0, 1, 1} };
    double target[NUMEX+1][NUM3+1] =
    {{ 0, 0},{  0, 0}, { 0, 1},{  0, 1}, { 0, 0} };
//    double learningRate=0.5;

    initWeight(numberUnits1,numberUnits2,weight12,deltaWeight12);
    initWeight(numberUnits2,numberUnits3,weight23,deltaWeight23);


    for (int l = 0; l < 2000; l++) {
     //while (!(Layer3Out[1][1]<0.5&&Layer3Out[2][1]>0.5&&Layer3Out[3]
	//[1]>0.5&&Layer3Out[4][1]<0.5)) {

        for (int e = 1; e <= numberExemple; e++) {
            tour++;
            //e=(rand()%4)+1;
            for( int i = 1 ; i <= numberUnits1 ; i++ ) {
                //printf("Layer2in: %f\n",layer1Out[e][i]);
            }
            for( int j = 1 ; j <= numberUnits2 ; j++ ) {
                Layer2In[e][j] = weight12[0][j] ;
                for( int i = 1 ; i <= numberUnits1 ; i++ ) {
                    Layer2In[e][j] += layer1Out[e][i] * weight12[i][j] ;
                }
                Layer2Out[e][j] = 1.0/(1.0 + exp(-Layer2In[e][j])) ;
            }

            for( int j = 1 ; j <= numberUnits3 ; j++ ) {
                Layer3In[e][j] = weight23[0][j] ;
                for( int i = 1 ; i <= numberUnits2 ; i++ ) {
                    Layer3In[e][j] += Layer2Out[e][i] * weight23[i][j] ;
                }
                Layer3Out[e][j] = 1.0/(1.0 + exp(-Layer3In[e][j])) ;
                deltaLayer3[j]=target[e][1]-Layer3Out[e][j];
                //printf("Layer3 out:%f\n",Layer3Out[j]);
            }
            for( int j = 1 ; j <= numberUnits2 ; j++ ) {
                //'back-propagatation 
                Layer2InBackProp[j] = 0.0 ;
                for( int k = 1 ; k <= numberUnits3 ; k++ ) {
                    Layer2InBackProp[j] += weight23[j][k] * deltaLayer3[k] ;
                }
                deltaLayer2[j] = Layer2InBackProp[j] *Layer2Out[e][j] * 
		(1.0 - Layer2Out[e][j]) ;
            }
            for (int j = 1; j <= numberUnits2; j++) {

                deltaWeight12[0][j] = 0.1*deltaLayer2[j] + 0.5 * 
		deltaWeight12[0][j] ;
                weight12[0][j]+=deltaWeight12[0][j];
                for (int i = 1; i <= numberUnits1; i++) {
                    deltaWeight12[i][j]=0.1*layer1Out[e][i]*deltaLayer2[j]+0.5*
		    deltaWeight12[i][j];
                    weight12[i][j]+=deltaWeight12[i][j];
                }
            }
            for (int j = 1; j <= numberUnits3; j++) {
                deltaWeight23[0][j] = 0.1*deltaLayer3[j] + 0.5* 
		deltaWeight23[0][j] ;
                weight23[0][j]+=deltaWeight23[0][j];
                for (int i = 1; i <= numberUnits2; i++) {
                    deltaWeight23[i][j]=0.1*Layer2Out[e][i]
                  *deltaLayer3[j]+0.5* deltaWeight23[i][j];
                    weight23[i][j]+=deltaWeight23[i][j];
                }
            }
        }
        if (l%500==0) {
    printf("Iteration number %d\n",l) ;
    printf("Target\t\tReal Out\n") ;
    printf("%f\t%f\n", target[1][1], Layer3Out[1][1]) ;
    printf("%f\t%f\n", target[2][1], Layer3Out[2][1]) ;
    printf("%f\t%f\n", target[3][1], Layer3Out[3][1]) ;
    printf("%f\t%f\n", target[4][1], Layer3Out[4][1]) ;
        }
    }
    printf("Target\tReal Out\n") ;
    printf("%f\t%f\n", target[1][1], Layer3Out[1][1]) ;
    printf("%f\t%f\n", target[2][1], Layer3Out[2][1]) ;
    printf("%f\t%f\n", target[3][1], Layer3Out[3][1]) ;
    printf("%f\t%f\n", target[4][1], Layer3Out[4][1]) ;
    //printf("%d\n",tour);
    return 0;
    }

