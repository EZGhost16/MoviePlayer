/**********************************************
 * File: Proj5.cpp
 * Project: CMSC 202 Project 5, Spring 2024
 * Author: Eden Zhang
 * Date: 4/20/2024
 * Section: 30/34
 * E-Mail: ezhang1@umbc.edu
 * 
 * Movie.cpp
 * Class file for Movie objects and 
 * the data used in MoviePlayer
 * 
*****************************************************/
#include "Movie.h"

// Movie
// Default constructor
Movie::Movie()
{
}

// Movie
// Movie main constructor, assigns each element with the passed arguments
Movie::Movie(string title, string rating, string genre, int year, string director,
	string star, long budget, long gross, string studio, int runtime)
{
    m_title = title;
    m_rating = rating;
    m_genre = genre;
    m_year = year;
    m_director = director;
    m_star = star;
    m_budget = budget;
    m_gross = gross;
    m_studio = studio;
    m_runtime = runtime;
}

//**** Getter functions *****/////
string Movie::GetTitle()const
{
    return m_title;
}

string Movie::GetRating()const
{
    return m_rating;
}

string Movie::GetGenre()const
{
    return m_genre;
}

int Movie::GetYear()const
{
    return m_year;
}

string Movie::GetDirector()const
{
    return m_director;
}

string Movie::GetStar() const
{
    return m_star;
}

long Movie::GetBudget() const
{
    return m_budget;
}

long Movie::GetGross() const
{
    return m_gross;
}

string Movie::GetStudio() const
{
    return m_studio;
}

int Movie::GetRuntime() const
{
    return m_runtime;
}

//**** Setter functions ****//////
void Movie::SetTitle(string title)
{
    m_title = title;
}

void Movie::SetRating(string rating)
{
    m_rating = rating;
}

void Movie::SetGenre(string genre)
{
    m_genre = genre;
}

void Movie::SetYear(int year)
{
    m_year = year;
}

void Movie::SetDirector(string director)
{
    m_director = director;
}

void Movie::SetStar(string star)
{
    m_star = star;
}

void Movie::SetBudget(long budget)
{
    m_budget = budget;
}

void Movie::SetGross(long gross)
{
    m_gross = gross;
}

void Movie::SetStudio(string studio)
{
    m_studio = studio;
}

void Movie::SetRuntime(int runtime)
{
    m_runtime = runtime;
}

// Overloaded <<
// Prints out Movie info
ostream& operator<<(ostream& out, Movie& m)
{
    // Displays movie in the following format
    out << m.GetTitle() << " by " << m.GetDirector() << 
    " from " << m.GetYear();

    return out;
}

// Overloaded <
// Compares the year of two movies
bool Movie::operator<(const Movie& m)
{
    if (m_year < m.GetYear())
    {
        return true;
    } else 
    {
        return false;
    }
}

// Overloaded >
// Compares the year of two movies
bool Movie::operator>(const Movie& m)
{
    if (m_year > m.GetYear())
    {
        return true;
    } else 
    {
        return false;
    }
}
