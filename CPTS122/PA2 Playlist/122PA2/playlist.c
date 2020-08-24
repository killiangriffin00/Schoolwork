/*
	NAME: Killian Griffin
	DATE: 2/6/20
	ASSIGNMENT: PA2
	LAB SECTION: 5
	DESCRIPTION: This program is a movie playlist manager that loads a playlist into the program, stores a playlist in a file, displays movie
	info, edits the attributes of a record, rates movies, and plays the playlist.
*/

#include "header.h"

/*
	FUNCTION: printMenu()
	DATE MODIFIED: 2/9/20
	INPUT PARAMETERS: none
	OUTPUT PARAMETERS: Integer (option)
	DESCRIPTION: Prints the menu for the playlist manager and returns the users chosen option.
*/
int printMenu(void)
{
	int option = 0;
	printf("PLAYLIST MANAGER\n\n"); // print statement for the menu
	printf("(1) Load\n(2) Store\n(3) Display\n(4) Insert\n(5) Delete\n(6) Edit\n(7) Sort\n(8) Rate\n(9) Play\n(10) Shuffle\n(11) Exit\n\n");
	printf("Choose an option: ");

	scanf("%d", &option); // user enters an option

	if (option < 1 || option > 11) // checks for invalid options
	{
		printf("Choose an option: ");
		scanf("%d", &option);
	}
	return option;
}

/*
	FUNCTION: isEmpty()
	DATE MODIFIED: 2/9/20
	INPUT PARAMETERS: Head pointer to a linked list
	OUTPUT PARAMETERS: Integer (status)
	DESCRIPTION: Checks if the linked list is empty.
*/

int isEmpty(Node* pHead)
{
	int status = 0;
	if (pHead == NULL) // pHead is null if the list is empty
	{
		status = 1;
	}
	return status;
}

/*
	FUNCTION: readFile()
	DATE MODIFIED: 2/10/20
	INPUT PARAMETERS: Inpit file, head pointer to a doubly linked list, tail pointer to a doubly linked list
	OUTPUT PARAMETERS: Integer (0)
	DESCRIPTION: Scans information in a file seperated by commmas into a doubly linked list.
*/

int readFile(FILE* infile, Node**pHead, Node**pTail)
{
	char trash = 0, topline[200] = "\0";
	int index = 0;

	for (; topline[index - 1] != '\n'; ++index) //reads in the top line first to avoid it getting read into the linked list
	{
		fscanf(infile, "%c", &topline[index]);
	}
	index = 0;

	while (!feof(infile)) // loop scans in the data
	{
		Node* newElement = (Node*)malloc(sizeof(Node));
		Node* pTraverse2 = *pHead; 

		for (index = 0; newElement->data.title[index-1] != ','; ++index) // scans in title
		{
			fscanf(infile, "%c", &newElement->data.title[index]);
		}
		newElement->data.title[index - 1] = NULL; // these statements are used to replace the comma with a null character, making the 
											      // attributes strings
		for (index = 0; newElement->data.director[index - 1] != ','; ++index) // scans in director
		{
			fscanf(infile, "%c", &newElement->data.director[index]);
		}
		newElement->data.director[index - 1] = NULL;

		for (index = 0; newElement->data.description[index - 1] != ','; ++index) // scans in description 
		{
			fscanf(infile, "%c", &newElement->data.description[index]);
		}
		newElement->data.description[index - 1] = NULL;

		for (index = 0; newElement->data.genre[index - 1] != ','; ++index) // scans in genre
		{
			fscanf(infile, "%c", &newElement->data.genre[index]);
		}
		newElement->data.genre[index - 1] = NULL;

		fscanf(infile, "%d", &newElement->data.runtime.hours); // scans in runtime (hours)
		fscanf(infile, "%c", &trash);// used to make sure no commas are scanned in

		fscanf(infile, "%d", &newElement->data.runtime.minutes); // scans in runtime (minutes)
		fscanf(infile, "%c", &trash);

		fscanf(infile, "%d", &newElement->data.year); // scans in year
		fscanf(infile, "%c", &trash);

		fscanf(infile, "%d", &newElement->data.played); // scans in times played
		fscanf(infile, "%c", &trash);

		fscanf(infile, "%d", &newElement->data.rating); // scans in rating
		fscanf(infile, "%c", &trash);

		newElement->next = NULL; // this element will be appended to the end of the list, meaning it will be pointing to null

		if (isEmpty(*pHead) == 1) // element becomes the head element if the list is empty
		{
			*pHead = newElement;
		}
		else
		{
			while (pTraverse2->next != NULL) // used to find the end of the list
			{
				pTraverse2 = pTraverse2->next;
			}
			newElement->previous = pTraverse2; // newElement is placed there
			pTraverse2->next = newElement;
		}
	}
	Node* pTraverse1 = *pHead;
	while (pTraverse1->next != NULL) // used to find the end of the list
	{
		pTraverse1 = pTraverse1->next;
	}
	*pTail = pTraverse1; // tail pointer is assigned to the end

	return 0;
}

