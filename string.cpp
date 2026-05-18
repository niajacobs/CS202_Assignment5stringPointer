/**
* @author Nia Jacobs, 2002559351, Assignment 5
* @brief implementation file for string.h, a data type that can represent large and small strings.
In order to do these member functions, there is an emphasis on pointer arithmetic. Larger strings larger
than a len of 15, will be stored into a dynamic array on the heap. More important functions
include: growing the array if needed, appending, inserting and finding in the string. 
* @note I pledge my word of honor that I have complied with UNLV's
* Academic Integrity Policy while completing this assignment.
* @note defining memebers and attributes of String Class. !! 
* @note I will describe the member and attributes within the headerfile.
*/
#include "String.h"
#include <iostream>
using namespace std;
/*
char small[SMALL_SIZE]: Fixed-size array for small strings (e.g., SMALL_SIZE = 16, in-
cluding space for null-terminator). It is used when the string length is less than 15 to avoid
dynamic allocation, improving efficiency for short strings.
– char* large: Pointer to a dynamically allocated array of char. It is nullptr when using
the small buffer; otherwise, it points to heap-allocated memory for longer strings. This allows
the class to handle arbitrary lengths using pointer arithmetic for access and manipulation.
– int len: Number of characters in the string (not including null-terminator). It tracks the
actual content size, used in all operations to determine loops, growth, and positions.
*/

String::String() // constructor
{
    *small = '\0';
    large = nullptr; 
    len = 0;
}

String::String(const char* cstr)
{
    large = nullptr;
    int i = 0;

   // cout << "hii" << endl; if the cout random im just checking where its running
    while ( *(cstr + i) != '\0')
    {
        //cout << *(cstr + i)  << endl;
        i++;
    }

    len = i;

    if (i < 15) //len must be less than 15 to account for the '\0'
    {

        for (int j = 0; j < len; j++)
        {
            *(small + j) = *(cstr + j);
            //cout << *(cstr + j);
        }

        small[len] = '\0';
    }

    if (i >= 15)
    {
        //cout<< "ayy" << endl;
        large = new char[len]; //dynamic array on the heap
        for (int j = 0; j < len; j++)
        {

            *(large + j) = *(cstr + j);
        }

        *(large + len) = '\0';

    }
}

String::String(const String& other)
{
    large = nullptr;
    len = other.len;
    
    if (other.len < 15)
    {
        for (int j = 0; j < len; j++)
        {
            *(small + j) = other.small[j];
            
        }
    }

    if (other.len >= 15)
    {
        large = new char[len];
        for (int j = 0; j < len; j++)
        {

            *(large + j) = *(other.large + j);
        }
    }

}

String::~String()
{
    if (large != nullptr)
    {
        delete[] large; //destructor, recycles the memory !! if u dont free then memory leak.. 
    }
}

void String::grow_if_needed(int new_capacity_needed) // !! important to see which buffer to use for future members
{
    if (large == nullptr) // use small array
    {
        if (len + new_capacity_needed > 15)
        {
            
            
            large = new char[16*2]; //doubling up array

             for (int i = 0; i < 16; i++)
            {
               *(large + i) = small[i]; // copying over data 
            }

            for(int i = 0; i < 15; i++)
            {
                *(small + i) = '\0';  //getting rid of data from past array, lowkey OD but made all \0
            } 
        }

    }
    else //if buffer is already a large array
    {
        int cnt = 0;
        for (int i = 0; i < len * 2; i++)
        {
            if( *(large + i) != '\0') // counts arraysize since it might vary 
            {
                cnt++;
            }
            else
            {
                break;
            }
        }
        if(len + new_capacity_needed > cnt)
        {
            
            char* copy = new char[cnt*2];
            for (int i = 0; i < cnt; i++)
            {
                *(copy + i) = *(large + i);
            }
            
            delete[] large; //deallocating the past large one i can make a BIG AND BETTER ONE
            large = new char[cnt*2]; //big and better one 
            for (int i = 0; i < cnt*2; i++)
            {
                *(large + i) = *(copy + i);
            }
            delete[] copy; //#no memory leak #free 
        }
    }
}

