#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int mainMenu();
int receivesNumberOfElements();
void allocateFloat(float **p, int quantity);
void receivesElementsAndErros(float *pElements, float *pErrors, int quantity);
float calculator(float *pElements, int quantity, int operationOption);
float sumAndSub(float *pELements, int quantity, int operationOption);
float multAndDiv(float *pElements, float *pErrors, int quantity);

int main(){

    int operationOption, numberOfElements;
    float resultOperation, errorResult;
    float *pElements = NULL, *pErrors = NULL; 

    do{
        operationOption = mainMenu();

        if(operationOption < 1 || operationOption > 5){
            printf("Invalid option, retype\n");
            system("pause");
        } else{
            numberOfElements = receivesNumberOfElements();
            pElements = NULL;
            pErrors = NULL;
            allocateFloat(&pElements, numberOfElements);
            allocateFloat(&pErrors, numberOfElements);
            receivesElementsAndErros(pElements, pErrors, numberOfElements);
            resultOperation = calculator(pElements, numberOfElements, operationOption);

            switch(operationOption){
                case 1: case 2:
                    errorResult = sumAndSub(pErrors, numberOfElements, operationOption);
                    break;
                case 3: case 4:
                    errorResult = multAndDiv(pElements, pErrors, numberOfElements);
                    break;
            }
            if(operationOption == 1 || operationOption == 2){
                printf("\nResult: %.4f +- %.4f\n", resultOperation, errorResult);
            } else{
                printf("\nResult: %.4f +- %.4f\n", resultOperation, errorResult * errorResult);
            }
            system("pause");
        }
    } while (operationOption != 5);

    return 0;
}

int mainMenu(){
    int option;
	
    system("cls");
    printf("-------------- Propagation of Errors --------------\n\n");
    printf("\t\tMathematical Operation:\n");
    printf("[1] Sum\n[2] Subtraction\n[3] Multiplication\n[4] Division\n[5] Exit\n");
    printf("\nOption: [ ]\b\b");
    scanf("%i", &option);
    fflush(stdin);

    return option;
}

int receivesNumberOfElements(){
    int quantity;
    
    do{
        printf("\nEnter the number of elements: ");
        scanf("%i", &quantity);
        fflush(stdin);
    } while (quantity > 2);

    return quantity;
}

void allocateFloat(float **p, int quantity){
    if((*p = (float*)realloc(*p, quantity * sizeof(float))) == NULL){
        printf("Insufficient memory.\n");
        system("pause");
    }
}

void receivesElementsAndErros(float *pElements, float *pErrors, int quantity){
    int i;
    printf("\n--------------- Receiving Elements --------------\n\n");
    for (i = 0; i < quantity; i++){
        printf("Enter the value of element %c: ", 'a' + i);
        scanf("%f", (pElements + i));
    }

    printf("\n---------------- Receiving Erros ----------------\n\n");
    for (i = 0; i < quantity; i ++){
        printf("Enter the error of element %c: ", 'a' + i);
        scanf("%f", (pErrors + i));
    }
}

float calculator(float *pElements, int quantity, int operationOption){
    int i;
    float result = 0;

    switch(operationOption){
        case 1:
            for (i = 0; i < quantity; i++){
                result += *(pElements + i);
            }
            break;
        case 2:
            for (i = 0; i < quantity ; i++){
                if(i != 0){
                    result -= *(pElements + i);
                } else{
                    result += *(pElements + i);
                }
            }
            break;
        case 3:
            result = 1;
            for (i = 0; i < quantity; i++){
                result *= *(pElements + i);
            }
            break;
        case 4:
            result = (*(pElements + 0)) / (*(pElements + 1));
            break;
    }
    return result;
}

float sumAndSub(float *pELements, int quantity, int operationOption){
    int i;
    float result = 0;

    for (i = 0; i < quantity; i++){
        result += pow(*(pELements + i), 2);
    }
    return sqrt(result);
}

float multAndDiv(float *pElements, float *pErrors, int quantity){
    int i;
    float result = 0;

    for (i = 0; i < quantity; i++){
        result += (pow(*(pErrors + i), 2)) / (pow(*(pElements + i), 2));
    }
    return sqrt(result);
}