/*
	FUNCTION: writeFile()
	DATE MODIFIED: 2/10/20
	INPUT PARAMETERS: Output file, head pointer to a doubly linked list, tail pointer to a doubly linked list
	OUTPUT PARAMETERS: Integer (0)
	DESCRIPTION: Writes the information in a doubly linked list to a file seperated by commas.
*/

int writeFile(FILE* outfile, Node* pHead, Node* pTail)
{
	if (isEmpty(pHead, pTail)) // will not execute if list is empty
	{
		return 0;
	}

	while (pHead != pTail) // will execute as long as  there are still elements in the list
	{
		fprintf(outfile, "%s", pHead->data.title); // printed in the same comma separated format
		fprintf(outfile, ",");

		fprintf(outfile, "%s", pHead->data.director);
		fprintf(outfile, ",");

		fprintf(outfile, "%s", pHead->data.description);
		fprintf(outfile, ",");

		fprintf(outfile, "%s", pHead->data.genre);
		fprintf(outfile, ",");

		fprintf(outfile, "%d", pHead->data.runtime.hours);
		fprintf(outfile, ",");

		fprintf(outfile, "%d", pHead->data.runtime.minutes);
		fprintf(outfile, ",");

		fprintf(outfile, "%d", pHead->data.year);
		fprintf(outfile, ",");

		fprintf(outfile, "%d", pHead->data.played);
		fprintf(outfile, ",");

		fprintf(outfile, "%d", pHead->data.rating);
		fprintf(outfile, "\n");
		pHead->previous = pHead; // traverse to next node
		pHead = pHead->next;
	}
	return 0;
}

/*
	FUNCTION: displayList()
	DATE MODIFIED: 2/11/20
	INPUT PARAMETERS: Head pointer to a doubly linked list, tail pointer to a doubly linked list
	OUTPUT PARAMETERS: Integer (0)
	DESCRIPTION: Allows the user to print all movies in the list to the screen, or all movies by a chosen director and in a certain year.
*/