void String::set(const char* cstr)
{
    if (large == nullptr) // small array
    {
       
        for (int i = 0; i < 15; i++)
        {
            *(small + i) = ' '; //clearing it out 
        }
        *(small) = '\0';
    }
    

    int cnt = 0;
        while (*(cstr+cnt) != '\0')
        {
            cnt++;
        }

    if (cnt < 15)
    {
        for (int i = 0; i < cnt; i++)
        {
            *(small + i) = *(cstr + i);
        }
        len = cnt;
        *(small + cnt) = '\0';
    }
    else
    {
        delete[] large;
        large = new char[cnt];
        for (int i = 0; i < cnt; i++)
        {
            *(large + i) = *(cstr + i);
        }
        len = cnt;
        large[cnt] = '\0';
    }
}

void String::set(const String& other)
{
    if (large == nullptr)
    {
       
        for (int i = 0; i < 15; i++)
        {
            *(small + i) = ' ';
        }
        small[0] = '\0';
    }
    else
    {
        delete[] large;
    }

     int cnt = 0;
       

    if (other.len < 15)
    {
        while (other.small[cnt]!= '\0')
        {
            cnt++;
        }

        for (int i = 0; i < 15; i++)
        {
            *(small + i) = *(other.small + i);
        }
        len = cnt;
        small[cnt] = '\0';
    }
    else
    {
       
        while (*(other.large + cnt) != '\0')
        {
            cnt++;
        }

        large = new char[cnt];
        for (int i = 0; i < cnt; i++)
        {
            *(large + i) = *(other.large + i);
        }
        len = cnt;
        *(large + cnt) = '\0';
    }
}

/*
int String::size() const
{
    return len;
}
*/

/*

bool String::is_empty() const
{
    bool empty = false;

    if (len == 0)
    {
        empty = true;
    }

    return empty;
}
*/

const char* String::c_str() const
{
    if (large != nullptr)
    {
        return large;
    }

    return small;
}

char String::get_at(int index) const
{
    if (index >= len)
    {
        return '\0'; //out of bounds
    }
    
    if (large != nullptr) //large array 
    {
        return *(large + index);
    }

    return small[index];
}

void String::clear()
{
    len = 0;

    if (large != nullptr)
    {
        *large = '\0';
    }
    else
    {
        *small = '\0';
    }
}

void String::append_char(char ch) //adding to end
{
    grow_if_needed(1); // only 1
    if (large != nullptr)
    {
        *(large + len) = ch;
        *(large + len + 1) = '\0';
    }
    else
    {
        *(small + len) = ch;
        *(small + len + 1) = '\0';
    }
    len++;
}

void String::append_cstr(const char* cstr)
{
    int cnt = 0;
    while (*(cstr + cnt) != '\0')
    {
        cnt++;
    }
    
    grow_if_needed(cnt);

    //cout << len << endl;
    //cout << cnt << endl;
    
    if (large == nullptr)
    {
        
        for (int i = 0; i < cnt; i++)
        {
            *(small + i + len)  = cstr[i];
            //cout << small[i + len] << endl;
        }
        len += cnt;
        *(small + len) = '\0';

    }
    else
    {
        for (int i = 0; i < cnt; i++)
        {
            *(large + i + len)  = cstr[i];
        }
        len += cnt;
        *(large + len) = '\0';
    }

}

void String::append(const String& other)
{
    grow_if_needed(other.len);

    //cout << len << endl;
    //cout << cnt << endl;
    //cout << "HELLOOOOOOOOOOO" << endl;
    if (large == nullptr) // if og small
    {
        if (other.large == nullptr)
        {
            for (int i = 0; i < other.len; i++)
            {
                *(small + i + len)  = *(other.small + i);
                //cout << other.small[i] << endl;
            }
        
        }
        else
        {
            for (int i = 0; i < other.len; i++)
            {
                *(small + i + len)  = *(other.large + i);
                //cout << other.small[i] << endl;
            }
        }
        len+= other.len;
        *(small + len) = '\0';
    }
    else // if og large
    {
        if (other.large == nullptr) // other is small 
        {
            for (int i = 0; i < other.len; i++)
            {
                *(large + i + len)  = *(other.small + i);
            }
        }
        else // other is large
        {
            for (int i = 0; i < other.len; i++)
            {
                *(large + i + len)  = *(other.large + i);
            }   
        }
        len+= other.len;
        *(large + len) = '\0';
    }

}

void String::insert_char(int pos, char ch)
{
    //cout << (large = nullptr) << endl;

    if (pos >= len)
    {
        append_char(ch);
        return;
    }
    grow_if_needed(1);
    if (large == nullptr) // is small
    {
        for (int i = 0; i < len - pos; i++)
        {
            *(small + len - i) = *(small + len - 1 - i);

        }
        len++;
        *(small + len) = '\0';
        *(small + pos) = ch;
    }
    else
    {
        for (int i = 0; i < len - pos; i++)
        {
            *(large + len - i) = *(large+ len-1 - i);

        }
        len++;
        *(large + len) = '\0';
        *(large + pos) = ch;
    }
}

