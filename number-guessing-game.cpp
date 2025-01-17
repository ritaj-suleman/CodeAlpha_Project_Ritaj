// Number Guessing Game 
#include <iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;
int main()
{
srand(time(0));
int num= rand() % 100 + 1;//range 1-100
int attempts=10, lower_bound=1, upper_bound=100;
bool locked_range=false,helpful_hint_given=false;
const int time_limit = 5;
const string whiteBG = "\033[47m";
const string magentaFG = "\033[35m";
const string cyanFG = "\033[36m";
const string resetFG = "\033[39m";

cout <<whiteBG<<magentaFG<< "Welcome to the Number Guessing Game!" << endl;
cout << "Guess the number between 1 and 100." << endl;
cout << "Note: You have " << time_limit << " seconds to make each guess!" << endl;

while (attempts>0)
{
cout <<endl<<magentaFG<<"You have " <<cyanFG<< attempts << " attempts remaining."<<magentaFG << "\n";

if(!locked_range)
{
cout <<"Guess a number between " << lower_bound << " and " << upper_bound << ": ";
}
else
{
cout << "Guess a number (the range is now hidden): ";
}

time_t start_time = time(0);

int guess;
cin>>guess;

time_t end_time = time(0);

double time_taken = difftime(end_time, start_time);

if (time_taken > time_limit) 
{
cout << "You took too long! You lost an attempt:(" << endl;
attempts--;  
continue;    
}

if (!locked_range && (guess < lower_bound || guess > upper_bound)) 
{
cout << "Please enter a number within the range!" << "\n";
continue;
}

if (guess == num) 
{
cout << "Congratulations! You guessed the correct number: " << num << " in "<<cyanFG<<(10-attempts)<<" attempts." <<magentaFG<< "\n";
break;
}
else
{
attempts--;
}

if (!locked_range) 
{
if (guess > num) 
{
upper_bound = guess - 1;
cout << "Too high." << "\n";
} 
else 
{
lower_bound = guess + 1;
cout << "Too low." << "\n";
}
}

// Clue logic based on random clue type
int clue_type;
if (attempts<=7) 
{
clue_type = rand() % 3; // 0: helpful, 1: vague, 2: misleading
}


if (clue_type == 0 && !helpful_hint_given) 
{ // helpful hint
cout << "Helpful hint: The number is " << (num % 2 == 0 ? "even." : "odd.") << "\n";
helpful_hint_given=true;
} 
else if (clue_type == 1) 
{ // Vague clue
int difference = guess - num;
if (difference < 0) difference = -difference;  // Absolute value
if (difference <= 10) 
{
cout << "You're close!" << "\n";
} 
else if (difference > 20) 
{
cout << "Not even close." << "\n";
}
} 
else if (clue_type == 2) 
{
// Provide misleading hints only if clue_type is 2
int misleading_hint_type = rand() % 3; 
if (misleading_hint_type == 0) 
{
cout << "The number maybe is not a multiple of 5!" << "\n";
} 
else if (misleading_hint_type == 1) 
{
cout << "You might want to guess a number close to 50!" << "\n";
} 
else 
{
cout << "The number might not be in the first half of the range!" << "\n";
}
}

if (attempts == 3 && !locked_range) 
{
int new_lower_bound = num - 10;
int new_upper_bound = num + 10;

// the locked range is within the original bounds
if (new_lower_bound < lower_bound) 
{
new_lower_bound = lower_bound;
}
if (new_upper_bound > upper_bound) 
{
new_upper_bound = upper_bound;
}

lower_bound = new_lower_bound;
upper_bound = new_upper_bound;

locked_range = true;  
cout << "The range is now hidden, but has been restricted!" << "\n";
}
}

if (attempts==0)
{
cout << "Game over! The correct number was " << num << ". Better luck next time:)" << "\n";
}

}
