/* Name: Bryan Coleman 
 * Date: 6/22/19
 * Section: 2
 * Assignment: 3
 * Due Date: 6/24/19
 * About this project: Tracks movies and specific data about them that you choose to add, and does some things to manipulate them
 * Assumptions: 
 *
 * All work below was performed by Bryan Coleman */

#include<iostream>
#include<cstring>
#include<iomanip>
#include"movieList.h"
using namespace std;

Date::Date()	//Date constructor
{
	month = 6;
	day = 21;
	year = 2019;
}

void Date::setDate(int setMonth, int setDay, int setYear)	//function to set the date for a given movie
{
	month = setMonth;
	day = setDay;
	year = setYear;
	if(month < 1 || day < 1 || year < 1)					//if any of the numbers are negative set default
	{
		month = 6;
		day = 21;
		year = 2019;
	}
}

void Date::printDate() const		//function to print date
{
	if(month < 10)					//if number is less then 10 put a zero up front to give the correct mm/dd/yyyy format
	{
		cout << "0";
		cout << month;
	}
	else
		cout << month;
	cout << "/";
	if(day < 10)
	{
		cout << "0";
		cout << day;
	}
	else
		cout << day;
	cout << "/";
	cout << year << endl;
}

int Date::getMonth() const 			//month accessor
{
	return month;
}

int Date::getDay() const			//day accessor
{
	return day;
}
int Date::getYear() const			//year accessor
{
	return year;
}

Movie::Movie()						//movie constructor
{
	title[75] = 0;
	director[50] = 0;
	genre = '\0';
	numWeeks = 0;
	weeklyRevenue = NULL;
}
	
void Movie::setMovieData(char movieTitle[], char movieDirector[], char movieGenre,
int movieMonth, int movieDay, int movieYear,int numOfWeeks, double weeklyTake[])		//function to set data for a movie
{
	strcpy(title, movieTitle);
	strcpy(director, movieDirector);
	genre = toupper(movieGenre);
	numWeeks = numOfWeeks;
	weeklyRevenue = new double[numOfWeeks];
	releaseDate.setDate(movieMonth,movieDay,movieYear);
	for(int i = 0; i < numOfWeeks; i++)
		weeklyRevenue[i] = weeklyTake[i];
}

Movie::~Movie()							//movie destructor
{
	if( weeklyRevenue != NULL)
	{
		delete [] weeklyRevenue;
		weeklyRevenue = NULL;
	}
}

const char * Movie::getTitle() const	//title accessor
{
	return title;
}

const char * Movie::getDirector() const	//director accessor
{
	return director;
}

char Movie::getGenre() const			//genre accessor
{
	return genre;
}

int Movie::getReleaseMonth() const		//release date month accessor
{
	return releaseDate.getMonth();
}

int Movie::getReleaseDay() const		//release date day accessor
{
	return releaseDate.getDay();
}

int Movie::getReleaseYear()	const		//release date year accessor
{
	return releaseDate.getYear();
}

int Movie::getNumWeeks() const			//number of weeks accessor
{
	return numWeeks;
}

double * Movie::getWeeklyRevenue() const	//weekly revenue accessor
{
	return weeklyRevenue;
}

void Movie::display()	const			//function to display the movies in the list
{
	cout << "Title: " << title << endl;
	cout << "Director: " << director << endl;
	cout << "Genre: ";
	if(genre == 'A')
		cout << "Action";
	if(genre == 'C')
		cout << "Comedy";
	if(genre == 'D')
		cout << "Drama";
	if(genre == 'F')
		cout << "Fantasy";
	if(genre == 'H')
		cout << "Horror";
	if(genre == 'S')
		cout << "Sci-Fi";
	if(genre == 'T')
		cout << "Thriller";
	cout << "\nRelease Date: ";
	releaseDate.printDate();								//call printDate
	cout << "Weeks since release: " << numWeeks << endl;
	cout << "Box Office: ";
	cout << fixed << showpoint << setprecision(2);
	cout << getBoxOffice() << endl << endl;					//call box office total
}

double Movie::getBoxOffice() const			//box office accessor
{
	double result = 0.0;
	for(int i = 0; i < numWeeks; i++)
		result += weeklyRevenue[i];
	return result;
}

MovieList::MovieList()						//movie list constructor
{
	numOfMovies = 0;
	capacity = 5;
	movieList = new Movie[capacity];
}

MovieList::~MovieList()						//movie list destructor
{
	if(movieList != NULL)
	{
		delete [] movieList;
		movieList = NULL;
	}
}

int MovieList::getNumOfMovies() const		//number of movies accessor
{
	return numOfMovies;
}

int MovieList::getCapacity() const			//capacity accessor
{
	return capacity;
}

