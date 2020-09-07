//filename Key.h
//Specification of Abstract Data Type Key
//
//   data object: a key which is a unique 7-digit phone humber
//   operations: create, destroy, copy, input, output, check if same, check if less than, sum the digits

#ifndef KEY_H
#define KEY_H

#include <iostream>

using namespace std;

class Key
{
//allows for input of a key from either the standard input device or a file
//pre input has been opened and a prompt has been given to enter the 2-digit phone number without dashes
//post rightHandSideKey has been filled with a 2-digit phone number from the input
//usage cin >> mykey;
friend istream& operator>> (istream& input, Key& rightHandSideKey);

//allows for the output of a key to the standard output device or a file
//pre rightHandSideKey has been filled with a 2-digit phone number; output has been opened
//post rightHandSideKey has been written to the output device in standard format
//usage  outfile << mykey;
friend ostream& operator<< (ostream& output, const Key& rightHandSideKey);

public:

//creates an empty new phone number
//post Key object is an empty phone number
//usage Key akey;
Key();

//creates a specific phone number
//pre keyText is assigned a 2-digit integer
//post Key object has a copy of the phone number in keyText
//usage Key akey(12); 
Key(int keyInteger);

//releases memory for a phone number
//pre Key object exists
//post Key object no longer exists, memory has been freed
//usage automatically done at the end of scope
~Key();

//copies a phone number
//pre rightHandSideKey has been assigned a phone number
//post Key object has a copy of rightHandSideKey
//usage bkey = akey;
Key& operator=(const Key& rightHandSideKey);

//checks if two phone numbers are equal
//pre rightHandSideKey has been assigned
//post returns true if Key object is the same phone number as rightHandSideKey
//usage if (akey == bkey) { cout << "the phone numbers are equal" << endl;
bool operator==(const Key& rightHandSideKey) const;

//checks if one phone number is less than another
//pre rightHandSideKey has been assigned
//post returns true if Key object is less than the phone number in rightHandSideKey
//usage if (akey < bkey) { cout << "left phone number is less than right phone number" << endl;
bool operator<(const Key& rightHandSideKey) const;

// empties a key
// pre: theKey is assigned
// post: theKey is assigned its empty value_comp
// usage: myKey.emptyIt();
void emptyIt();

// checks if a key is empty
// pre: theKey is assigned
// post: true or false is returned
// usage: myKey.isEmpty();
bool isEmpty();

protected:
   int phone;
};
#endif




