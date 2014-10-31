//This program was written by Franciszek Jemioło and Michał Sołtysiak.
//Identified by index numbers fj346919 and ms347246 respectively.

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
using namespace std;
using namespace boost;
using namespace boost::algorithm;
#define ST const string
#define ll long long
#define plls pair <ll, string>
#define pllll pair <ll, ll>
#define vp vector <plls>
#define out(s) cout<<s.second<<" "<<s.first<<endl
#define err(s, n) cerr<<"Error in line "<<n<<":"<<s<<endl
#define MAX_SIZE 1000000000000
#define MAX_LENGTH 13

//The pattern for the coin.
ST coinPat = "((\\S)+)";
//The pattern for the description which can be anything.
ST desPat = "(.*)";
//The pattern for blank space.
ST blPat = "(\\s+)";
//The pattern for the year.
ST yrPat = "(-?[1-9](\\d)*)";
//The pattern for ending which is blank space and end of line sign. 
ST endPat = "((\\s)*$)";
//The pattern for number.
ST numPat = "(-?[0-9]+)";
//The pattern for the whole line describing coin.
ST linePat = coinPat + desPat + blPat + yrPat + endPat;
//The pattern for the numbers line.
ST numsPat = numPat + blPat + numPat + endPat;
//The pattern for years.
ST yrsPat = yrPat + blPat + yrPat + endPat;

bool isBtwn (ll x)
//Checking if the number is in [-MAX_SIZE, MAX_SIZE]
{
  return ((x <= MAX_SIZE)&&(x >= -MAX_SIZE));
};

bool ifNum (ST s)
//A string can be a number only if its length is not too long.
{
  return (s.length() < 13);
};

ll retNum (ST s)
//This function returns a long long number or 0 if its not a valid number.
{
    if (ifNum (s)) {
      if (isBtwn (stoll(s))) {
        return stoll(s);
      };
    };
    return 0;
}

void prnt (plls s) {
//Small function printing a pair of long long and string.
  out (s);
};

bool checkFor (ST line, ST pat)
//We are checking if the following pattern occurs in the line.
{
  smatch res;
  regex patLine (pat);
  //Searching for first and only match in given line.
  return (regex_match (line, res, patLine));
};

bool isLine (ST line)
//We are checking if line is describing the coin.
{
  return checkFor (line, linePat);
};

bool isNums (ST line)
//We are checking if line consists of two numbers.
{
  return checkFor (line, numsPat); 
};

plls parseLine (ST line)
{
  smatch res;
  regex patLine (linePat);
  ll year = 0;
  string wrks = "";
  //Searching for first and only match in given line.
  if (regex_match (line, res, patLine)) {
    //Because the fifth group in regex is concerning year.
    year = retNum (res[5]);
    //Because the first and third group is concerning description and coin name.
    wrks = (res[1] + res[3]);
    trim_right (wrks);
  }
  return plls (year, wrks);
};

pllll parseNums (ST line)
{
  smatch res;
  regex patLine (yrsPat);
  string wrks;
  ll r1 = 0, r2 = 0;
  //Searching for first and only match in given line.
  if (regex_match (line, res, patLine)) {
    //Because the first group in regex is concerning first year.
    r1 = retNum (res[1]);
    //Because the fourth group is concerning the second year.
    r2 = retNum (res[4]);
  }
  return pllll (r1, r2);
};

//In this to vectors we store paired coin description with year.
vp pairCoins;
//These are the numbers of year by which we will be sorting r1 < r2.
ll r1 = -MAX_SIZE, r2 = -MAX_SIZE;

bool input ()
//The method that controls the input for the program.
{
  string line;
  ll num = 1;
  bool read = true;
  //String on which we will be working in reading a line.
  pllll wrkp;
  while (!cin.eof())
  {
    //Getting next line.
    getline (cin, line);
    if (!((cin.eof()) && (line == "")))
    {
      if ((isNums (line))&&(read)) {
      //Checking if the line has 2 numbers, which indicates end.
        wrkp = parseNums (line);
        r1 = wrkp.first;
        r2 = wrkp.second;
        if ((r1 == 0)||(r2 == 0)||(!isBtwn(r1))||(!isBtwn(r2))) {
          err (line, num);
        }
        else if (r1 >= r2) {
          err (line, num);
          read = false;
        }
        else {
          read = false;
        }
      }
      else if ((isLine(line))&&(read)) {
      //Checking if the line is describing a coin.
        plls coin = parseLine(line);
        if (coin.first != 0){
          pairCoins.push_back (coin);
        }
        else {
          err (line, num);
        }
      }
      else {
      //We are printing errors.
        err (line, num);
      }
      num++;
    }
  }
  if (read) {
    line = "";
    err (line, num);
  };
  return (!read);
};

void output ()
//Here we are printing our sorted coins.
{
  //Sorting
  sort (pairCoins.begin(), pairCoins.end());
  //Iterators for our years.
  vp::iterator low, up;
  low = lower_bound(pairCoins.begin(), pairCoins.end(), plls(r1, ""));
  up = lower_bound(pairCoins.begin(), pairCoins.end(), plls(r2, ""));
  //Printing everything that has lower year than r1.
  for_each(pairCoins.begin(), low, prnt);
  if (r1 < r2){
    //Now reversing the iterators.
    vp::reverse_iterator lowr(up), upr(low);
    //Decreasingly print years from r1 to r2.
    for_each(lowr, upr, prnt);
  }
  //Everything from year r2 to the end.
  for_each(up, pairCoins.end(), prnt);
};

int main ()
{
  if (input ()) {
    output ();
  }
};
