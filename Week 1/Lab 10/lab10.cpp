/// @file pa06b.cpp
/// @author Thien Nguyen thiennguyen@.csn.edu
/// @date 11/9/21
/// @note I pledge my word of honor that
///       I have abided by the the CSN Academic Integrity Policy
///       while completing this assignment.
///
/// @brief This assignment reads and filters a delimited data stream 
///        to identify and report those transactions occurring on a given 
///        weekday. The largest quantity and sale are noted and reported at
///        the end of the report, along with a count of items sold 
///        and the total sales for the period.
/// @note People who helped:
/// @note This is but one possible solution to the assignment.
///       Programming techniques and commands in this solution
///       are aligned with the current and previous chapters,
///       labs, and lectures, which may result in a trade-off
///       between efficient coding and what student are
///       currently able to understand.


// include libs
#include <cmath>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <string>
#include <random>
#include <cstdlib>
#include <limits>

// setting a namcespace scope
using namespace std;


/// -----------------------------------------------------------------------
/// Function Prototypes
/// -----------------------------------------------------------------------

class clockType {

public: 

    clockType();       // default constructor
    clockType(int hour, int minute, int second);

    void setTime(int hour, int minute, int second);
    void getTime(int& hour, int & minute, int& second) const;

    void printTime() const {
        cout << hr << ":" << minute << ":" << second << endl;
    }

    void incrementSeconds();
    void incrementMinutes();
    void incrementHours();
    bool equalTime(const clockType& other) const;

private: 
    int hr;
    int minute;
    int second;
};



/// -----------------------------------------------------------------------
/// Main entry-point for this application
///
/// @returns Exit-code for the process - 0 for success, else an error code.
/// -----------------------------------------------------------------------
int main() {

    clockType myclock;      // calls default constructor
    clockType Yourclock;

    // clockType times[3600] = {{ 0, 0, 0 }}; 

    // myclock.printTime();

// return to the operating system
return EXIT_SUCCESS;
}

/// -----------------------------------------------------------------------
/// Function Implementations
/// -----------------------------------------------------------------------

clockType::clockType() {
    int hr = 0;
    int minute = 0;
    int second = 0;
}

clockType::clockType(int hour, int minute, int second) {

}

// void setTime(int hour, int minute, int second) {


// }
// void clockType::getTime(int& hour, int & minute, int& second) {


// }

// void clockType::clockType::printTime() {

// cout << hr << ":" << minute << ":" << second << endl;


// }
// void clockType::incrementSeconds() {


// }
// void clockType::incrementMinutes() {


// }
// void clockType::incrementHours() {


// }
// bool clockType::equalTime(const clockType& other) {

//     return false;
// }

// 


class Bag {

public:

    Bag();

    using value_type = int;     // equivalent to 'typedef int value_type'
    using size_type  = size_t;   // typedef size_t -> size_type

    static const size_type CAPACITY = 20;

    size_type size() const;

    bool empty() const;

    void insert(const value_type& value);

    bool erase_one(const value_type& target);

    void clear();

    size_type count(const value_type& target) const;

    void write(std::ostream& output = std::cout) const;

private:
    value_type data[CAPACITY];
    size_type  used;

};