int displayList(Node* pHead, Node* pTail)
{
	if (isEmpty(pHead)) // will not execute if list is empty
	{
		return 0;
	}

	int option = 0, year = 0, none = 1, index = 0;
	char director[20], trash;

	printf("1. Print movies in playlist\n"); // user options
	printf("2. Print all movies by director\n");
	printf("3. Print all movies by year\n\n");
	printf("Select an option: ");

	scanf("%d", &option);

	while (option < 1 || option > 3) // checks for valid option
	{
		printf("Select an option: ");
		scanf("%d", &option);
	}
	system("cls");

	switch (option)
	{
	case 1: // print all movies
		while (pHead != pTail) // while there are still elements in the list
		{
			printf("%s", pHead->data.title); // printed in the same comma separated format
			printf(",");

			printf("%s", pHead->data.director);
			printf(",");

			printf("%s", pHead->data.description);
			printf(",");

			printf("%s", pHead->data.genre);
			printf(",");

			printf("%d", pHead->data.runtime.hours);
			printf(",");

			printf("%d", pHead->data.runtime.minutes);
			printf(",");

			printf("%d", pHead->data.year);
			printf(",");

			printf("%d", pHead->data.played);
			printf(",");

			printf("%d", pHead->data.rating);
			printf("\n");
			pHead->previous = pHead; // traverses the list
			pHead = pHead->next;
		}
		system("pause");
		system("cls");
		break;

	case 2: // print movies by director
		printf("Enter director: "); 
		scanf("%c", &trash);
		fgets(director, 20, stdin);
		while (director[index] != '\n') // looks for \n character and replaces it with null
		{
			++index;
		}
		director[index] = NULL;
		index = 0;
		while (pHead != pTail) // while there are still elements in the list
		{
			if (strcmp(director, pHead->data.director) == 0) // checks if user's input is the same as in the list
			{
				printf("%s", pHead->data.title); // prints in the same comma separated format
				printf(",");

				printf("%s", pHead->data.director);
				printf(",");

				printf("%s", pHead->data.description);
				printf(",");

				printf("%s", pHead->data.genre);
				printf(",");

				printf("%d", pHead->data.runtime.hours);
				printf(",");

				printf("%d", pHead->data.runtime.minutes);
				printf(",");

				printf("%d", pHead->data.year);
				printf(",");

				printf("%d", pHead->data.played);
				printf(",");

				printf("%d", pHead->data.rating);
				printf("\n");
				none = 0;
			}
			pHead->previous = pHead; // traverses the list
			pHead = pHead->next;
		}
		if (none == 1) // if no elements mached the search
		{
			printf("No movies were found\n\n");
		}
		none = 1;
		system("pause");
		system("cls");
		break;

	case 3: // prints movies by year
		printf("Enter a year: "); 
		scanf("%d", &year); // user input

		while (pHead != pTail) // while there are still elements in the list
		{
			if (year == pHead->data.year) // checks if user input is the same as in the list
			{
				printf("%s", pHead->data.title); //prints in same comma separated format
				printf(",");

				printf("%s", pHead->data.director);
				printf(",");

				printf("%s", pHead->data.description);
				printf(",");

				printf("%s", pHead->data.genre);
				printf(",");

				printf("%d", pHead->data.runtime.hours);
				printf(",");

				printf("%d", pHead->data.runtime.minutes);
				printf(",");

				printf("%d", pHead->data.year);
				printf(",");

				printf("%d", pHead->data.played);
				printf(",");

				printf("%d", pHead->data.rating);
				printf("\n");
				none = 0;
			}
			pHead->previous = pHead; // traverses the list
			pHead = pHead->next;
		}
		if (none == 1) // if no elements mached the search
		{
			printf("No movies were found\n\n");
		}
		none = 1;
		system("pause");
		system("cls");
		break;
	}
	return 0;
}

/*
	FUNCTION: editList()
	DATE MODIFIED: 2/10/20
	INPUT PARAMETERS:  Double head pointer to a doubly linked list, double tail pointer to a doubly linked list 
	OUTPUT PARAMETERS: Integer (0)
	DESCRIPTION: Allows user to search for any movie in the list by director, and allows them to edit the record of the movie.
*/

