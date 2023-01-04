#include "CNIC.h"
#include <iostream>
#include <algorithm>
using namespace std;



CNIC::CNIC() {

	chip_w = 0;
	chip_h = 0;
	chip_x = 0;
	chip_y = 0;

	card_w = 0;
	card_h = 0;
	card_x = 0;
	card_y = 0;

}


bool CNIC::isValid() {

	int xmap = card_x - (chip_x - (chip_w * 0.7));
	int ymap = card_y - (chip_y - (chip_h * 1.5));

	int chip_area = chip_w * chip_h;
	int card_area = card_w * card_h;

	if (xmap < 0) {	xmap *= -1;	}
	if (ymap < 0) { ymap *= -1; }

	if (xmap < 30 && ymap < 30) {
		if (card_area / chip_area < 35 && card_area / chip_area > 25) {
			cout << "VALID !!!!!!!!!!!!!!!!!!!!";
			return true;

		}

	}

	return false;


}


bool CNIC::isCNIC(string x) {

	int i = 0;
	transform(x.begin(), x.end(), x.begin(), ::tolower);

	//cout << x;
	//cout << "1st Read" << endl;

	if (x.find("pakistan") != std::string::npos) i++;
	if (x.find("national") != std::string::npos) i++;
	if (x.find("identity") != std::string::npos) i++;
	if (x.find("card") != std::string::npos) i++;


	if (i > 7) { return true; }
	return false;
}


int CNIC::getID(string x) {



	return 0;
}