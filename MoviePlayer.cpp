/**********************************************
 * File: Proj5.cpp
 * Project: CMSC 202 Project 5, Spring 2024
 * Author: Eden Zhang
 * Date: 4/20/2024
 * Section: 30/34
 * E-Mail: ezhang1@umbc.edu
 * 
 * MoviePlayer.cpp
 * Main driver file for the MoviePlayer program
 * 
*****************************************************/
#include "MoviePlayer.h"

// MoviePlayer
// Default constructor and sets filename
MoviePlayer::MoviePlayer()
{
    m_filename = "proj5_movies.txt";
}

// MoviePlayer
// Overloaded constructor and sets filename to passed value
MoviePlayer::MoviePlayer(string filename)
{
    m_filename = filename;
}

// ~MoviePlayer
// Destructor
MoviePlayer::~MoviePlayer()
{
    // Iterates through the catalog and deallocates each Movie object
    for (vector<Movie*>::iterator it = m_movieCatalog.begin(); it != m_movieCatalog.end(); it++)
    {
        delete *it;
        *it = nullptr;
    }
}

// LoadCatalog
// Loads file, takes info, constructs Movies, adds to catalog
void MoviePlayer::LoadCatalog()
{
    char const DELIMITER = ';';  // Delimiter for the txt data file

    // File I/O variables
    ifstream movies;
    string data;

    // Counter for the number of files loaded
    int loaded = 0;

    // Movie object variables
    string title;
    string rating;
    string genre;
    int year;
    string director;
    string star;
    long budget;
    long gross;
    string studio;
    int runtime;

    // Opens file
    movies.open(m_filename);

    // Checks that the file is actually open
    if (movies.is_open())
    {
        // Loops through the file and gradually
        // grabs the data to build a Movie
        while (getline(movies, data, DELIMITER))
        {   
            // Getlines for each variable of data
            title = data;

            getline(movies, data, DELIMITER);
            rating = data;

            getline(movies, data, DELIMITER);
            genre = data;

            getline(movies, data, DELIMITER);
            year = stoi(data);

            getline(movies, data, DELIMITER);
            director = data;

            getline(movies, data, DELIMITER);
            star = data;

            getline(movies, data, DELIMITER);
            budget = stoul(data);

            getline(movies, data, DELIMITER);
            gross = stoul(data);

            getline(movies, data, DELIMITER);
            studio = data;

            getline(movies, data);
            runtime = stoi(data);

            // Constructs a Movie object and adds to the catalog vector
            m_movieCatalog.push_back(new Movie(title, rating, genre, year, 
            director, star, budget, gross, studio, runtime));

            // Counts each movie that's loaded.
            loaded++;
        }
    } else 
    {
        cout << "Unable to open file." << endl;
    }

    movies.close();
    cout << loaded << " movie files loaded." << endl;
}

// MainMenu
// Displays Menu, user picks their action
void MoviePlayer::MainMenu()
{
    int user = -1;

    // Manages the menu in a loop until player exits
    while (user != 6)
    {
        // Menu
        cout << "What would you like to do?" << endl;
        cout << "1. Display Movie by Type and Year" << endl;
        cout << "2. Add Movie to Playlist" << endl;
        cout << "3. Display Playlist" << endl;
        cout << "4. Sort Playlist by Year" << endl;
        cout << "5. Search for Movie" << endl;
        cout << "6. Quit" << endl;
        cin >> user;

        // Bound checking
        while (user < 1 || user > 6)
        {
            cout << "Please choose a valid option from the menu." << endl;
            cin >> user;
        }

        // Switch statement for managing menu actions
        switch (user)
        {
            case 1:
            DisplayMovie();
            break;

            case 2:
            AddMovie();
            break;

            case 3:
            DisplayPlaylist();
            break;

            case 4:
            SortPlaylist();
            break;

            case 5:
            SearchMovie();
            break;

            case 6:
            cout << "Thank you for using MoviePlayer!" << endl;
            break;
        }
    }
}

// DisplayMovie
// Displays all movies in the catalog
int MoviePlayer::DisplayMovie()
{
    int year;
    string genre;
    int count = 0;
    int index = 0;

    // Asks user for the year 
    cout << "What year would you like to display? (1980-2020)" << endl;
    cin >> year;

    // Bound checking
    while (year < MIN_YEAR || year > MAX_YEAR)
    {
        cout << "Please pick a year within range." << endl;
        cin >> year;
    }
    // Display and asks user for target genre
    cout << "**********" << year << "**********" << endl;
    cout << "What genre would you like to display?" << endl;
    cin >> genre;
    cout << "**********" << genre << "**********" << endl;
    cout << "MOVIES TOTAL: " << m_movieCatalog.size() << endl;

    // Iterate through the movie catalog
    for (vector<Movie*>::iterator it = m_movieCatalog.begin(); it != m_movieCatalog.end(); it++)
    {
        if ((*it)->GetGenre() == genre && (*it)->GetYear() == year)
        {
            cout << index << " " << *(*it) << endl;
            count++;
        }
        index++;
    }
    cout << count << " movies found." << endl;

    return count;
}