void String::insert_cstr(int pos, const char* cstr)
{
        //cout << (large = nullptr) << endl;

    if (pos >= len)
    {
        append_cstr(cstr);
        return;
    }
    int cnt = 0;
    while (cstr[cnt] != '\0')
    {
        cnt++;
    }
    grow_if_needed(cnt);
    if (large == nullptr) // is small
    {
        //cout << "hoy" << endl;
        for (int i = 0; i < len - pos + 1; i++)
        {
            //cout << small[len - i]<< endl;
            //cout << (cnt + pos + (len-pos) - i) << endl;
            *(small + cnt + pos + (len-pos) - i) = *(small + len - i);
            
        }


        /*
for (int i = 0; i < 15; i++)
   {
    cout << small[i];
    cout << i << endl;
    //cout << (b.small[i] >= 'a' && b.small[i] <= 'z' || b.small[i] == ' ' || (b.small[i] >= 'A' && b.small[i] <= 'Z') ) << endl;
   }
   cout << endl;
   */
        
        for(int i = 0; i < cnt; i++)                                                                                                                                                    
        {
            *(small + pos + i) = *(cstr + i);
    
        }

        len += cnt;
        *(small+ len) = '\0';
    }
    else
    {
        //cout << "hey" << endl;
        for (int i = 0; i < len - pos + 1; i++)
        {
           //cout << large[len - i]<< endl;
            //cout << (cnt + pos + (len-pos) - i) << endl;
            *(large + cnt + pos + (len-pos) - i) = *(large + len - i);

        }

        for(int i = 0; i < cnt; i++)                                                                                                                                                    
        {
            *(large + pos + i) = *(cstr + i);
    
        }
        
        len += cnt;
        *(large + len) = '\0';
        //large[pos] = ch;
    }
}


void String::insert(int pos, const String& other)
{
            //cout << (large = nullptr) << endl;

    if (pos >= len)
    {
        //cout << "heyoo" << endl;
        append(other);
        return;
    }

    grow_if_needed(other.len);

  
    if (large == nullptr) // is small
    {
        //cout << "hoy" << endl;
        for (int i = 0; i < len - pos; i++)
        {
            //cout << small[len - i - 1];
            //cout << " " << (other.len + pos + (len-pos) - i - 1) << endl;
            *(small + other.len + pos + (len-pos) - i - 1) = *(small + len - i - 1);
            
        }
        
        for(int i = 0; i < other.len; i++)                                                                                                                                                    
        {
            *(small + pos + i) = *(other.small + i);
    
        }

        len += other.len;
        *(small + len) = '\0';
    }
    else
    {
        //cout << "hey" << endl;
        for (int i = 0; i < len - pos; i++)
        {
           //cout << large[len - i - 1]<< endl;
        //cout << (other.len + pos + (len-pos) - i - 1) << endl;
            *(large + other.len + pos + (len-pos) - i - 1) = *(large + len - i - 1);

        }

        if(other.large == nullptr)
        {
            for(int i = 0; i < other.len; i++)                                                                                                                                                    
            {
                *(large + pos + i) = *(other.small + i);
                
            }
        }
        else
        {
            for(int i = 0; i < other.len; i++)                                                                                                                                                    
            {
                *(large + pos + i) = *(other.large + i);
    
            }
        }
        
        len += other.len;
        //cout << len << endl;
        *(large + len) = '\0';
        //cout << *(large + len) << endl;
    }
}

void String::erase(int pos, int count)
{
    //cout << pos << endl;
    //cout << count << endl;

    if (pos >= len || count >= len)
    {
        return;
    }

    //cout << "bro T.T" << endl;
    if (large == nullptr)
    {
        for (int i = pos; i <= len - count; i++)
        {
            //cout << "hey" << endl;
            *(small + i) = *(small +  i + count);
            //small[pos + count + i] = small[pos + i];
            //cout << pos + count + i << endl;
            //cout << pos + i << endl;
        }


    }
    else
    {
        //cout << "hey" << endl;
        for (int i = pos; i <= len - count; i++)
        {
        
            *(large + i) = *(large + i + count);
            //small[pos + count + i] = small[pos + i];
            //cout << pos + count + i << endl;
            //cout << pos + i << endl;
        }
    }

    len -= count;
}

