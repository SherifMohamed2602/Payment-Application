#include <stdio.h>
#include<string.h>
#include "card.h"
#include "terminal.h"
#include "server.h"
#include "app.h"



int main ()
{
	appStart();

}



void appStart(void) {
	ST_transaction_t* pAtm;
	pAtm = (ST_transaction_t*)malloc(sizeof(ST_transaction_t));

	while (getCardHolderName(&pAtm->cardHolderData)) { printf("NotValid Name\n"); }
	while (getCardExpiryDate(&pAtm->cardHolderData)) { printf("NotValid Date\n"); }
	while (getCardPAN(&pAtm->cardHolderData)) { printf("NotValid number\n"); }
	while (getTransactionDate(&pAtm->terminalData)) { printf("NotValid Date\n"); }
	if (isCardExpired(pAtm->cardHolderData , pAtm->terminalData))
	{	printf("CARD_EXPIRED\nTransaction Declined"); return; }
	setMaxAmount(&pAtm->terminalData);
	printf("Max Amount set to 5000\n");
	while (getTransactionAmount(&pAtm->terminalData)) {}
	if(isBelowMaxAmount(&pAtm->terminalData))
	{	printf("MaxAmountExeeded\nTransaction Declined"); return; }
	 recieveTransactionData(pAtm);
	 saveTransaction(pAtm);
	if (pAtm->transState == 1)
		printf("You don't have enough fund\nTransaction Declined");
	else if (pAtm->transState == 2)
		printf("Stolen Card\nTransaction Declined");
	else if (pAtm->transState == 3 )
		printf("Account not found\nTransaction Declined");
	else 
		printf("Transaction APPROVED");
	}
