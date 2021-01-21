#include<iostream>
#include <fstream>
#include <string>
#include"DList.hpp"
#include"Hash.h"
#include"ListNode.hpp"
#include "BinarySearchTree.h"
#include"Painting.h"
#include"StackADT.h"


using namespace std;
/*
Prints out a greeting for this program
*/
void printGreeting() {
	cout << "Welcome to CIS22C Group 2's Project!" << endl;
	cout << "This program will read in a list of paintings from " << endl;
	cout << "the Minneapolis Institute of Art and build a hash table " << endl;
	cout << "from the list. Group Members: Alex Crawford - team leader " << endl;
	cout << "and main function. Zachery Minshall - screen output, hash function and " << endl;
	cout << "BST algorithms. Yu Wen Ssu - file I/O and test plan. " << endl;
	cout << "James Johnston - undoDelete function." << endl << endl;
}
char readUserIn();
void menuSelect(Hash<Painting>&, BinarySearchTree<Painting>&, BinarySearchTree<Painting>&, Stack<Painting>&);
void printMainMenu();
void insertManager(Hash<Painting>&, BinarySearchTree<Painting>&, BinarySearchTree<Painting>&);
void searchManager(Hash<Painting>& , BinarySearchTree<Painting>&, BinarySearchTree<Painting>& , int compare(const Painting, const Painting), void visit(Painting&));
void printSearchMenu();
void listManager(Hash<Painting>&, BinarySearchTree<Painting>&, BinarySearchTree<Painting>&);
void printListMenu();
void buildStructures(string, Hash<Painting>&, BinarySearchTree<Painting>&, BinarySearchTree<Painting>&);

string getTargetName(string &);
string getMedium(string &);
string getCountry(string &);
string getArtist(string &);

int titleCompare(const Painting, const Painting);
int artistCompare(const Painting, const Painting);

void deleteManager(Hash<Painting>&, BinarySearchTree<Painting>&, BinarySearchTree<Painting>&, Stack<Painting>&);
void undoDelete(Hash<Painting>&, BinarySearchTree <Painting>&, BinarySearchTree <Painting>&, Stack<Painting>&);

void primaryKeySearch(Hash<Painting>& hash);
void secondaryKeySearch(BinarySearchTree<Painting>& titleTree, int compare(const Painting, const Painting), void visit(Painting&));
void visit(Painting& obj);

template<class T>
void printTitle(T&);
template<class T>
void printArtist(T&);