int editList(Node** pHead, Node** pTail)
{
	if (isEmpty(*pHead)) // will not execute if list is empty
	{
		return 0;
	}
	Node* pTemp = NULL;
	int index = 0, count = 0, iteration = 0, none = 1, exit = 0, option = 0;
	char director[20], title[20], trash;
	printf("Enter director: ");
	scanf("%c", &trash);
	fgets(director, 20, stdin);
	while (director[index] != '\n') // looks for \n character and replaces it with a null character
	{
		++index;
	}
	director[index] = NULL;
	index = 0;

	while (*pHead != *pTail) // while there are still elements in the list
	{
		if (strcmp(director, (*pHead)->data.director) == 0) // checks if user input is the same as in the list
		{
			printf("%s\n", (*pHead)->data.title);
			++count;
			strcpy(title, (*pHead)->data.title); // stores title in case there are more than one movies by the director
			none = 0;
		}
		pTemp = *pHead; // iterates through the list
		*pHead = (*pHead)->next;
		(*pHead)->previous = pTemp;
		++iteration;
	}

	for (int index = 0; index < iteration; ++index) // iterates back the same ammount of iterations it made in the previous loop
	{
		*pHead = (*pHead)->previous;
	}

	if (none == 1) // if no elements matched the search
	{
		printf("No movies were found\n\n");
		system("pause");
		system("cls");
		return 0;
	}
	if (count < 1) // if there are more than one movies by that director
	{
		printf("Enter a movie title: "); // search by title
		fgets(title, 20, stdin);
		while (title[index] != '\n') // eliminate \n cahracter
		{
			++index;
		}
		title[index] = NULL;
		index = 0;
	}
	system("cls");
	iteration = 0;
	while (exit == 0 && *pHead != *pTail) // while the title hasn't been found and there are still elements in the list
	{
		if (strcmp((*pHead)->data.title, title) == 0) // checks if user input is the same as in the list
		{
			printf("1. Title: %s\n", (*pHead)->data.title); // prints information for user to easily choose from

			printf("2. Director: %s\n", (*pHead)->data.director);

			printf("3. Description: %s\n", (*pHead)->data.description);

			printf("4. Genre: %s\n", (*pHead)->data.genre);

			printf("5. Run Time (Hours): %d\n", (*pHead)->data.runtime.hours);

			printf("6. Run Time(Minutes): %d\n", (*pHead)->data.runtime.minutes);

			printf("7. Year: %d\n", (*pHead)->data.year);

			printf("8. Times Played: %d\n", (*pHead)->data.played);

			printf("9. Rating: %d\n", (*pHead)->data.rating);
			none = 0;
			exit = 1;
		}
		if (exit == 0)
		{
			pTemp = *pHead; // iterates through the array if title hasn't been found
			*pHead = (*pHead)->next;
			(*pHead)->previous = pTemp;
			++iteration;
		}
	}
	for (int index = 0; index < iteration; ++index) // iterates back through the array the same ammount oof iterations in the last loop
	{
		*pHead = (*pHead)->previous;
	}
	if (none == 1) // if no movies matched the search
	{
		printf("No movies were found\n\n");
		system("pause");
		system("cls");
		return 0;
	}

	printf("Choose an attribute to edit: ");
	scanf("%d", &option); // user chooses attribute to edit

	while (option < 1 || option > 9) // checks for valid values
	{
		printf("Choose an attribute to edit: ");
		scanf("%d", &option);
	}
	switch (option) 
	{
	case 1: // edit title
		system("cls");
		printf("Enter a Title: ");
		scanf("%c", &trash);
		fgets((*pHead)->data.title, 20, stdin);
		while ((*pHead)->data.title[index] != '\n')
		{
			++index;
		}
		(*pHead)->data.title[index] = NULL;
		index = 0;
		break;

	case 2: // edit director
		system("cls");
		printf("Enter a Director: ");
		scanf("%c", &trash);
		fgets((*pHead)->data.director, 20, stdin);
		while ((*pHead)->data.director[index] != '\n')
		{
			++index;
		}
		(*pHead)->data.director[index] = NULL;
		index = 0;
		break;

	case 3: // edit description
		system("cls");
		printf("Enter a Description: ");
		scanf("%c", &trash);
		fgets((*pHead)->data.description, 20, stdin);
		while ((*pHead)->data.description[index] != '\n')
		{
			++index;
		}
		(*pHead)->data.description[index] = NULL;
		index = 0;
		break;

	case 4: // edit genre
		system("cls");
		printf("Enter a Genre: ");
		scanf("%c", &trash);
		fgets((*pHead)->data.genre, 20, stdin);
		while ((*pHead)->data.genre[index] != '\n')
		{
			++index;
		}
		(*pHead)->data.genre[index] = NULL;
		index = 0;
		break;

	case 5: // edit runtime (hours)
		system("cls");
		printf("Enter a Run Time (Hours): ");
		scanf("%d", &(*pHead)->data.runtime.hours);
		break;

	case 6: // edit runtime (minutes)
		system("cls");
		printf("Enter a Run Time (Minutes): ");
		scanf("%d", &(*pHead)->data.runtime.minutes);
		break;

	case 7: // edit year
		system("cls");
		printf("Enter a Year: ");
		scanf("%d", &(*pHead)->data.year);
		break;

	case 8: // edit times played
		system("cls");
		printf("Enter Times Played: ");
		scanf("%d", &(*pHead)->data.played);
		break;

	case 9: // edit rating
		system("cls");
		printf("Enter a Rating: ");
		scanf("%d", &(*pHead)->data.rating);
		break;
	}
	return 0;
}

