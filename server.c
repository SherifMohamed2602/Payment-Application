#include <stdio.h>
#include<string.h>
#include "server.h"
ST_accountsDB_t accounts[255] = { {10500 , RUNNING , "123456789123456789"}, {50000, RUNNING , "987654321987654321"}, {2000, RUNNING , "012345665432100123"},
	                              {5000, BLOCKED , "2024680246802468"}, {1200, RUNNING , "13579135799753115"}, {2500, RUNNING , "2602011109775962602"}};
int found = 0; int c = 0;
ST_transaction_t transactions[255] = { 0 };

EN_transState_t recieveTransactionData(ST_transaction_t* transData) {
	transData->transState = OK2;
	if (isValidAccount(&transData->cardHolderData))
		transData->transState = ACCOUNT_NOT_FOUND;
	if (isAmountAvailable(&transData->terminalData))
		transData->transState = DECLINED_INSUFFECIENT_FUND;
	if (accounts[found].accState == BLOCKED	)
		transData->transState = DECLINED_STOLEN_CARD;

	   if (transData->transState == 0)
	   {
		   accounts[found].balance -= transData->terminalData.transAmount;
		   printf("new balance is %f\n", accounts[found].balance);
		   return OK2;
	   }
	 
}
EN_serverError_t isValidAccount(ST_cardData_t* cardData) {

	for (int i = 0; i < 255 ; i++)
		if (!strcmp(cardData->primaryAccountNumber, accounts[i].primaryAccountNumber))
		{
			found = i; 
			return OK2;
		}
	
	return DECLINED_STOLEN_CARD;
}
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData) {
	if (termData->transAmount > accounts[found].balance)
		return LOW_BALANCE;
	else return OK2;

}
EN_serverError_t saveTransaction(ST_transaction_t* transData) {

	transactions[c].cardHolderData = transData->cardHolderData;
	transactions[c].terminalData = transData->terminalData;
	
	transactions[c].transState = transData->transState;

	transactions[c++].transactionSequenceNumber++;

	return OK2; 


}

