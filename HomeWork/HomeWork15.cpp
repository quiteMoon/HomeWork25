#include <iostream>
#include <stdexcept>
#include <ctime>

using namespace std;

class DateTime {
private:
    int year, month, day, hours, minutes, seconds;

    bool isLeapYear(int year) const {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    int daysInMonth(int month, int year) const {
        if (month < 1 || month > 12) throw invalid_argument("Invalid month");
        static const int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        if (month == 2 && isLeapYear(year)) return 29;
        return daysInMonth[month - 1];
    }

    void validateDate() const {
        if (month < 1 || month > 12) throw invalid_argument("Invalid month");
        if (day < 1 || day > daysInMonth(month, year)) throw invalid_argument("Invalid day");
        if (hours < 0 || hours >= 24) throw invalid_argument("Invalid hours");
        if (minutes < 0 || minutes >= 60) throw invalid_argument("Invalid minutes");
        if (seconds < 0 || seconds >= 60) throw invalid_argument("Invalid seconds");
    }

    void addDays(int days) {
        struct tm timeinfo = { 0 };
        timeinfo.tm_year = year - 1900;
        timeinfo.tm_mon = month - 1;
        timeinfo.tm_mday = day + days;
        timeinfo.tm_hour = hours;
        timeinfo.tm_min = minutes;
        timeinfo.tm_sec = seconds;
        mktime(&timeinfo);
        year = timeinfo.tm_year + 1900;
        month = timeinfo.tm_mon + 1;
        day = timeinfo.tm_mday;
        hours = timeinfo.tm_hour;
        minutes = timeinfo.tm_min;
        seconds = timeinfo.tm_sec;
    }

public:
    DateTime(int y, int m, int d, int h = 0, int min = 0, int s = 0)
        : year(y), month(m), day(d), hours(h), minutes(min), seconds(s) {
        validateDate();
    }

    int getYear() const { return year; }
    int getMonth() const { return month; }
    int getDay() const { return day; }
    int getHours() const { return hours; }
    int getMinutes() const { return minutes; }
    int getSeconds() const { return seconds; }

    void setYear(int y) { year = y; validateDate(); }
    void setMonth(int m) { month = m; validateDate(); }
    void setDay(int d) { day = d; validateDate(); }
    void setHours(int h) { hours = h; validateDate(); }
    void setMinutes(int min) { minutes = min; validateDate(); }
    void setSeconds(int s) { seconds = s; validateDate(); }

    friend DateTime operator+(const DateTime& dt1, const DateTime& dt2) {
        struct tm timeinfo = { 0 };
        timeinfo.tm_year = dt1.year - 1900 + dt2.year - 1900;
        timeinfo.tm_mon = dt1.month - 1 + dt2.month - 1;
        timeinfo.tm_mday = dt1.day + dt2.day;
        timeinfo.tm_hour = dt1.hours + dt2.hours;
        timeinfo.tm_min = dt1.minutes + dt2.minutes;
        timeinfo.tm_sec = dt1.seconds + dt2.seconds;
        mktime(&timeinfo);
        return DateTime(timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday,
            timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
    }

    friend DateTime operator-(const DateTime& dt1, const DateTime& dt2) {
        struct tm timeinfo = { 0 };
        timeinfo.tm_year = dt1.year - 1900 - (dt2.year - 1900);
        timeinfo.tm_mon = dt1.month - 1 - (dt2.month - 1);
        timeinfo.tm_mday = dt1.day - dt2.day;
        timeinfo.tm_hour = dt1.hours - dt2.hours;
        timeinfo.tm_min = dt1.minutes - dt2.minutes;
        timeinfo.tm_sec = dt1.seconds - dt2.seconds;
        mktime(&timeinfo);
        return DateTime(timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday,
            timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
    }

    DateTime& operator+=(int days) {
        addDays(days);
        return *this;
    }

    DateTime& operator-=(int days) {
        addDays(-days);
        return *this;
    }

    bool operator<(const DateTime& dt) const {
        if (year != dt.year) return year < dt.year;
        if (month != dt.month) return month < dt.month;
        if (day != dt.day) return day < dt.day;
        if (hours != dt.hours) return hours < dt.hours;
        if (minutes != dt.minutes) return minutes < dt.minutes;
        return seconds < dt.seconds;
    }

    bool operator>(const DateTime& dt) const { return dt < *this; }
    bool operator<=(const DateTime& dt) const { return !(dt < *this); }
    bool operator>=(const DateTime& dt) const { return !(*this < dt); }
    bool operator==(const DateTime& dt) const {
        return year == dt.year && month == dt.month && day == dt.day &&
            hours == dt.hours && minutes == dt.minutes && seconds == dt.seconds;
    }

    bool operator!=(const DateTime& dt) const { return !(*this == dt); }

    int operator[](const string& key) const {
        if (key == "year") return year;
        if (key == "month") return month;
        if (key == "day") return day;
        if (key == "hours") return hours;
        if (key == "minutes") return minutes;
        if (key == "seconds") return seconds;
        throw invalid_argument("Invalid key");
    }

    friend ostream& operator<<(ostream& os, const DateTime& dt) {
        os << dt.year << "-"
            << (dt.month < 10 ? "0" : "") << dt.month << "-"
            << (dt.day < 10 ? "0" : "") << dt.day << " "
            << (dt.hours < 10 ? "0" : "") << dt.hours << ":"
            << (dt.minutes < 10 ? "0" : "") << dt.minutes << ":"
            << (dt.seconds < 10 ? "0" : "") << dt.seconds;
        return os;
    }

    friend istream& operator>>(istream& is, DateTime& dt) {
        char delimiter;
        is >> dt.year >> delimiter >> dt.month >> delimiter >> dt.day
            >> dt.hours >> delimiter >> dt.minutes >> delimiter >> dt.seconds;
        dt.validateDate();
        return is;
    }
};

int main() {
    try {
        DateTime dt1(2023, 7, 13, 12, 30, 45);
        DateTime dt2(2024, 2, 29, 11, 20, 35);

        cout << "DateTime 1: " << dt1 << endl;
        cout << "DateTime 2: " << dt2 << endl;

        DateTime dt3 = dt1 + dt2;
        cout << "DateTime 3 (dt1 + dt2): " << dt3 << endl;

        dt1 += 5;
        cout << "DateTime 1 after adding 5 days: " << dt1 << endl;

        dt2 -= 10;
        cout << "DateTime 2 after subtracting 10 days: " << dt2 << endl;

        cout << "Year of DateTime 1: " << dt1["year"] << endl;
        cout << "Month of DateTime 1: " << dt1["month"] << endl;

        cout << "Enter a new date and time (YYYY-MM-DD HH:MM:SS): ";
        DateTime dt4(2020, 1, 1);
        cin >> dt4;
        cout << "You entered: " << dt4 << endl;

    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}