void String::make_upper()
{
    if (large == nullptr)
    {
        for (int i = 0; i < len; i++)
        {
            if(*(small + i) >= 'a' && *(small + i) <= 'z' )
            {
                *(small + i) -= 32;
            }
        }
    }
    else
    {
        for (int i = 0; i < len; i++)
        {
            if(*(large + i) >= 'a' && *(large + i) <= 'z' )
            {
                *(large + i) -= 32;
            }
        }
    }
}

void String::make_lower()
{
    if (large == nullptr)
    {
        for (int i = 0; i < len; i++)
        {
            if(*(small + i) >= 'A' && *(small + i) <= 'Z' )
            {
                *(small + i) += 32;
            }
        }
    }
    else
    {
        for (int i = 0; i < len; i++)
        {
            if(*(large + i) >= 'A' && *(large + i) <= 'Z' )
            {
                *(large + i) += 32;
            }
        }
    }
}

void String::reverse()
{
    if(large == nullptr)
    {

    for (int j = 0; j < len - 1; j++)
    {
        for (int i = 0; i < len - j - 1; i++)
        {
           char saved =  *(small + i);
           //cout << *(small + i) << endl;
            *(small + i) = *(small + i + 1);
            *(small + i + 1) = saved;
            //cout << *(small + i) << " switched " << *(small + i + 1) << endl;
        }
    }
    
    }
    else
    {
   for (int j = 0; j < len - 1; j++)
    {
       
        for (int i = 0; i < len - j - 1; i++)
        {
           char saved =  *(large + i);
           //cout << *(large + i) << endl;
            *(large + i) = *(large + i + 1);
            *(large + i + 1) = saved;
            //cout << *(large + i) << " switched " << *(large + i + 1) << endl;
        }
       large[len] = '\0';
    }
    }
    //cout << "hello" << endl;
}

void String::trim_left()
{
    if (large == nullptr)
    {
        int white = 0;
        for (int i = 0; i < len; i++)
        {
            if(*(small + i) == ' ' || *(small + i) == '\n' || *(small + i) == '\t' )
            {
                white++;
                *(small + i) = '\0';

            }
            else
            {
                break;
            }
        }

        for(int i = 0; i < len; i++)
        {
            *(small + i) = *(small + white + i);
        }
        len -= white;
        *(small + len) = '\0';
    }
    else
    {
        int white = 0;
        for (int i = 0; i < len; i++)
        {
            if(*(large + i) == ' ' || *(large + i) == '\n' || *(large + i) == '\t')
            {
                white++;
                *(large + i) = '\0';
            }
            else
            {
                break;
            }
        }

        for(int i = 0; i < len; i++)
        {
            *(large + i) = *(large + white + i);
        }
        len -= white;
        *(large + len) = '\0';
    }
}

void String::trim_right()
{
    if (large == nullptr)
    {
        int white = 0;
        for (int i = 0; i < len; i++)
        {
            if(*(small + len - 1 - i) == ' ' || *(small + len - 1 - i) == '\n' || *(small + len - 1 - i) == '\t')
            {
                white++;
                *(small + len - 1 - i) = '\0';
            }
            else
            {
                break;
            }
        }

        len -= white;
        *(small + len) = '\0';
    }
    else
    {
        int white = 0;
        for (int i = 0; i < len; i++)
        {
            if(*(large + len - 1 - i) == ' ' || *(large + len - 1 - i) == '\n' || *(large + len - 1 - i) == '\t')
            {
                white++;
                *(large + len - 1 - i) = '\0';
            }
            else
            {
                break;
            }
        }
        len -= white;
        *(large + len) = '\0';
    } 
}

void String::trim()
{
    trim_right();
    trim_left();
}