int main() {
	int bucketCount = 29;
	string fileName = "CIS22C_Database_-_Sheet3.csv";
    BinarySearchTree<Painting> titleTree;
    BinarySearchTree<Painting> artistTree;
    Hash<Painting> hash(bucketCount);
	Stack<Painting> deletedPaintings;

	printGreeting();
	buildStructures(fileName, hash, titleTree, artistTree);
    menuSelect(hash,titleTree,artistTree,deletedPaintings);

	return 0;
}
/*
Print out menu options so the user doesn't have to guess what option to select.
TODO: Organize all of the menu funcitons so that the code is more readable.
*/
void printListMenu()
{
	cout << "Print List Menu: " << endl;
	cout << "(U) to Print an unsorted list." << endl;
	cout << "(T) to Print a list sorted by Painting Title." << endl;
	cout << "(A) to Print a list sorted by Artist Name." << endl;
	cout << "(I) to Print an indented list." << endl;
	cout << "(M) to Print the list menu." << endl;
	cout << "(Q) to Return to the Main Menu." << endl;
}
/*
The listManager funciton will continuously prompt the user for an input character.  
TODO: Organize all of the menu funcitons so that the code is more readable.
*/
void listManager(Hash<Painting>& hash, BinarySearchTree<Painting>& titleTree, BinarySearchTree<Painting>& artistTree)
{
	printListMenu();
	char userIn = ' ';
	while(userIn != 'q' && userIn != 'Q') {
		userIn = readUserIn();
		switch (userIn) {
		case 'u':
		case 'U':
			cout << endl << "UNSORTED PAINTINGS (HASH ORDER):" << endl;
			hash.printHash();
			break;
		case 't':
		case 'T':
			cout << endl << "PAINTINGS SORTED BY TITLE:" << endl;
			titleTree.inOrder(printTitle);
			break;
		case 'a':
		case 'A':
			cout << endl << "PAINTINGS SORTED BY ARTIST NAME:" << endl;
			artistTree.inOrder(printArtist);
			break;
		case 'i':
		case 'I':
			cout << endl << "PAINTINGS AS AN INDENTED LIST (TITLE BST):" << endl;
			titleTree.printTree(printTitle);
			break;
		case 'm': // Print list menu
		case 'M': printListMenu();
			break;
		case 'q':
		case 'Q':
			break;
		default:
			cout << userIn << " is not a valid selection." << endl;
			userIn = ' ';
			break;
		}
	}
}
/*
The printSearchMenu function will display the list menu choices so the user can easily navigate the program.
TODO: Organize all of the menu funcitons so that the code is more readable.
*/
void printSearchMenu()
{
	cout << "Print Search Menu: " << endl;
	cout << "(A) to Search by painting artist." << endl;
	cout << "(T) to Search by painting title." << endl;
	cout << "(M) to Print the search menu." << endl;
	cout << "(Q) to Return to the main menu." << endl;
}
/*
The searchManager function will take in a hash of paintings, two BST of paintings, a compare function, and a visit function. It will
then print out the search menu and loop through the search options.
TODO: Organize all of the menu funcitons so that the code is more readable.
*/
void searchManager(Hash<Painting>& hash, BinarySearchTree<Painting>& titleTree, BinarySearchTree<Painting>& artistTree, int compare(const Painting, const Painting), void visit(Painting&)) {
	printSearchMenu();
	char userIn = ' ';
	while (userIn != 'q' && userIn != 'Q') {
		userIn = readUserIn();
		switch (userIn) {
		case 'a': // Search by artist name
		case 'A': secondaryKeySearch(artistTree, compare, visit);
			break;
		case 't': // Search by painting title
		case 'T': primaryKeySearch(hash);
			break;
		case 'm': // Print search menu
		case 'M': printSearchMenu();
			break;
		case 'q': // Return to main menu
		case 'Q':
			break;
		default:
			cout << userIn << " is not a valid selection." << endl;
			userIn = ' ';
			break;
		}
	}
}

/*
The primaryKeySearch will take in a hash of paintings and will prompt the user to enter a painting
title.  It will then hash the title and see if there is a matching title in that hash bucket and 
display the results.
TODO: Move this to the painting class, if possible.
*/
void primaryKeySearch(Hash<Painting>& hash)
{
    string title;
    cout << "Please enter the title of a painting: ";
	cin.ignore();
	getline(cin, title);
    
    Painting data(title, "", "", "", "");
    Painting returnedData;
    
    if(hash.search(title, returnedData)) {
        cout << returnedData;
		cout << title << " was found in the database." << endl;
    }
	else {
		cout << title << " was not found in the database." << endl;
	}
}
/*
The secondaryKeySearch function will take in a BST of paintings, a compare function, and a visit function.  
It will then search the BST for the artist name and print out the results to the console.
TODO: Move this to the painting class if possible.
*/
void secondaryKeySearch(BinarySearchTree<Painting>& artistTree, int compare(const Painting, const Painting), void visit(Painting&))
{
	Painting artistToFind("", "", "", "", "");
	Painting returnItem("", "", "", "", "");
	string artist = "";

	cout << "Please enter the name of an artist: " << endl;
	cin.ignore();
	getline(cin, artist);
	artistToFind.setArtist(artist);
	if (artistTree.getEntry(artistToFind, returnItem, compare)) {
		cout << "The following paintings were made by " << artist << ":" << endl;
		artistTree.getAllEntry(artistToFind, compare, visit);
	}
	else
		cout << "No paintings were found by " << artist << "." << endl;
}
/*
The visit function will print out the data from the painting object. 
TODO:Move this into the painting class where it belogs.
*/
void visit(Painting& obj)
{
    cout << "Title: " << obj.getTitle() << endl;
    cout << "Artist: " << obj.getArtist() << endl;
    cout << "Year Painted: " << obj.getYearPainted() << endl;
    cout << "Medium: " << obj.getMedium() << endl;
	cout << "Country: " << obj.getCountry() << endl << endl;
}

