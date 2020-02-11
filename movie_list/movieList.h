/* Name: Bryan Coleman 
 * Date: 6/22/19
 * Section: 2
 * Assignment: 3
 * Due Date: 6/24/19
 * About this project: Tracks movies and specific data about them that you choose to add, and does some things to manipulate them
 * Assumptions: 
 *
 * All work below was performed by Bryan Coleman */
 
class Date
{
	public:
	Date();
	
	void setDate(int setMonth, int setDay, int setYear);
	void printDate() const;
	int getMonth() const;
	int getDay() const;
	int getYear() const;

	private:
  	int month, day, year;
};

class Movie
{
	public:
	Movie();
	
	void setMovieData(char movieTitle[], char movieDirector[], char movieGenre,
	int movieMonth, int movieDay, int movieYear, int numOfWeeks, double weeklyTake[]);
	
	~Movie();
	
	const char * getTitle() const;
	const char * getDirector() const;
	char getGenre() const;
	int getNumWeeks() const;
	double * getWeeklyRevenue() const;
	int getReleaseMonth() const;
	int getReleaseDay() const;
	int getReleaseYear() const;	
	void display() const;
	double getBoxOffice() const;
	
	private:
	char title[75];
	char director[50];
	char genre;
	Date releaseDate;
	int numWeeks;
	double * weeklyRevenue;
};

class MovieList
{

	public:
	MovieList();
	
	~MovieList();
	
	int getNumOfMovies() const;
	
	int getCapacity() const;
	
	void addMovie(char movieTitle[], char movieDirector[], char movieGenre,
	int movieMonth, int movieDay, int movieYear, int numOfWeeks, double weeklyTake[]);
	
	
	void deleteMovie(char movieTitle[]);
	
	void displayList() const;

	void insertMovie(Movie movie, int insertion);
	
	void displayByGenre(char movieGenre) const;
	
	int search(char movieTitle[]) const;
	
	void sortMovies();

	private:
	
	Movie * movieList;
	int numOfMovies;
	int capacity;
};
