// Specification file for the Painting class
// Written By: Zachary Minshall
// IDE: MSVS

#include <iostream>

// Forward Declaration
class Painting;

// Function Prototype for Overloaded Stream Operator
// CURRENTLY UNFINISHED (Implement according to your output need in main())
std::ostream& operator << (std::ostream&, const Painting&); 

using std::string;

class Painting
{
private:
	string title;
	string artist;
	string yearPainted; 
	string medium;
	string country;
public:
	Painting();
	Painting(string t, string a, string y, string m, string c);
	Painting(const Painting&);

	// Setters
	void setTitle(string t) { title = t; }
	void setArtist(string a) { artist = a; }
	void setYearPainted(string y) { yearPainted = y; }
	void setMedium(string m) { medium = m; }
	void setCountry(string c) { country = c; }

	// Getters
	string getTitle() const { return title; }
	string getArtist() const { return artist; }
	string getYearPainted() const { return yearPainted; }
	string getMedium() const { return medium; }
	string getCountry() const { return country; }

	// Input validation
	bool validateWords(const string&);
	bool validateYear(const string&);
	void formatWords(string&);

	// Overloaded Operators
	bool operator < (const Painting&);
	bool operator == (const Painting&);

	// Friends
	friend std::ostream& operator << (std::ostream&, const Painting&);
};