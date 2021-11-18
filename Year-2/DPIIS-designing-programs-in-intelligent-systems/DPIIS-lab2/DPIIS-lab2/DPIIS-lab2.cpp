#include "ArtworkPicture.h"
#include "ArtworkSculpture.h"
#include "ArtworkExposition.h"

#include "ArtworkPublic.h"
#include "ArtworkProtected.h"
#include "ArtworkPrivate.h"
#include "ARtworkMultipleInheritance.h"

#include <ctime>
//#include <math.h>

using std::cout;
using std::cin;

namespace My {
	int max(int a, int b) { return std::max(a, b); }
}

int main()
{
	/*

	// Creating data (pictures, age) for tests
	srand(time(0));
	int age = rand() % 10000;
	std::string str(15, 219);
	std::vector<std::string> pic_pic_3(10, str);
	for (int i = 1; i < 9; i++)
		for (int j = 1; j < 14; j++)
			if (rand() % 2 == 1)
				pic_pic_3[i][j] = 32;
	std::vector <std::string> pic(5, "|||||||");


	// ArtworkPicture Class
	cout << "[ArtworkPicture] Tests:\n";
	cout << "[ArtworkPicture] Initialization:\n";
	ArtworkPicture pic_1(age, "Computer", "Best picture ever"), 
				   pic_2,
				   pic_3(1344431, "He", "AMAZING", 12, pic_pic_3);
	cout << "[Artwork] Count of instances: ";
	cout << pic_1.get_count_of_instances() << "\n";
	
	cout << "[ArtworkPicture] Info | Instance | 1 |:\n";
	cout << "Description: " << pic_1._description << " " <<
			"Age: "         << pic_1.get_age()    << " " <<
			"Author: "      << pic_1.get_author() << "\n";
	pic_1.installation(); cout << "\n";
	pic_1.print_picture();
	cout << "[ArtworkPicture] Info | Instance | 2 |:\n";
	cout << "Description: " << pic_2._description << " " <<
			"Age: "	        << pic_2.get_age()    << " " <<
			"Author: "      << pic_2.get_author() << "\n";
	pic_2.installation(); cout << "\n";
	pic_2.print_picture();
	cout << "[ArtworkPicture] Info | Instance | 3 |:\n";
	cout << "Description: " << pic_3._description << " " <<
			"Age: "         << pic_3.get_age()    << " " <<
			"Author: "      << pic_3.get_author() << "\n";
	pic_3.installation(); cout << "\n";
	pic_3.print_picture();
	
	cout << "[ArtworkPicture] Test | Changing Instance | 2 |:\n";
	cout << "[ArtworkPicture] Info | Instance | 2 | Picture |:\n";
	pic_2.set_picture(pic);
	pic_2.print_picture();

	
	// ArtworkSculpture class
	cout << "[ArtworkSculpture] Tests:\n";
	cout << "[ArtworkSculpture] Initialization:\n";
	ArtworkSculpture sclpt_1(1,"He", "Not bad sculpture"), sclpt_2;
	cout << "[Artwork] Count of instances: ";
	cout << sclpt_1.get_count_of_instances() << "\n";

	cout << "[ArtworkSculpture] Info | Instance | 1 |:\n";
	sclpt_1.installation();
	cout << "Volume: "      << sclpt_1.get_volume() << " " <<
			"Description: " << sclpt_1._description << " " << 
			"Age: "	        << sclpt_1.get_age()    << " " << 
			"Author: "      << sclpt_1.get_author() << "\n";
	cout << "[ArtworkSculpture] Info | Instance | 2 |:\n";
	sclpt_2.installation();
	cout << "Volume: "      << sclpt_2.get_volume() << " " << 
			"Description: " << sclpt_2._description << " " << 
			"Age: "         << sclpt_2.get_age()    << " " << 
			"Author: "      << sclpt_2.get_author() << "\n";


	// ArtworkExposition class
	cout << "[ArtworkExposition] Tests:\n";
	cout << "[ArtworkExposition] Initialization:\n";
	ArtworkExposition exp_1(pic_1.get_age(), pic_3.get_author(), sclpt_1._description);
	cout << "[Artwork] Count of instances: ";
	cout << exp_1.ArtworkPicture::get_count_of_instances() << "\n";

	exp_1.show_exposition();
	cout << "age: " << My::max(pic_1.get_age(), 99999) << "\n";
	

	*/

	ArtworkPublic apublic;
	ArtworkPrivate aprivate;
	ArtworkProtected aprotected;
	ARtworkMultipleInheritance ami;

	//apublic.installation();
	cout << apublic.get_class_id() << "\n";
	//aprotected.installation();
	cout << aprotected.transmitter() << "\n";
	//aprivate.installation();
	cout << aprivate.transmitter() << "\n";
	//
	ami.installation(); 
	cout << "\n"; ami.ArtworkPublic::installation();
	// cout << "\n"; ami.transmitter();
	cout << "\n" << ami.ArtworkProtected::transmitter();
	cout << "\n" << ami.ArtworkPrivate::transmitter();

	ARtworkMultipleInheritance ami2;
	ArtworkPublic* apub = &ami2;
	cout << "\n"; apub->installation();
	cout << "\n" << apub->ArtworkPublic::class_id << "\n";
	//cout << apub->ArtworkProtected::class_id << "\n";
	//cout << apub->ArtworkPrivate::class_id << "\n";

	return 0;
}
