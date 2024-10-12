/*
Suhail Attaelmanan
June 7 2024
distance project 1: The program prompts the user to enter a number followed by a unit type.
Then prints out the distance in metres, followed by a table of the equivalent distances in metric and imperial units.
*/

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip> 
#include <algorithm>
#include <cctype>

using namespace std;

// Properties for metric Units and imperail Units
struct Unit {
	string name;
	string symbol;
	string fullName;
	string plurals;
	double conversion;
};

// Metric units array
const Unit metricUnits[] = {
	{"m", "m", "metre","metres" ,1.0},
	{"km", "km", "kilometre","kilometres", 1e3},
	{"cm", "cm", "centimetre","centimetres", 1e-2},
	{"mm", "mm", "millimetre", "millimetres",1e-3},
	{"um", "um", "micrometre","micrometres", 1e-6},
	{"nm", "nm", "nanometre", "nanometres",1e-9},
	{"pm", "pm", "picometre", "picometres",1e-12},
	{"fm", "fm", "femtometre", "femtometres",1e-15},
	{"dam", "dam", "decametre","decametres", 1e1},
	{"hm", "hm", "hectometre","hectometres", 1e2},
	{"Mm", "Mm", "megametre","megametres", 1e6},
	{"Gm", "Gm", "gigametre","gigametres", 1e9},
	{"Tm", "Tm", "terametre", "terametres",1e12},
	{"Pm", "Pm", "petametre", "petametres",1e15},
	{"Em", "Em", "exametre","exametres",1e18},
	{"Zm", "Zm", "zettametre","zettametres", 1e21},
	{"Ym", "Ym", "yottametre", "yottametres",1e24},
	{"dm", "dm", "decimetre","decimetres",1e-1},
	{"am","am","attometre","attometres",1e-18},
	{"zm","zm","zeptometre","zeptometres",1e-21},
	{"ym","ym","yoctometre","yoctometres",1e-24}
};

// Imperail units array
const Unit imperialUnits[] = {
	{"in", "\"", "inch", "inches",0.0254},
	{"ft", "'", "foot", "feet",0.3048},
	{"yd", "yd", "yard", "yardes",0.9144},
	{"mi", "mi", "mile","miles", 1609.344},
	{"lea", "lea", "league","leagues", 4828.032},
	{"nmi", "nmi", "nautical mile","nautical miles", 1852.0},
	{"ftm", "ftm", "fathom","fathoms", 1.852},
	{"ch", "ch", "chain","chains", 20.1168},
	{"fur", "fur", "furlong", "furlongs",201.168},
	{"link", "link", "link","links", 0.201168},
	{"rod", "rod", "rod","rods", 5.0292},
	{"h", "h", "hand", "hands",0.1016},
	{"Bc", "Bc", "barleycorn","barleycorns", 0.0084667},
	{"th", "th", "thou","thous", 0.0000254},
	{"twip", "twip", "twip","twips", 0.0000176389},
	{"cable","cable","cable","cables",185.2}
};

/*
isValidUnit
This function used to check if the unit that the user typed is vaild or not in the arrays
*/
bool isValidUnit(const string& unit) {
	for (const Unit& u : metricUnits) {
		if (unit == u.name || unit == u.symbol || unit == u.fullName || unit == u.plurals) {
			return true;
		}
	}
	for (const Unit& u : imperialUnits) {
		if (unit == u.name || unit == u.symbol || unit == u.fullName || unit == u.plurals) {
			return true;
		}
	}
	return false;
}

/*
toLower
Makes strings lower case
*/
string toLower(string& s) {
	for (char& c : s)
		c = tolower(c);
	return s;
}

/*
isImperial
checks for Imperial units
*/
bool isImperial(string& unit) {
	for (const Unit& u : imperialUnits) {
		if (unit == u.name || unit == u.symbol || unit == u.fullName || unit == u.plurals) {
			return true;
		}
	}
	return false;
}

/*
isMetric
checks for Metric Units
*/
bool isMetric(string& unit) {
	for (const Unit& u : metricUnits) {
		if (unit == u.name || unit == u.symbol || unit == u.fullName || unit == u.plurals) {
			return true;
		}
	}
	return false;
}

int main() {
	// Title
	cout << "distances 1.1.0: (c) 2024, Suhail Attaelmanan\n";

	// Prompt the user to enter number and unit name
	cout << "Enter a real-number distance followed by unit name.\n" << endl;
	cout << "Distance: ";
	string input;
	getline(cin, input);

	// parse the input
	istringstream iss(input);
	double value;
	string unit;

	// non-numeric values
	if (!(iss >> value)) {
		cerr << "Error: you did not enter a recognizable number." << endl;
		cerr << "usage: dddd.ddd unittype" << endl;
	}

	// missing unit
	else if (!(iss >> unit)) {
		cerr << "Error: the unit type " << "'" << unit << "'" << " is not recognized." << endl;
		cerr << "usage: dddd.ddd unittype" << endl;
	}

	// Convert the unit to lowercase if it's an imperial unit and covert the value to metres:

	double distanceInMeters = value;
	string unitTemp = unit;
	toLower(unit);
	if (isImperial(unit)) {
		//cout << unit << " Worked! Imperial" << endl;
		for (const Unit& u : imperialUnits) {
			if (unit == u.name || unit == u.symbol || unit == u.fullName || unit == u.plurals) {
				distanceInMeters *= u.conversion;
				break;
			}
		}
	}
	else if (unit = unitTemp; isMetric(unit)) {
		//cout << unit << " Worked! Metric" << endl;
		for (const Unit& u : metricUnits) {
			if (unit == u.name || unit == u.symbol || unit == u.fullName || unit == u.plurals) {
				distanceInMeters *= u.conversion;
				break;
			}
		}
	}
	// unrceognized unit type 
	if (!isValidUnit(unit)) {
		cerr << "Error: the unit type " << "'" << unit << "'" << " is not recognized." << endl;
		cerr << "usage: dddd.ddd unittype" << endl;
		return 1; // Quits
	}

	// output the number and the unit
	cout << fixed << setprecision(3);
	cout << "\n" << "\"" << value << " " << unit << "\"" << " is " << distanceInMeters << " metres." << endl;

	// output the table of conversions:
	cout << "\n";
	cout << setw(20) << "Metric" << setw(30) << "Imperial" << endl;
	cout << setw(20) << "=======" << setw(30) << "========" << endl;

	// index for metric and imperail arrays
	int metricIndex = 0;
	int imperialIndex = 0;

	// using a loop to print
	while (metricIndex < 21 || imperialIndex < 16) {

		// output metric 
		if (metricIndex < 21) {
			double metricDistance = distanceInMeters / metricUnits[metricIndex].conversion;
			cout << setw(20) << scientific << metricDistance << " " << metricUnits[metricIndex].symbol;
			++metricIndex;
		}
		else {
			cout << setw(20) << " ";
		}

		// output imperial distance
		if (imperialIndex < 16) {
			double imperialDistance = distanceInMeters / imperialUnits[imperialIndex].conversion;
			cout << setw(25) << fixed << setprecision(3) << imperialDistance << " " << imperialUnits[imperialIndex].fullName << endl;
			++imperialIndex;
		}

		else {
			cout << setw(30) << " " << endl;
		}
	}
}