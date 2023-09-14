#include <stdio.h>
#include<string.h>
#include "terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {

	printf("please enter the transaction date in the format DD/MM/YYYY :");
	gets(termData->transactionDate);
	for (int i = 0; i < 10; i++)
	{
		
		if (termData->transactionDate[0] - '0' > 4)
			return WRONG_DATE;
		if (termData->transactionDate[0] - '0' == 3 && termData->transactionDate[1] - '0' > 0)
			return WRONG_DATE;
		if (termData->transactionDate[3] - '0' > 1)
			return WRONG_DATE;
		if (termData->transactionDate[3] - '0' == 1 && termData->transactionDate[4] - '0' > 2)
			return WRONG_DATE;
		if (i == 2)
		{
			if (termData->transactionDate[i] != '/')
		
				return WRONG_DATE;
			
		}
		else if (i == 5)
		{
			if (termData->transactionDate[i] != '/')
			
				return WRONG_DATE;
			
		}

		else if (termData->transactionDate[i] > 57 || termData->transactionDate[i] < 48)
		
			return WRONG_DATE;
		

	}
	return OK1;

}



EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData) {
	int j = 0, k = 0;
	if (termData.transactionDate[6] < 50 )
		return OK1;
	if (termData.transactionDate[7] > 48 && termData.transactionDate[6] == 50)
		return EXPIRED_CARD;
	for (int i = 0; i < 4 ; i++) {

		if (termData.transactionDate[i + 8 - j] > cardData.cardExpirationDate[i + 3 - k])
			return EXPIRED_CARD;
		else if (termData.transactionDate[i + 8 - j] < cardData.cardExpirationDate[i + 3 - k])
			return OK1;
		if (i == 1) { j = 7 ; k = 5 ;  }
	}

	return OK1;

}



EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {

	printf("please enter the tranaction amount:");
	scanf_s("%f", &termData->transAmount);
	if (termData->transAmount <= 0)
		return INVALID_AMOUNT;
	else return OK1;

}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
	if (termData->transAmount > termData->maxTransAmount)
		return EXCEED_MAX_AMOUNT;
	else return OK1;


}
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData) {

	termData->maxTransAmount = 5000;
	if (termData->maxTransAmount <= 0)
		return INVALID_MAX_AMOUNT;
	else return OK1;
}