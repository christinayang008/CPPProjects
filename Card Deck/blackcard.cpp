#include <iostream>
#include <cstdlib>
#include "blackcard.h"

BlackCard::BlackCard(int v) : Card(v)
{
	SetValue(v);
}

string BlackCard::Description() const
// Outputs card characteristics - value as a string
// DO NOT MODIFY THIS METHOD !!!!
{
	string d = "Value = ";    // temporary variable used to accumulate result

	switch (GetValue())            // Append card value to variable's value
	{
	case 2:   d = d + "2";    break;      // Number cards
	case 3:   d = d + "3";    break;
	case 4:   d = d + "4";    break;
	case 5:   d = d + "5";    break;
	case 6:   d = d + "6";    break;
	case 7:   d = d + "7";    break;
	case 8:   d = d + "8";    break;
	case 9:   d = d + "9";    break;
	case 10:  d = d + "10";   break;

	case 11:  d = d + "J";    break;      // Face cards
	case 12:  d = d + "Q";    break;
	case 13:  d = d + "K";    break;
	case 14:  d = d + "A";    break;

	default:  d = d + "?";    break;      // Unknown card
	}

	d = d + "\nColor = Black";

	return d;                 // Return string describing card value
}