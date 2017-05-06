#include <iostream>
#include <string>
#include <cstdlib>


using namespace std;
float toFloat(string s);

int main() {
	int quit = 0;
	while (quit == 0)
	{
//Reading the string from user and saving it as strig
		string input;
		string polygons;

		getline(cin, input);

//Quits if the input was "Quit"
		if (input == "Quit"){
			quit = 1;
			break;
		}

// Removing Polygos=[] from the string and saving it to polygons string
		int start = input.find("(");
		int end = input.rfind(")");
		int count = 1;

// if empty string print "none" and break
		if (start == -1) {
			cout << "none" << endl;
			count = 0;
		}
		else
		{
			polygons = ";" + input.substr(start, end - start + 1) + ";";
		}
//Counting the polygons
		while (count==1)
		{
			int polyNo = 0;
			for (int i = 0; i <= polygons.length(); i++) {
				if (polygons[i] == ';') {
					polyNo++;
				}
			}
			cout << polyNo - 1 << endl;	//Polygons number
			count = 0;
		}

//Counting the points
		int pointsNo = 0;
		for (int i = 0; i <= polygons.length(); i++) {
			if (polygons[i] == '(') {
				pointsNo++;
			}
		}
		if (pointsNo!=0)
			cout << pointsNo << endl;	//points number
		else
			cout << "none" << endl;
//****************************************************************************************************End of 1,2 Operations


//finding X and Y of all points and storing them in two arrays
	//Changning Format
		string str = polygons;
		for (int i = 0; i <= 2; i++) {
			for (int i = 0; i <= str.length(); i++) {
				if (str.substr(i, 3) == "),(")
					str.replace(i, 3, "s");
				
				if (str.substr(i, 3) == ");(")
					str.replace(i, 3, "s");

				if (str[i] == ')')
					str.replace(i, 1, "s");

				if (str[i] == '(')
					str.replace(i, 1, "s");

				if (str[i] == ',')
					str.replace(i, 1, "s");
			}
		}
		
	//Array of X points
		float xPoints[10000] ;
		float yPoints[10000] ;
		int firstS = str.find("s");
		int secS = str.find("s", firstS + 1);
		for (int i = 0; i <= str.length(); i++) {
			if (firstS != string::npos && secS != string::npos) {
				xPoints[i] = toFloat(str.substr(firstS + 1, secS - firstS - 1));
				firstS = secS;
				secS = str.find("s", firstS + 1);
				firstS = secS;
				secS = str.find("s", firstS + 1);
			}
			else
				break;
		}
		firstS = str.find("s");
		firstS = str.find("s", firstS + 1);
		secS = str.find("s", firstS + 1);
		for (int i = 0; i <= str.length(); i++) {
			if (firstS != string::npos && secS != string::npos) {
				yPoints[i] = toFloat(str.substr(firstS + 1, secS - firstS - 1));
				firstS = secS;
				secS = str.find("s", firstS + 1);
				firstS = secS;
				secS = str.find("s", firstS + 1);
			}
			else
				break;
		}
	//Finding and printing Max X and min X
		float Xmax = xPoints[0];
		float Xmin = xPoints[0];
		for (int i = 0; i < 10000; i++) {
			if (xPoints[i] != -107374176.) {
				if (xPoints[i] > Xmax)
					Xmax = xPoints[i];
				if (xPoints[i] < Xmin)
					Xmin = xPoints[i];
			}
		}

			cout << Xmin << endl;	//Min X

			cout << Xmax << endl;	//Max X



//Finding and printing Max Y and min Y
		float Ymax = yPoints[0];
		float Ymin = yPoints[0];
		for (int i = 0; i < 10000; i++) {
			if (yPoints[i] != -107374176.) {
				if (yPoints[i] > Ymax)
					Ymax = yPoints[i];
				if (yPoints[i] < Ymin)
					Ymin = yPoints[i];
			}
		}
		
			cout << Ymin << endl;	//Min Y
		
			cout << Ymax << endl;	//Max Y
		

//Printing The enclousing rectanngle
		cout << "(" << Xmax << "," << Ymax << ")" << "," 
		 	 << "(" << Xmax << "," << Ymin << ")" << "," 
			 << "(" << Xmin << "," << Ymin << ")" << "," 
			 << "(" << Xmin << "," << Ymax << ")"  << endl;

//*****************************************************************************************End of 3,4,5,6,7 Operations

//Cutting Polygons in arrays
		string pol[1000];  // pol[polygon's number-1] array of polygons

		int firstSemi = polygons.find(";");
		int secSemi = polygons.find(";", firstSemi + 1);
		for (int i = 0; i <= 100; i++) {
			if (firstSemi != string::npos) {
				pol[i] = "s" + polygons.substr(firstSemi + 1, secSemi - firstSemi - 1) + "s";
				firstSemi = secSemi;
				secSemi = polygons.find(";", firstSemi + 1);
			}
			else
				break;
		}
		

//finding Redundant points (repeated points) (point lying on a line of previous and next points)
		// repeated points

		//removing separiting commas and putting s instead of it
		for (int j = 0; j < 1000; j++) {
			for ( int i = 0; i < pol[j].length(); i++){
				if (pol[j].substr(i, 3) == "),(")
					pol[j].replace(i, 3, ")s(");
			}
		}
		string polygonsPoints[100][100];//array of 100 polygons and 100 points for each poylgon
		for (int j = 0; j < 100; j++) {
			int s1 = pol[j].find("s");
			int s2 = pol[j].find("s", s1 + 1);
			int repeat = 0;
			for (int i = 0; i <= pol[j].length(); i++) {
				if (pol[j].substr(i, 1) == "s")
					repeat++;
			}
			for (int i = 0; i <= repeat - 1; i++) {
				if (s1 != string::npos) {
					polygonsPoints[j][i] = pol[j].substr(s1 + 1, s2 - s1 - 1);
					s1 = s2;
					s2 = pol[j].find("s", s1 + 1);
				}
				else
					break;
			}
		}
		//counting reduntant points 
		int redNo = 0;
		for (int j = 0; j < 100; j++) {
			for (int i = 0; i < 100; i++) {
				if (polygonsPoints[j][i] != "") {
					if (polygonsPoints[j][i] == polygonsPoints[j][i + 1]) {
						redNo++;
					}
				}
			}
		}
		cout << redNo << endl;
		// point lying on a line of previous and next points




	} // end of last(9) operation of level 1
	return 0;
}

float toFloat(string s){
	return atof(s.c_str());
}