int String::compare(const String& other) const
{
   int thingval;
   int val2;
    if(large == nullptr)
    {
        thingval = 0;
        for(int i = 0; i < len; i++)
        {
            thingval += *(small + i);
        }
    }
    else
    {
        thingval = 0;
        for(int i = 0; i < len; i++)
        {
            thingval += *(large + i);
        }  
    }
//-------------------------------------------
    if(other.large == nullptr)
    {
        val2 = 0;
        for(int i = 0; i < other.len; i++)
        {
            val2 += *(other.small + i);
        }
    }
    else
    {
        val2 = 0;
        for(int i = 0; i < other.len; i++)
        {
            val2 += *(other.large + i);
        }  
    }

    if(thingval < val2)
    {
        return -1;
    }
    else if(thingval > val2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

bool String::equals(const String& other) const
{
    if(compare(other) == 0 && len == other.len)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool String::equals_ignore_case(const String& other) const
{
    int thingval; //lexi value of object instance
    int val2; // val of other
    int compare = 0; //what the boolean based on, lowk couldve done without or been a bool, but heres a int version

    if(large == nullptr)
    {
        thingval = 0;
        for(int i = 0; i < len; i++)
        {
            if(*(small + i) >= 'A' && *(small + i) <= 'Z')
            {
                thingval+=32;
            }
            
            thingval += *(small + i);
        }
    }
    else
    {
        thingval = 0;
        for(int i = 0; i < len; i++)
        {
            if(*(large + i) >= 'A' && *(large + i) <= 'Z')
            {
                thingval+=32;
            }
            thingval += *(large + i);

        }  
    }
//-------------------------------------------
    if(other.large == nullptr)
    {
        val2 = 0;
        for(int i = 0; i < other.len; i++)
        {
            if(*(other.small + i) >= 'A' && *(other.small + i) <= 'Z')
            {
                val2+=32;
            }
            val2 += *(other.small + i);
        }
    }
    else
    {
        val2 = 0;
        for(int i = 0; i < other.len; i++)
        {
            if(*(other.large + i) >= 'A' && *(other.large + i) <= 'Z')
            {
                val2+=32;
            }
            val2 += *(other.large + i);
        }  
    }

    if(thingval < val2)
    {
        compare = -1;
    }
    else if(thingval > val2)
    {
        compare = 1;
    }
    else
    {
        compare = 0;
    }
//--------------------------------------------------
    if(compare == 0 && len == other.len)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int String::find(const String& pattern) const
{
    bool firstfind = false;
    int index = 0; //where it @
    bool afterfind = false;
    bool found = false;
    int corlen = 0; //for seeing how many chars consecutively match til == len
    if(large == nullptr)//----------------------------------------------------------------------- og small array
    {
        if(pattern.large == nullptr) //---------------------------------------------------------- other small array
        {
            for (int i = 0; i < len; i++)
            {
                //cout << (found == false) << endl;
                if (found == false && found == false)
                {
                for (int j = 0; j < pattern.len; j++)
                {
                    if(*(small + i) == *(pattern.small + j))
                    {
                        index = i;
                        firstfind = true;
                    }
                }
                if (firstfind == true)
                {
                    firstfind = false;
                    found = true;
                    corlen++;
                    //cout << "find1" << endl;
                    continue;
                }
                }   

                if(found == true)
                {

                        if(*(small + i) == *(pattern.small + corlen))
                        {
                            afterfind = true;
                        }
                    
                    if (afterfind == true)
                    {
                        afterfind = false;
                        corlen++;
                    }
                    else
                    {
                        afterfind = false;
                        corlen = 0;
                        found = false;
                    }

                    if(corlen == pattern.len)
                    {
                        found = true;
                        break;
                    }

                }
            }
        }//-----------------------------------------------------------------------------------------other is large
        else 
        {
            found = false;  //cant find smthing large in small
        }
    }
    else//------------------------------------------------------------------------------------------- og is large array
    {
        if(pattern.large == nullptr) //---------------------------------------------------------- other small array
        {
            for (int i = 0; i < len; i++)
            {
                //cout << (found == false) << endl;
                if (found == false && found == false)
                {
                for (int j = 0; j < pattern.len; j++)
                {
                    if(*(large + i) == *(pattern.small + j))
                    {
                        index = i;
                        firstfind = true;
                    }
                }
                if (firstfind == true)
                {
                    firstfind = false;
                    found = true;
                    corlen++;
                    //cout << "find1" << endl;
                    continue;
                }
                }   

                if(found == true)
                {
        
                        if(*(large + i) == *(pattern.small + corlen))
                        {
                            afterfind = true;
                        }
                    
                    if (afterfind == true)
                    {
                        afterfind = false;
                        corlen++;
                    }
                    else
                    {
                        afterfind = false;
                        corlen = 0;
                        found = false;
                    }

                    if(corlen == pattern.len)
                    {
                        found = true;
                        break;
                    }

                }
            }
        }
        else//--------------------------------------------------------------------------------------------- other also large
        {
            if (pattern.len > len)
            {
                found = false;
                return found;
            }

                for (int i = 0; i < len; i++)
                {
                //cout << (found == false) << endl;
                    if (found == false && found == false)
                    {
                    for (int j = 0; j < pattern.len; j++)
                    {
                        if(*(large + i) == *(pattern.large + j))
                        {
                            index = i;
                            firstfind = true;
                        }
                    }
                    if (firstfind == true)
                    {
                        firstfind = false;
                        found = true;
                        corlen++;
                    //cout << "find1" << endl;
                        continue;
                    }
                    }   

                    if(found == true)
                    {
                            if(*(large + i) == *(pattern.large + corlen))
                            {
                                afterfind = true;
                            }
                        
                        if (afterfind == true)
                        {
                            afterfind = false;
                            corlen++;
                        }
                        else
                        {
                            afterfind = false;
                            corlen = 0;
                            found = false;
                        }

                        if(corlen == pattern.len)
                        {
                            found = true;
                            break;
                        }

                    }
                }


            
        }//-------------
    }

    

    if (found == 0)
    {
       // cout << "hey!" << endl;
        return -1;
  
    }
    
    if(found == 1)
    {
        //cout << "Now" << endl;
        return index;

    }

    return -1;
}

int String::find_cstr(const char* pattern) const
{
    bool firstfind = false;
    bool afterfind = false;
    bool found = false;
    int index;
    int corlen = 0;
    int pattern_len = 0;

    

    while (*(pattern + pattern_len) != '\0')
    {
        pattern_len++;
    }

    if (pattern_len > len)
    {
        return found;
    }

    if(large == nullptr)//----------------------------------------------------------------------- og small array
    {
            for (int i = 0; i < len; i++)
            {
                //cout << (found == false) << endl;
                if (found == false && found == false)
                {
                for (int j = 0; j < pattern_len; j++)
                {
                    if(*(small + i) == *(pattern + j))
                    {
                        index = i;
                        firstfind = true;
                    }
                }
                if (firstfind == true)
                {
                    firstfind = false;
                    found = true;
                    corlen++;
                    //cout << "find1" << endl;
                    continue;
                }
                }   

                if(found == true)
                {
                        if(*(small + i) == *(pattern + corlen))
                        {
                            afterfind = true;
                        }
                    
                    if (afterfind == true)
                    {
                        afterfind = false;
                        corlen++;
                    }
                    else
                    {
                        afterfind = false;
                        corlen = 0;
                        found = false;
                    }

                    if(corlen == pattern_len)
                    {
                        found = true;
                        break;
                    }

                }
            }

    }
    else//------------------------------------------------------------------------------------------- og is large array
    {
        //cout << "HEYOOOO" << endl;
        
            for (int i = 0; i < len; i++)
            {
                //cout << (found == false) << endl;
                if (found == false)
                {
                for (int j = 0; j < pattern_len; j++)
                {
                    if(*(large + i) == *(pattern + j))
                    {
                        index = i;
                        firstfind = true;
                        
                    }
                }
                if (firstfind == true)
                {
                    firstfind = false;
                    found = true;
                    corlen++;
                    //cout << "find1" << endl;
                    continue;
                }
                }   

                if(found == true)
                {
                    if(*(large + i) == *(pattern + corlen))
                    {
                        afterfind = true;
                    }
                    
                    if (afterfind == true)
                    {
                        afterfind = false;
                        corlen++;
                    }
                    else
                    {
                        afterfind = false;
                        corlen = 0;
                        found = false;
                    }

                    if(corlen == pattern_len)
                    {
                        found = true;
                        break;
                    }

                }
            }
    }

    if (found == false)
    {
        return -1;
    }
    else
    {
        return index;
    }


    return found;
}

int String::find_char(char ch) const
{
    //bool firstfind = false;
    //bool afterfind = false;
    bool found = false;
    //int corlen = 0;
    int index = 0;


    if (1 > len)
    {
        return found;
    }

    if(large == nullptr)//----------------------------------------------------------------------- og small array
    {
            for (int i = 0; i < len; i++)
            {
  
                    if(*(small + i) == ch)
                    {
                        index = i;
                        found = true;
                    }
            }
    }
    else//------------------------------------------------------------------------------------------- og is large array
    {
           for (int i = 0; i < len; i++)
            {
  
                    if(*(large + i) == ch)
                    {
                        index = i;
                        found = true;
                    }
            }
    }

    if (found == false)
    {
        return -1;
    }
    else
    {
        return index;
    }


    return found;
}

void String::print() const //final print func oat
{
    if (large == nullptr)
    {
        for (int i = 0; i < len; i++)
        {
            cout << small[i];
        }
    }
    else
    {
        for (int i = 0; i < len; i++)
        {
            cout << large[i];
        }
    }
}
