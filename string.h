/**
* @author Nia Jacobs, 2002559351, Assignment 5
* @brief headerfile for string class, includes description of each member.
* @note I pledge my word of honor that I have complied with UNLV's
* Academic Integrity Policy while completing this assignment.
* @note prototypes of memebers and attributes of String Class to be defined in String.cpp.e
*/
#ifndef MY_STRING_H
#define MY_STRING_H
class String {
private:
static const int SMALL_SIZE = 16;
char small[SMALL_SIZE] = {}; // always present, used when length < 15
char* large; // NULL if using small buffer, otherwise heap
int len; // actual number of characters (not counting null)
bool using_small() const {
return large == nullptr;
}
// Internal helper: copy characters from src to dst (up to n chars)
void copy_chars(char* dst, const char* src, int n) {
for (int i = 0; i < n; ++i) {
dst[i] = src[i];
}
}
// Internal helper: set terminator
void set_null_terminator() {
if (using_small()) {
small[len] = '\0';
} else {
large[len] = '\0';
}
}
// Internal helper: set terminator
bool is_whitespace(char c) {
return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}
// Internal helper: grow to at least new_capacity characters (excluding null)
void grow_if_needed(int new_capacity_needed);
public:
//
String(); // empty string
String(const char* cstr); // from null-terminated C string
String(const String& other); // copy
~String();
//
void set(const char* cstr); //sets to *this to c style string growing if needed
void set(const String& other); // sets this* to other String
//
int size() const { return len; } //returnes length
int length() const { return len; } //same thing as size
//int capacity() const; 
bool is_empty() const { return len == 0; } //returns true if len == 0;
const char* c_str() const; //returns pointer to used buffer 
char get_at(int index) const; // returns char at index, or a \0 if out of bounds
//
void clear(); // len ==0 and null terminator (no dellocation)
void append_char(char ch); //adds a char at end of string
void append_cstr(const char* cstr); //adds a c style string at end of string 
void append(const String& other); // adds string stored in other
// void prepend_char(char ch);
// void prepend_cstr(const char* cstr);
// void prepend(const String& other);
void erase(int pos, int count = 1); // erases chars from position and count number of chars
//
void make_upper(); // makes everything uppercase
void make_lower();//turn everything into lowercase
//
void trim_left(); //trims leading whitespace
void trim_right(); //trims whitespace after string
void trim(); // calls and trims whtiespace left & right 
//
void insert(int pos, const String& other); // shifts string right wtih pointer and inserts string there
void insert_cstr(int pos, const char* cstr); // same thing except with c string
void insert_char(int pos, char ch); // only inputs a char and shifts 
//
void reverse(); // makes string go the other way around 
//
int compare(const String& other) const; // compares the char values of each string and returns -1 if less than, 0 if equal, and 1 if greater than
bool equals(const String& other) const; // returns true if len and compare() are both true
bool equals_ignore_case(const String& other) const;  // compares but makes sure everything in owercase beforehand
int find(const String& pattern) const; //finds string of other in *this buffer
int find_cstr(const char* pattern) const; //finds c style string in *this buffer
int find_char(char ch) const; //finds char in the string
//
void print() const; //prints out string 
};
#endif // MY_STRING_H