/*
The readUserIn function will prompt the user for a character for menu selection. It will
then return the character for use by the menu that called the function.
*/
char readUserIn() {
	char userIn = ' ';
	while (userIn == ' ')
	{
		cout << "Please enter a selection: " << endl;
		cin >> userIn;
		if (!(userIn >= 'a' && userIn <= 'z') && !(userIn >= 'A' && userIn <= 'Z')) {
			userIn = ' ';
		}
	}
	return userIn;
}
/*
The printMainMenu function will print out all the optoins for the main menu.
TODO: organize all of the printMenu functions.
*/
void printMainMenu()
{
	cout << "Main Menu: " << endl;
	cout << "(A) to Insert into the database." << endl;
	cout << "(D) to Delete from the database." << endl;
	cout << "(L) to Print a list from the database." << endl;
	cout << "(S) to Search the database." << endl;
	cout << "(T) to Print the hash table statistics." << endl;
	cout << "(U) to Undo your last delete." << endl;
	cout << "(W) to Write the database to a text file." << endl;
	cout << "(M) to Print the Main Menu again." << endl;
	cout << "(Q) to Quit." << endl;
}
/*
The menuSelect function will continuously prompt the user for an input to:
	(A) to Insert into the database.
	(D) to Delete from the database.
	(L) to Print a list from the database.
	(S) to Search the database.
	(T) to Print the hash table statistics.
	(U) to Undo your last delete.
	(W) to Write the database to a text file.
	(M) to Print the Main Menu again.
	(Q) to Quit.
TODO: Organize all of the menu funcitons so that the code is more readable.
	*/
void menuSelect(Hash<Painting>& hash, BinarySearchTree<Painting>& titleTree, BinarySearchTree<Painting>& artistTree, Stack<Painting>& deletedStack) {
	printMainMenu();
	char userIn = ' ';
	while (userIn != 'q' && userIn != 'Q') {
		userIn = readUserIn();
		switch (userIn) {
		case 'a': //Adds a painting to the hash table and BST.
		case 'A': insertManager(hash, titleTree, artistTree);
			break;
		case 'd': //Deletes a painting from the hash table and BST.
		case 'D': deleteManager(hash, titleTree, artistTree, deletedStack);
			break;
		case 'l': //Lists the data either sorted by primary or secondary key, or unsorted.
		case 'L': listManager(hash, titleTree, artistTree);
			break;
		case 's': //Search for one element using the title or artist.
		case 'S': searchManager(hash, titleTree, artistTree, artistCompare, visit);
			break;
		case 't': //Print the Statistics of the Hash
		case 'T': 
			hash.printCollisions();
			hash.printLoadFactor();
			break;
		case 'u': //Undo the most recent delete action.
		case 'U': undoDelete(hash, titleTree, artistTree, deletedStack);
			break;
		case 'w': //Write the hash list to file.
		case 'W': hash.writeToFile();
			break;
		case 'm': //Print the main menu
		case 'M': printMainMenu();
			break;
		case 'q': // Quit
		case 'Q':
			break;
		default:
			cout << userIn << " is not a valid selection." << endl;
			userIn = ' ';
			break;
		}
	}
	cout << "Thanks for using our program!" << endl;
	hash.writeToFile();
}
/*
The titleCompare function recieves two Painting objects.  It will return an int based
on that comparison.
*/
int titleCompare(const Painting p1, const Painting p2)
{
	int result;
	if (p1.getTitle() == p2.getTitle()) {
		result = 0;
	}
	else if (p1.getTitle() > p2.getTitle()) {
		result = 1;
	}
	else if (p1.getTitle() < p2.getTitle()){
		result = -1;
	}
	return result;
}
/*
The artistCompare function recieves two Painting objects.  It will return an int based
on that comparison.
*/
int artistCompare(const Painting p1, const Painting p2)
{
    int result;
    if(p1.getArtist() == p2.getArtist()) {
		result = 0;
	}
    else if(p1.getArtist() > p2.getArtist()) {
		result = 1;
	}
	else if (p1.getArtist() < p2.getArtist()) {
		result = -1;
	}
	return result;
}

