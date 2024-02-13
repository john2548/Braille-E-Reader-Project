// char_c.c : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include "char_c.h"
#include "pin.h"

#define TOTAL_CHARS 26 // A-Z a-z 0-9 ' ' ...
#define MAX_CHARS_PER_LINE 10

int main()
{
    Char_c ALL_CHARS[TOTAL_CHARS];
    // may need modificaiton if double cells for caps, numbers

    // Create the list of characters
    // Check reddit for caps and numbers

    // caps and digits may require an array of size 2 of cells
    // capital letters
    // A B C .... X Y Z
    // lower case letters
    // a b c .... x y z
    char lowercaseChars[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                                'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

    bool lowercaseFlags[26][6] = {
        { 1,0,0,0,0,0 }, //a
        { 1,1,0,0,0,0 }, //b
        { 1,0,0,1,0,0 }, //c
        { 1,0,0,1,1,0 }, //d
        { 1,0,0,0,1,0 }, //e
        { 1,1,0,1,0,0 }, //f
        { 1,1,0,1,1,0 }, //g
        { 1,1,0,0,1,0 }, //h
        { 0,1,0,1,0,0 }, //i
        { 0,1,0,1,1,0 }, //j
        { 1,0,1,0,0,0 }, //k
        { 1,1,1,0,0,0 }, //l
        { 1,0,1,1,0,0 }, //m
        { 1,0,1,1,1,0 }, //n
        { 1,0,1,0,1,0 }, //o
        { 1,1,1,1,0,0 }, //p
        { 1,1,1,1,1,0 }, //q
        { 1,1,1,0,1,0 }, //r
        { 0,1,1,1,0,0 }, //s
        { 0,1,1,1,1,0 }, //t
        { 1,0,1,0,0,1 }, //u
        { 1,1,1,0,0,1 }, //v
        { 0,1,0,1,1,1 }, //w
        { 1,0,1,1,0,1 }, //x
        { 1,0,1,1,1,1 }, //y
        { 1,0,1,0,1,1 }  //z
    };

    // use this and when making a Char_c word, find the corresponding character match
    // and just copy that char
    // addChar = ALL_CHARS[x]
    // add addChar to the mappedText [][]
    for (int i = 0; i < 26; ++i) {
        ALL_CHARS[i] = createChar(lowercaseChars[i], lowercaseFlags[i]);
    }

    // OR go thru this process once for each letter 
    // I THINK this is easier even from a timing persepctive    

    // the 
    // t h e

    //ALL_CHARS[0] = createChar('a', lowercaseFlags);
    // digits
    // 0 1 2 ... 7 8 9
    // symbols
    // ' ' (space ) , period comma etc
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
