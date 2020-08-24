/*
	NAME: Killian Griffin
	DATE: 3/26/20
	ASSIGMNEMT: PA5
	LAB SECTION: 5
	DESCRIPTION: This program allows the user to play the card game Yu-Gi-Oh with another user
*/

#include "header.h"

int main()
{
	Deck p1Deck, p2Deck;
	Hand p1Hand, p2Hand;
	int option = 0, modifiedDeck = 0, win = 0, turn = rand() % 2, p1Life = 8000, p2Life = 8000,
		cardchoiceATK1 = 0, cardchoiceDEF1 = 0, cardchoiceATK2 = 0, cardchoiceDEF2 = 0, choice1 = 0, choice2 = 0;


	srand(time(NULL));
	while (option == option)
	{
		cout << "WELCOME TO YU-GI-OH\n\n" << "Choose an option:\n" << "1. Create Player\n"
			<< "2. Duel\n" << "3. Trade\n" << "4. End the game\n\n";
		cin >> option;
		system("cls");

		while (option < 1 || option > 4)
		{
			cout << "WELCOME TO YU-GI-OH\n\n" << "Choose an option:\n" << "1. Create Player\n"
				<< "2. Duel\n" << "3. Trade\n" << "4. End the game\n\n";
			cin >> option;
			system("cls");
		}

		switch (option)
		{
		case 1:
			cout << "PLAYER CREATION\n\n" << "1. Create Player 1 deck\n" << "2. Create Player 2 deck\n\n";
			cin >> option;
			system("cls");

			while (option < 1 || option > 2)
			{
				cout << "PLAYER CREATION\n\n" << "1. Create Player 1 deck\n" << "2. Create Player 2 deck\n\n";
				cin >> option;
				system("cls");
			}
			modifiedDeck = option;

			cout << "PLAYER CREATION\n\n" << "1. Use premade deck\n" << "2. Create deck\n";
			cin >> option;
			system("cls");

			while (option < 1 || option > 2)
			{
				cout << "PLAYER CREATION\n\n" << "1. Use premade deck\n" << "2. Create deck\n";
				cin >> option;
				system("cls");
			}

			switch (option)
			{
			case 1:
				if (modifiedDeck == 1)
				{
					readDeckFile(&p1Deck);
					p1Deck.printDeck();
				}

				if (modifiedDeck == 2)
				{
					readDeckFile(&p2Deck);
					p2Deck.printDeck();
				}
				break;

			case 2:
				if (modifiedDeck == 1)
				{
					for (int index = 0; index < 30; ++index)
					{
						Card newCard;
						cout << "Enter a card name:\n";
						cin >> newCard.name;
						system("cls");

						cout << "Enter an attack stat:\n";
						cin >> newCard.attack;
						system("cls");

						cout << "Enter a defense stat:\n";
						cin >> newCard.defense;
						system("cls");

						cout << "Enter a card type:\n";
						cin >> newCard.type;
						system("cls");

						p1Deck.addCard(newCard);
					}
				}
				if (modifiedDeck == 2)
				{
					for (int index = 0; index < 30; ++index)
					{
						Card newCard;
						cout << "Enter a card name:\n";
						cin >> newCard.name;
						system("cls");

						cout << "Enter an attack stat:\n";
						cin >> newCard.attack;
						system("cls");

						cout << "Enter a defense stat:\n";
						cin >> newCard.defense;
						system("cls");

						cout << "Enter a card type:\n";
						cin >> newCard.type;
						system("cls");

						p1Deck.addCard(newCard);
					}
				}
				break;
			}
			break;

		case 2:
			cout << "IT'S TIME TO DUEL\n\n";
			while (win == 0)
			{
				switch (turn)
				{
				case 0:
					p1Hand.drawToFull(p1Deck);
					cout << "LIFE: " << p1Life << endl;
					p1Hand.printHand();

					cout << "\n\nPlayer 1, choose a card to place in attack mode:\n";
					cin >> cardchoiceATK1;

					while (cardchoiceATK1 < 1 || cardchoiceATK1 > 5)
					{
						cout << "\n\nPlayer 1, choose a card to place in attack mode:\n";
						cin >> cardchoiceATK1;
					}
					system("cls");

					cout << "LIFE: " << p1Life << endl;
					p1Hand.printHand();

					cout << "\n\nPlayer 1, choose a card to place in defense mode:\n";
					cin >> cardchoiceDEF1;

					while ((cardchoiceDEF1 < 1 || cardchoiceDEF1 > 5) && cardchoiceATK1 == cardchoiceDEF1)
					{
						cout << "\n\nPlayer 1, choose a card to place in defense mode:\n";
						cin >> cardchoiceDEF1;
					}
					system("cls");

					p2Hand.drawToFull(p1Deck);
					cout << "LIFE: " << p2Life << endl;
					p2Hand.printHand();

					cout << "\n\nPlayer 2, choose a card to place in attack mode:\n";
					cin >> cardchoiceATK1;

					while (cardchoiceATK2 < 1 || cardchoiceATK2 > 5)
					{
						cout << "\n\nPlayer 2, choose a card to place in attack mode:\n";
						cin >> cardchoiceATK2;
					}
					system("cls");

					cout << "LIFE: " << p2Life << endl;
					p2Hand.printHand();

					cout << "\n\nPlayer 2, choose a card to place in defense mode:\n";
					cin >> cardchoiceDEF2;

					while ((cardchoiceDEF2 < 1 || cardchoiceDEF2 > 5) && cardchoiceATK2 == cardchoiceDEF2)
					{
						cout << "\n\nPlayer 2, choose a card to place in defense mode:\n";
						cin >> cardchoiceDEF2;
					}
					system("cls");

					cout << "Player 1, choose an option:\n\n" << "1. Activate attack card\n" << "2. Activate defense card\n";
					cin >> choice1;

					while (choice1 < 1 || choice1 > 2)
					{
						system("cls");
						cout << "Player 1, choose an option:\n\n" << "1. Activate attack card\n" << "2. Activate defense card\n";
						cin >> choice1;
					}
					system("cls");

					cout << "Player 2, choose an option:\n\n" << "1. Activate attack card\n" << "2. Activate defense card\n";
					cin >> choice2;

					while (choice2 < 1 || choice2 > 2)
					{
						system("cls");
						cout << "Player 2, choose an option:\n\n" << "1. Activate attack card\n" << "2. Activate defense card\n";
						cin >> choice2;
					}

					if (choice1 == 1 && choice2 == 1)
					{
						if (p1Hand.getCard(cardchoiceATK1).attack > p2Hand.getCard(cardchoiceATK2).attack)
						{
							p2Life = p2Life - (p1Hand.getCard(cardchoiceATK1).attack + p2Hand.getCard(cardchoiceATK2).attack);
						}
						if (p2Hand.getCard(cardchoiceATK2).attack > p1Hand.getCard(cardchoiceATK1).attack)
						{
							p1Life = p1Life - (p1Hand.getCard(cardchoiceATK2).attack + p2Hand.getCard(cardchoiceATK1).attack);
						}
					}
					if (choice1 == 1 && choice2 == 2)
					{
						if (p1Hand.getCard(cardchoiceATK1).attack > p2Hand.getCard(cardchoiceDEF2).defense)
						{
							p2Life = p2Life - (p1Hand.getCard(cardchoiceATK1).attack - p2Hand.getCard(cardchoiceDEF2).defense);
						}
					}
					if (choice1 == 2 && choice2 == 1)
					{
						if (p2Hand.getCard(cardchoiceATK2).attack > p1Hand.getCard(cardchoiceDEF1).defense)
						{
							p1Life = p1Life - (p2Hand.getCard(cardchoiceATK2).attack - p1Hand.getCard(cardchoiceDEF1).defense);
						}
					}

					p1Hand.discard(cardchoiceATK1);
					p1Hand.discard(cardchoiceDEF1);
					p2Hand.discard(cardchoiceATK2);
					p2Hand.discard(cardchoiceDEF2);
					turn = 1;
					break;

				case 1:
					p2Hand.drawToFull(p1Deck);
					cout << "LIFE: " << p2Life << endl;
					p2Hand.printHand();

					cout << "\n\nPlayer 2, choose a card to place in attack mode:\n";
					cin >> cardchoiceATK2;

					while (cardchoiceATK2 < 1 || cardchoiceATK2 > 5)
					{
						cout << "\n\nPlayer 2, choose a card to place in attack mode:\n";
						cin >> cardchoiceATK2;
					}
					system("cls");

					cout << "LIFE: " << p2Life << endl;
					p2Hand.printHand();

					cout << "\n\nPlayer 2, choose a card to place in defense mode:\n";
					cin >> cardchoiceDEF2;

					while ((cardchoiceDEF2 < 1 || cardchoiceDEF2 > 5) && cardchoiceATK2 == cardchoiceDEF2)
					{
						cout << "\n\nPlayer 2, choose a card to place in defense mode:\n";
						cin >> cardchoiceDEF2;
					}
					system("cls");

					p1Hand.drawToFull(p1Deck);
					cout << "LIFE: " << p1Life << endl;
					p1Hand.printHand();

					cout << "\n\nPlayer 1, choose a card to place in attack mode:\n";
					cin >> cardchoiceATK1;

					while (cardchoiceATK1 < 1 || cardchoiceATK1 > 5)
					{
						cout << "\n\nPlayer 1, choose a card to place in attack mode:\n";
						cin >> cardchoiceATK1;
					}
					system("cls");

					cout << "LIFE: " << p1Life << endl;
					p1Hand.printHand();

					cout << "\n\nPlayer 1, choose a card to place in defense mode:\n";
					cin >> cardchoiceDEF1;

					while ((cardchoiceDEF1 < 1 || cardchoiceDEF1 > 5) && cardchoiceATK1 == cardchoiceDEF1)
					{
						cout << "\n\nPlayer 1, choose a card to place in defense mode:\n";
						cin >> cardchoiceDEF1;
					}
					system("cls");

					cout << "Player 2, choose an option:\n\n" << "1. Activate attack card\n" << "2. Activate defense card\n";
					cin >> choice2;

					while (choice2 < 1 || choice2 > 2)
					{
						system("cls");
						cout << "Player 2, choose an option:\n\n" << "1. Activate attack card\n" << "2. Activate defense card\n";
						cin >> choice2;
					}

					cout << "Player 1, choose an option:\n\n" << "1. Activate attack card\n" << "2. Activate defense card\n";
					cin >> choice1;

					while (choice1 < 1 || choice1 > 2)
					{
						system("cls");
						cout << "Player 1, choose an option:\n\n" << "1. Activate attack card\n" << "2. Activate defense card\n";
						cin >> choice1;
					}
					system("cls");

					if (choice1 == 1 && choice2 == 1)
					{
						if (p1Hand.getCard(cardchoiceATK1).attack > p2Hand.getCard(cardchoiceATK2).attack)
						{
							p2Life = p2Life - (p1Hand.getCard(cardchoiceATK1).attack + p2Hand.getCard(cardchoiceATK2).attack);
						}
						if (p2Hand.getCard(cardchoiceATK2).attack > p1Hand.getCard(cardchoiceATK1).attack)
						{
							p1Life = p1Life - (p1Hand.getCard(cardchoiceATK1).attack + p2Hand.getCard(cardchoiceATK2).attack);
						}
					}
					if (choice1 == 1 && choice2 == 2)
					{
						if (p1Hand.getCard(cardchoiceATK1).attack > p2Hand.getCard(cardchoiceDEF2).defense)
						{
							p2Life = p2Life - (p1Hand.getCard(cardchoiceATK1).attack - p2Hand.getCard(cardchoiceDEF2).defense);
						}
					}
					if (choice1 == 2 && choice2 == 1)
					{
						if (p2Hand.getCard(cardchoiceATK2).attack > p1Hand.getCard(cardchoiceDEF1).defense)
						{
							p1Life = p1Life - (p2Hand.getCard(cardchoiceATK2).attack - p1Hand.getCard(cardchoiceDEF1).defense);
						}
					}

					p1Hand.discard(cardchoiceATK1);
					p1Hand.discard(cardchoiceDEF2);
					p2Hand.discard(cardchoiceATK1);
					p2Hand.discard(cardchoiceDEF2);
					turn = 0;
					break;
				}
				if (p1Life <= 0 || p2Life <= 0)
				{
					win = 1;
				}
			}
			if (p1Life <= 0)
			{
				cout << "Player 2 wins the duel!\n";
				system("pause");
				system("cls");
			}
			if (p2Life <= 0)
			{
				cout << "Player 1 wins the duel!\n";
				system("pause");
				system("cls");
			}
			break;

		case 3:
			break;

		case 4:
			return 0;
			break;
		}
		
	}
}