/*
The buildStructuers function will recieve a string, a Hash<Painting>, and two BST<Painting>s it will then read in the filename string and 
use that file to build the hash table of paintings, the BST sorted by title (primary key BST) and by artist (secondary key BST).
*/
void buildStructures(string fileName, Hash<Painting>& hash, BinarySearchTree<Painting>& titleTree, BinarySearchTree<Painting>& artistTree)
{
    ifstream inFile;
    string data, line;
    string title, medium, country, artist;

    inFile.open(fileName);

    if (!inFile) {
        cout << "Error opening the input file: "" << fileName << """ << endl;
        exit(EXIT_FAILURE);
    }

    while (getline(inFile, data))
    {
        Painting* painting = new Painting;

        title = getTargetName(data);
        painting->setTitle(title);
        medium = getMedium(data);
        painting->setMedium(medium);
        country = getCountry(data);
        painting->setCountry(country);
        artist = getArtist(data);
        painting->setArtist(artist);
        painting->setYearPainted(data);

        hash.insertItem(title, *painting);
        titleTree.insert(*painting, titleCompare);
		artistTree.insert(*painting, artistCompare);
    }
    inFile.close();
}
/*
The getArtist function will recieve a string input by reference and will parse 
that string to find the artist name. It will then remove the artist name from 
the string and return the artist name.  
*/
string getArtist(string & data)
{
    size_t firstComa = data.find(',', 0);
    string targetArtist = data.substr(0, firstComa);
    data = data.substr(firstComa + 1, data.length() - targetArtist.length());
    
    return targetArtist;
}
/*
The getTargetName function will recieve a string input by reference and wll
parse the string to find the title of the painting.  It will then remove the
title from the string and retrun the title string.
*/
string getTargetName(string & data)
{
    size_t testComa = data.find(',', 0);
    size_t firstComa = 0;

    if(data[testComa + 1] != ' ')
        firstComa = testComa;
    else
        firstComa = data.find(',', testComa + 1);
    
    string targetName = data.substr(0, firstComa);
    data = data.substr(firstComa + 1, data.length() - targetName.length());
    return targetName;
}
/*
The getMedium function will recieve a string input by reference and wll
parse the string to find the medium of the painting.  It will then remove the
medium from the string and retrun the meduim string.
*/
string getMedium(string & data)
{
    size_t testComa = data.find(',', 0);
    size_t firstComa = 0;
    
    if(data[testComa + 1] != ' ')
        firstComa = testComa;
    else
    {
        while(data[testComa + 1] == ' ')
            testComa = data.find(',', testComa + 1);
        firstComa = testComa;
    }
    string targetMedium = data.substr(0, firstComa);
    data = data.substr(firstComa + 1, data.length() - targetMedium.length());
    
    return targetMedium;
}
/*
The getCountry function will recieve a string input by reference and will
parse the string to find the country of origin for the painting.  It will 
then remove the country from the string and retrun the cournty string.
*/
string getCountry(string & data)
{
    size_t firstComa = data.find(',', 0);
    string targetCountry = data.substr(0, firstComa);
    data = data.substr(firstComa + 1, data.length() - targetCountry.length());
    
    return targetCountry;
}
/*
prints out the title of the painting.
TODO: Move this to the painting class.
*/
template<class T>
void printTitle(T& painting)
{
	cout << painting.getTitle() << endl;
}
/*
prints out the artist of the painting.
TODO: move this to the painting class.
*/
template<class T>
void printArtist(T& painting)
{
		cout << painting.getArtist() << " - " << painting.getTitle() << endl;
}
/*
The deleteManager function will recieve a Hash<Painting>, two BST<Painting>s, and a Stack<Painting>.
It will then prompt the user for a title of a painting.  Then it will search the hash for that painting.  
Finally it will add the item to the stack of deleted items, remove it from the hash and both BSTs.
*/
void deleteManager(Hash<Painting>& hash, BinarySearchTree<Painting>& titleTree, BinarySearchTree<Painting>& artistTree, Stack<Painting>& deletedStack)
{
	Painting returnedItem;
	string title = "";
	cout << "Please enter the title of the painting you want to delete: ";
	cin.ignore();
	getline(cin, title);
	returnedItem.setTitle(title);
	if (hash.search(title, returnedItem)) {
		deletedStack.push(returnedItem);
		hash.deleteItem(title, returnedItem);
		titleTree.remove(returnedItem, titleCompare, titleCompare);
		artistTree.remove(returnedItem, artistCompare, titleCompare);
		cout << title << " was deleted successfully." << endl;
	}
	else
		cout << title << " does not exist in the database." << endl;
}
/*
The undoDelete function will take in a Hash<Painting>, two BST<Painting>, and a Stack<Painting>.  It will then pop the top of the 
stack and search the hash for that item.  If it is not in the hash it will enter the item into the hash and both BSTs.
*/
void undoDelete(Hash<Painting>& hash, BinarySearchTree <Painting>& titleTree, BinarySearchTree <Painting>& artistTree, Stack<Painting>& deletedlist)
{
	if (deletedlist.isEmpty()) {
		cout << "There are no deleted items." << endl;
		return;
	}
	Painting temp;
	deletedlist.pop(temp);
	if (!hash.search(temp.getTitle(), temp)) {
		hash.insertItem(temp.getTitle(), temp);
		titleTree.insert(temp, titleCompare);
		artistTree.insert(temp, artistCompare);
		cout << temp.getTitle() << " inserted successfully." << endl;
	}
	else
		cout << temp.getTitle() << " already exists in the database" << endl;
}
/*
The insertManager function will take a hash<Painting> and two BST<Painting>.  It will then prmpt the user to enter in all of the 
info for the new painting.  Hash the title and insert it into the Hash and both BSTs.*/
void insertManager(Hash<Painting>& hash, BinarySearchTree<Painting>& titleTree, BinarySearchTree<Painting>& artistTree)
{
	Painting insertItem("", "", "", "", "");
	string title = "";
	string artist = "";
	string yearPainted = "";
	string country = "";
	string medium = "";
	cout << "Please enter the title of the painting you want to insert: ";
	cin.ignore();
	getline(cin, title);
	insertItem.setTitle(title);
	if (!hash.search(title, insertItem)) {
		cout << "Please enter the artist of the painting you want to insert: ";
		getline(cin, artist);
		insertItem.setArtist(artist);
		cout << "Please enter the year the painting was made: ";
		getline(cin, yearPainted);
		insertItem.setYearPainted(yearPainted);
		cout << "Please enter the country the painting was made in: ";
		getline(cin, country);
		insertItem.setCountry(country);
		cout << "Please enter the medium of the painting: ";
		getline(cin, medium);
		insertItem.setMedium(medium);

		cout << insertItem;

		hash.insertItem(title, insertItem);
		titleTree.insert(insertItem, titleCompare);
		artistTree.insert(insertItem, artistCompare);
		
		cout << title << " inserted successfully." << endl;
	}
	else
		cout << title << " already exists in the database." << endl;
}