#include <stdio.h>
#include <string.h>
#include "card.h"
EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {

	printf("please enter the card holder name:");
	gets(cardData->cardHolderName);
	if (strlen(cardData->cardHolderName) < 20 || strlen(cardData->cardHolderName) > 24)
	{
		return WRONG_NAME;
	}
	else return OK;

}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {

	printf("please enter the card expiry date in the format \"MM / YY\":");
	gets(cardData->cardExpirationDate);
	for (int i = 0; i < 5; i++)
	{
		if (cardData->cardExpirationDate[0] - '0' > 1)
			return WRONG_EXP_DATE;
		if (cardData->cardExpirationDate[0] - '0' == 1 && cardData->cardExpirationDate[1] - '0' > 2)
			return WRONG_EXP_DATE;

		if (i == 2){
			if (cardData->cardExpirationDate[i] != '/')

				return WRONG_EXP_DATE;
	}

		else if (cardData->cardExpirationDate[i] > 57 || cardData->cardExpirationDate[i] < 48)
		
			return WRONG_EXP_DATE;
		

	}
	return OK;
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData) {

	printf("please enter the card's primary account number:");
	gets(cardData->primaryAccountNumber);

	if (strlen(cardData->primaryAccountNumber) > 19 || strlen(cardData->primaryAccountNumber) < 16)
	
		return WRONG_PAN;
	
	for (int i = 0; i < strlen(cardData->primaryAccountNumber); i++) {

		if ((cardData->primaryAccountNumber[i] > 57 && cardData->primaryAccountNumber[i] < 65) ||
			(cardData->primaryAccountNumber[i] > 90 && cardData->primaryAccountNumber[i] < 97) ||
			cardData->primaryAccountNumber[i] > 122 || cardData->primaryAccountNumber[i] < 48)
		{
			return WRONG_PAN;
		}
	}
	return OK;
}
