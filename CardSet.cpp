/*******************************************************
 * AUTHOR: NIMRA GAUHAR
 * ID: 5949403
 *******************************************************/
#include "CardSet.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

CardSet::CardSet(){
	Card=NULL;
	nCards=0;
}
CardSet::CardSet(int n){
	nCards=n;	
	Card = new int[nCards];
	if(n<=52){
		for(int i=0 ; i<nCards ; i++){
		Card[i]=i;
		}	
	}
	else{
		int howManySets = nCards/51;
		int leftOverSet = n%51;
		int j=0;
		for(int i=0 ; i<nCards ; i++){
			Card[i]=j;
			if(j!=51){
				j++;
			} else if(j==51){
				j=0;
			}
		}
	}
}

CardSet::~CardSet(){
	delete Card;
}
int CardSet::Size() const{
	return nCards;
}
bool CardSet::IsEmpty() const{
	return(nCards==0);
}
void CardSet::Print() const{
	int newLine=0;
	for(int i = 0; i < nCards;i++){
		newLine++;
		PrintCard(Card[i]);
		cout<<" ";
		if(newLine%5==0){
			cout<<endl;
		}
	}
	cout<<endl;
}
void CardSet::Shuffle(){
	srand(time(0));
    for (int i=0; i<nCards; i++) {
        int j = rand() % nCards;
        if(i!=j){
	        int temp = Card[i];
			Card[i] = Card[j]; 
			Card[j] = temp;
		}
    }	
}

int CardSet::Deal(){
	if(nCards==0){
		cerr<<"Not enough cards in the set to deal. Terminated.";
		exit(1);
	}

	int returnValue=Card[0];
	
	int *newCard = new int[nCards-1];
	for(int i = 0 ; i < (nCards-1) ; i++){
		newCard[i]=Card[i+1];	
	}
    delete Card;
	nCards = nCards-1;
	Card=newCard;

	return returnValue;
}

void CardSet::AddCard(int c){

	int *newCard= new int[nCards+1];
	for(int i = 0 ; i < nCards; i++){
		newCard[i]=Card[i];
	}
	delete Card;
	newCard[nCards]=c;
	nCards=nCards+1;
	Card=newCard;

}
void CardSet::Deal(int n,CardSet& hand1 ,CardSet& hand2){
	int card1, card2;
	for(int i = 0 ; i < n ; i++){
		card1=this->Deal();
		hand1.AddCard(card1);
		card2=this->Deal();
		hand2.AddCard(card2);
	}
}

void CardSet::Deal(int n,CardSet& hand1, CardSet& hand2, CardSet& hand3 ,CardSet& hand4){
	int card1, card2, card3, card4;
	for(int i = 0 ; i < n; i++){
		card1=this->Deal();
		hand1.AddCard(card1);
		card2=this->Deal();
		hand2.AddCard(card2);
		card3=this->Deal();
		hand3.AddCard(card3);
		card4=this->Deal();
		hand4.AddCard(card4);
	}
}
void CardSet::MergeShuffle(CardSet& otherCard){
	int newSize= this->Size()+otherCard.Size();
	cout<<newSize<<endl;
	int *CardSetNew = new int[newSize];
	int firstSetIndex=0, secondSetIndex=0;
	
	
	for(int i = 0 ; i < newSize ; i++){
		if(firstSetIndex!=this->Size()){
			CardSetNew[i]= this->Card[firstSetIndex];
			i++;
			firstSetIndex++;
		}
		if(secondSetIndex!=otherCard.Size()){
			CardSetNew[i]= otherCard.Card[secondSetIndex];
			secondSetIndex++;
		}
	}
	delete this->Card;
	
	this->Card = new int[newSize];
	this->nCards = newSize;
	this->Card = CardSetNew;
	
}
void CardSet::PrintCard(int c) const
{
	if(c>51){
		cout<<"heres the problem\n";
	}
	int Rank = c%13;
	int Suit = c/13;
	const char NameSuit[5] = "SCDH";
	const char NameRank[14] = "23456789XJQKA";
	cout << NameRank[Rank] << NameSuit[Suit];
}