void MovieList::addMovie(char movieTitle[], char movieDirector[], char movieGenre,
int movieMonth, int movieDay, int movieYear, int numOfWeeks, double weeklyTake[])		//function to add movie to movie list
{
	movieList[numOfMovies].setMovieData(movieTitle, movieDirector, movieGenre, 
	movieMonth, movieDay, movieYear, numOfWeeks, weeklyTake);							//call setmoviedata to hard copy data
	cout << "Movie added" << endl << endl;
	numOfMovies++;
	if(numOfMovies == capacity)															//if number of movies is equal to capacity increase by 5
	{
		Movie tempMovieList[numOfMovies];												//create a temp Movie array
		capacity += 5;
		for(int i = 0; i < numOfMovies; i++)
		{
			char tempTitle[75];															//create temp title and temp director c strings
			char tempDirector[50];
			strcpy(tempTitle, movieList[i].getTitle());
			strcpy(tempDirector, movieList[i].getDirector());
			
			tempMovieList[i].setMovieData(tempTitle, tempDirector, 						
			movieList[i].getGenre(), movieList[i].getReleaseMonth(),
			movieList[i].getReleaseDay(), movieList[i].getReleaseYear(),
			movieList[i].getNumWeeks(), movieList[i].getWeeklyRevenue());				//call setmoviedata to give the temp array the values of movielist
		}
		delete [] movieList;															//delete the movie list
		movieList = new Movie[capacity];												//create a new one with the new capacity
		for(int i = 0; i < numOfMovies; i++)
		{
			char tempTitle[75];
            char tempDirector[50];
			strcpy(tempTitle, tempMovieList[i].getTitle());
			strcpy(tempDirector, tempMovieList[i].getDirector());
			
			movieList[i].setMovieData(tempTitle, tempDirector, 
			tempMovieList[i].getGenre(), tempMovieList[i].getReleaseMonth(), 
			tempMovieList[i].getReleaseDay(), tempMovieList[i].getReleaseYear(),
			tempMovieList[i].getNumWeeks(), tempMovieList[i].getWeeklyRevenue());		//give the new array with the new capacity the values from the temp array
		}

	}

}


void MovieList::insertMovie(Movie movie, int insertion)									//function to insert movie into a specific index
{
	char tempTitle[75];
	char tempDirector[50];
	strcpy(tempTitle, movie.getTitle());
	strcpy(tempDirector, movie.getDirector());
	
	if(insertion < 0 || insertion > numOfMovies)
		cout << "Failed to insert movie" << endl;
	else
	{
		numOfMovies++;
		if(numOfMovies == capacity)														//do the same thing above if we need to add to the capacity																										
		{
			Movie tempMovieList[numOfMovies];
			capacity += 5;
			for(int i = 0; i < numOfMovies; i++)
			{
				char tempTitle[75];
				char tempDirector[50];
				strcpy(tempTitle, movieList[i].getTitle());
				strcpy(tempDirector, movieList[i].getDirector());
				
				tempMovieList[i].setMovieData(tempTitle, tempDirector, 
				movieList[i].getGenre(), movieList[i].getReleaseMonth(), 
				movieList[i].getReleaseDay(), movieList[i].getReleaseYear(),
				movieList[i].getNumWeeks(), movieList[i].getWeeklyRevenue());
			}
			delete [] movieList;
			movieList = new Movie[capacity];
			for(int i = 0; i < numOfMovies; i++)
			{
					char tempTitle[75];
					char tempDirector[50];
					strcpy(tempTitle, tempMovieList[i].getTitle());
					strcpy(tempDirector, tempMovieList[i].getDirector());
					
					movieList[i].setMovieData(tempTitle, tempDirector, 
					tempMovieList[i].getGenre(), tempMovieList[i].getReleaseMonth(), 
					tempMovieList[i].getReleaseDay(), tempMovieList[i].getReleaseYear(),
					tempMovieList[i].getNumWeeks(), tempMovieList[i].getWeeklyRevenue());
			}
		}		

		for(int i = numOfMovies; i > insertion; i--)									//this shift the array over the "right" untill we get to the insertion
			movieList[i] = movieList[i - 1];
		
		movieList[insertion].setMovieData(tempTitle, tempDirector, movie.getGenre(),
		movie.getReleaseMonth(), movie.getReleaseDay(), movie.getReleaseYear(),
		movie.getNumWeeks(), movie.getWeeklyRevenue());									//add the movie to correct insertion index
		
		cout << "Movie added" << endl << endl;
	}

}