// AddMovie
// Displays movies, user chooses, adds movie to playlist
void MoviePlayer::AddMovie()
{
    // Displays the current playlist and guides user's actions
    int userIndex;
    int index = 0;

    DisplayPlaylist();
    cout << "Choose the movie you would like to add to the playlist." << endl;

    // Displays movie and asks user for the number of movie to add
    DisplayMovie();
    cout << "Enter the number of the movie you would like to add:" << endl;
    cin >> userIndex;

    // Bound check
    while (userIndex < 0 || userIndex > int(m_movieCatalog.size()))
    {
        cout << "Please enter a number in range." << endl;
        cin >> userIndex;
    }

    // Iterates through the vector until it finds the chosen movie
    for (vector<Movie*>::iterator it = m_movieCatalog.begin(); it != m_movieCatalog.end(); it++)
    {
        // Adds the movie to the Queue
        if (index == userIndex)
        {
            m_playList.PushBack(*it);
            cout << *(*it) << " added to playlist." << endl;
            return;
        }
        index++;
    }

    cout << "Unable to add movie to playlist." << endl;
}

// DisplayPlaylist
// Checks empty, displays movies in playlist in numbered list
void MoviePlayer::DisplayPlaylist()
{
    int listNum = 1;

    // Checks if the playlist has movies in it
    if (m_playList.IsEmpty() == false)
    {
        // Loops through the playlist linked list
        for (int i = 0; i < m_playList.GetSize(); i++)
        {
            // Displays the movies in a numbered list
            cout << listNum << ". " << *(m_playList.At(i)) << endl;
            listNum++;
        }
    } else 
    {
        cout << "The playlist is currently empty." << endl;
    }
}

// SortPlaylist
// Calls the sort function for Queue to sort the list by year
void MoviePlayer::SortPlaylist()
{
    if (m_playList.GetSize() >= 2)
    {
        m_playList.Sort();
        cout << "Done sorting by year." << endl;
    } else 
    {
        cout << "The playlist needs at least two movies to sort." << endl;
    }
}

// StartPlayer
// Calls the functions to start the program
void MoviePlayer::StartPlayer()
{
    LoadCatalog();
    MainMenu();
}

void MoviePlayer::SearchMovie()
{
    int user = -1;
    string word;
    int year;
    long minProfit;
    long earnings;
    int listNum = 1;

    // Menu for Search movie
    cout << "What do you want to search by?" << endl;
    cout << "1. Word in Title or Director" << endl;
    cout << "2. Year" << endl;
    cout << "3. Earnings" << endl;
    cin >> user;

    // Bound check
    while (user < 1 || user > 3)
    {
        cout << "Please pick one of the options." << endl;
        cin >> user;
    }

    // Switch to manage function according to user's choice
    switch (user)
    {
        case 1:
        cout << "What string would you like to search?" << endl;
        cin >> word;

        // Goes through all the movies and tries to find any with the given word
        for (vector<Movie*>::iterator it = m_movieCatalog.begin(); it != m_movieCatalog.end(); it++)
        {
            // If it finds a match then displays it in a list format
            if (int(((*it)->GetTitle()).find(word)) != -1 || int(((*it)->GetDirector()).find(word)) != -1)
            {
                cout << listNum << ". " << *(*it) << endl;
                listNum++;
            }
        }
        break;

        case 2:
        cout << "What year (int) would you like to search?" << endl;
        cin >> year;

        // Goes through all the movies and tries to find any with the given year
        for (vector<Movie*>::iterator it = m_movieCatalog.begin(); it != m_movieCatalog.end(); it++)
        {
            // If it finds a match then displays it in a list format
            if (((*it)->GetYear()) == year)
            {
                cout << listNum << ". " << *(*it) << endl;
                listNum++;
            }
        }
        break;

        case 3:
        cout << "What minimum profit (long) do you want to search?" << endl;
        cin >> minProfit;

        // Goes through all the movies and tries to find any with profit greater than given minProfit
        for (vector<Movie*>::iterator it = m_movieCatalog.begin(); it != m_movieCatalog.end(); it++)
        {
            // Calculates each movie's earnings
            earnings = (*it)->GetGross() - (*it)->GetBudget();

            // If it finds a match then displays it in a list format
            if (earnings > minProfit)
            {
                cout << listNum << ". " << *(*it) << endl;
                listNum++;
            }
        }
        break;
    }
}
