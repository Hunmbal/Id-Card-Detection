#pragma once
#include <string>
using namespace std;
class CNIC
{

public:
	int chip_w;
	int chip_h;
	int chip_x;
	int chip_y;

	int card_w;
	int card_h;
	int card_x;
	int card_y;

	int id;


	CNIC();



	bool isValid();

	bool isCNIC(string x);

	int getID(string x);

};