void MovieList::deleteMovie(char movieTitle[])											//function to delete movie
{	
	int counter = 0;
	int sevenApart = 0; 
	for(int i = 0; i < numOfMovies; i++)
	{
		if(strcmp(movieList[i].getTitle(),movieTitle) == 0)
		{
			for(int j = i; j < numOfMovies; j++)
				movieList[j] = movieList[j + 1];
			numOfMovies--;
			int sevenApart = capacity - numOfMovies;
			counter++;
		}
	}

	if(sevenApart == 7)																	//if numofmovies and capacity are ever 7 apart(3 is technically 4)
	{																					//subtract the capacity by 5 and do the same as above
		Movie tempMovieList[numOfMovies];
		capacity -= 5;
		for(int i = 0; i < numOfMovies; i++)
		{
			char tempTitle[75];
			char tempDirector[50];
			strcpy(tempTitle, movieList[i].getTitle());
			strcpy(tempDirector, movieList[i].getDirector());
			
			tempMovieList[i].setMovieData(tempTitle, tempDirector,
			movieList[i].getGenre(), movieList[i].getReleaseMonth(),
			movieList[i].getReleaseDay(), movieList[i].getReleaseYear(),
			movieList[i].getNumWeeks(), movieList[i].getWeeklyRevenue());
		}
		delete [] movieList;
		movieList = new Movie[capacity];
		for(int i = 0; i < numOfMovies; i++)
		{
			char tempTitle[75];
			char tempDirector[50];
			strcpy(tempTitle, tempMovieList[i].getTitle());
			strcpy(tempDirector, tempMovieList[i].getDirector());
			movieList[i].setMovieData(tempTitle, tempDirector, 
			tempMovieList[i].getGenre(), tempMovieList[i].getReleaseMonth(),
			tempMovieList[i].getReleaseDay(), tempMovieList[i].getReleaseYear(),
			tempMovieList[i].getNumWeeks(), tempMovieList[i].getWeeklyRevenue());
		}

	}
	if(counter == 0)
		cout << "Movie not found" << endl << endl;
	else
		cout << "Movie deleted" << endl << endl;
}

void MovieList::displayList() const 								//function to display the list
{
	int counter = 1;												//counter to cout movie 1, movie 2, and etc..
	for(int i = 0; i < numOfMovies; i++)
	{
		cout << "Movie " << counter << ":" << endl;
		movieList[i].display();
		counter++;
	}
}

void MovieList::displayByGenre(char movieGenre) const				//function to display by the genre
{
	int counter = 1;
	for(int i = 0; i < numOfMovies; i++)
	{
		if(movieList[i].getGenre() == movieGenre)
		{
			cout << "Movie " << counter << ":" << endl;
			movieList[i].display();
			counter++;
		}
	}
}

int MovieList::search(char movieTitle[]) const						//function to search for a title
{	
	for(int i = 0; i < numOfMovies; i++)
	{
		if(strcmp(movieList[i].getTitle(), movieTitle) == 0)
		{
			return i;
		}
	}
	return -1;
}	
	
void MovieList::sortMovies()							//function to sort movies extra credit
{
	
	Movie tempMovieList[numOfMovies];					//temp movie array
	bool keepGoing;										//This is a bubble sort function that i learned and referenced from a programming 1 program

	for(int i = 0; i < numOfMovies - 1; i++)			//runs through enough times to be efficient
	{
		keepGoing = false;								//sets keepGoing to false always first
		for(int j = 0; j < numOfMovies - i - 1; j++)	//runs through the program just enough times to be efficient again
		{
			char tempTitle[75];
            char tempTitleTwo[75];
			strcpy(tempTitle, movieList[j].getTitle());
			strcpy(tempTitleTwo, movieList[j+1].getTitle());
			
			if(strcmp(tempTitle, tempTitleTwo) > 0)					//compares two titles to see if one is larger then the other
			{
				char tempTitle[75];
				char tempDirector[50];
				strcpy(tempTitle, movieList[j].getTitle());
				strcpy(tempDirector, movieList[j].getDirector());
				
				tempMovieList[j].setMovieData(tempTitle, tempDirector,
				movieList[j].getGenre(), movieList[j].getReleaseMonth(), 
				movieList[j].getReleaseDay(), movieList[j].getReleaseYear(),
				movieList[j].getNumWeeks(), movieList[j].getWeeklyRevenue());			//tempmovielist = to movielist[j]

				strcpy(tempTitle, movieList[j+1].getTitle());
				strcpy(tempDirector, movieList[j+1].getDirector());
				
				movieList[j].setMovieData(tempTitle, tempDirector,
				movieList[j+1].getGenre(), movieList[j+1].getReleaseMonth(),
				movieList[j+1].getReleaseDay(), movieList[j+1].getReleaseYear(),
				movieList[j+1].getNumWeeks(), movieList[j+1].getWeeklyRevenue());		//movielist[j] = movielist[j+1]
				
				strcpy(tempTitle, tempMovieList[j].getTitle());
				strcpy(tempDirector, tempMovieList[j].getDirector());
				
				movieList[j+1].setMovieData(tempTitle, tempDirector, 
				tempMovieList[j].getGenre(), tempMovieList[j].getReleaseMonth(), 
				tempMovieList[j].getReleaseDay(), tempMovieList[j].getReleaseYear(),
				tempMovieList[j].getNumWeeks(), tempMovieList[j].getWeeklyRevenue());	//movielist[j+1] = tempmovielist
	
				keepGoing = true;														//set keepgoing to true to run again
			}
		}

		if(keepGoing == false)															//break if it didnt have to loop
			break;
	}
}