/*
	FUNCTION: rateList()
	DATE MODIFIED: 2/11/20
	INPUT PARAMETERS: Double head pointer to a doubly linked list, double tail pointer to a doubly linked list
	OUTPUT PARAMETERS: Integer (0)
	DESCRIPTION: Allows the user to search for any movie in the list and assign a rating to it from 1-5
*/

int rateList(Node** pHead, Node** pTail)
{
	if (isEmpty(*pHead)) // will not execute if list is empty
	{
		return 0;
	}
	Node* pTemp = NULL;
	int exit = 1, rating = 0, index = 0, iteration = 0;
	char title[20], trash;
	printf("Enter a movie title: ");
	scanf("%c", &trash); // user enters a movie title
	fgets(title, 20, stdin);
	while (title[index] != '\n') // removes \n character
	{
		++index;
	}
	title[index] = NULL;
	index = 0;

	while (exit == 0 && *pHead != *pTail) // while movie hasn't been found and there are still elements in the list
	{
		if (strcmp((*pHead)->data.title, title) == 0) // checks if user input is the same as in the list
		{
			exit = 1;
		}
		if (exit == 0) // if title hasn't been found, iterate the list
		{
			pTemp = *pHead;
			*pHead = (*pHead)->next;
			(*pHead)->previous = pTemp;
			++iteration;
		}
	}
	for (int index = 0; index < iteration; ++index) // iterate back through the list the same ammount as in the last loop
	{
		*pHead = (*pHead)->previous;
	}
	if (exit == 0) // if nothing in the list matched the search
	{
		printf("No movies were found\n\n");
		system("pause");
		system("cls");
		return 0;
	}
	printf("%s\nRating: %d\nEnter a new rating between 1 and 5: ", title, (*pHead)->data.rating);
	scanf("%d", &rating); // user enters rating

	while (rating < 1 || rating > 5) // checks if rating is valid
	{
		printf("Enter a new rating between 1 and 5: ");
		scanf("%d", &rating);
	}

	(*pHead)->data.rating = rating; // replaces old rating with new
	return 0;
}

/*
	FUNCTION: playList()
	DATE MODIFIED: 2/10/20
	INPUT PARAMETERS: Head pointer to a Doubly linked list, Tail pointer to a doubly linked list
	OUTPUT PARAMETERS: none
	DESCRIPTION: "Plays" the selection of movies in the linked list in order.
*/

void playList(Node* pHead, Node* pTail)
{
	if (isEmpty(pHead, pTail)) // will not execute if list is empty
	{
		return 0;
	}

	while (pHead != pTail) // print as long as there are still elements in the list
	{
		printf("Title: %s\n", pHead->data.title);

		printf("Director: %s\n", pHead->data.director);

		printf("Description: %s\n", pHead->data.description);

		printf("Genre: %s\n", pHead->data.genre);

		printf("Run Time (Hours): %d\n", pHead->data.runtime.hours);

		printf("Run Time(Minutes): %d\n", pHead->data.runtime.minutes);

		printf("Year: %d\n", pHead->data.year);

		printf("Times Played: %d\n", pHead->data.played);

		printf("Rating: %d\n", pHead->data.rating);
		system("pause");
		system("cls");

		pHead->previous = pHead; // traverse the list
		pHead = pHead->next;
	}
}