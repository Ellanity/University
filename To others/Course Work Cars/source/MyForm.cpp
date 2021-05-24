#include <set>
#include <msclr/marshal_cppstd.h>

#include "MyForm.h"
#include "CourseWork.h"
/* using namespace System; */
/* using namespace System::Windows::Forms; */

/* All cars that were added */
std::set <Car> cars;

/* main function, creates window with forms */
[System::STAThreadAttribute]
void main(array<System::String^>^ args)
{
	System::Windows::Forms::Application::EnableVisualStyles();
	System::Windows::Forms::Application::SetCompatibleTextRenderingDefault(false);
	
	CourseWork::MyForm form;
	System::Windows::Forms::Application::Run(% form);
}

/* Function to create simple car */
System::Void CourseWork::MyForm::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	try {
		/* Check fields before creating car */
		std::string name = "";
		int speed = -1;

		/* msclr::interop::marshal_as<std::string> creates from System::String to std::string */
		try { name = msclr::interop::marshal_as<std::string>(textBox1->Text); }
		catch (System::FormatException^ e) { textBox1->Text = "Invalid"; }
		if (name == "")
			textBox1->Text = "Invalid";

		try { speed = Int32::Parse(textBox2->Text); }
		catch (System::FormatException^ e) { textBox2->Text = "Invalid"; }

		if (speed >= 0 && name != "") {

			/* Object of the Car class, push it to all cars */
			Car car(name, speed);
			cars.insert(car);

			showInformation();
			textBox1->Text = "";
			textBox2->Text = "";
		}
	}
	catch (System::Exception^ e) {}
	/* Catching exceptions related to forms */
}

/* Function to create executive car */
System::Void CourseWork::MyForm::button2_Click(System::Object^ sender, System::EventArgs^ e)
{
	try {
		std::string name = "";
		int speed = -1;

		try { name = msclr::interop::marshal_as<std::string>(textBox1->Text); }
		catch (System::FormatException^ e) { textBox1->Text = "Invalid"; }
		if (name == "")
			textBox1->Text = "Invalid";

		try { speed = Int32::Parse(textBox2->Text); }
		catch (System::FormatException^ e) { textBox2->Text = "Invalid"; }


		if (speed >= 0 && name != "") {
			
			ExecutiveCar car(name, speed);
			cars.insert(car);

			showInformation();
			textBox1->Text = "";
			textBox2->Text = "";
		}
	}
	catch (System::Exception^ e) {}
}

/* Update all cars in the list */
System::Void CourseWork::MyForm::button3_Click(System::Object^ sender, System::EventArgs^ e) 
{
	/* New list of all cars */
	std::set<Car> newCars; 

	/* Read all cars. Change them depending on their type(simple/executive) */
	std::set<Car>::iterator it = cars.begin();
	for (int i = 0; it != cars.end(); i++, it++)
	{
		/* Creates object of car */
		Car car = *it; 
		if (car.getType() == "executive")
		{
			/* If type is executive -> create same car (object) of right class (ExecutiveCar) */
			ExecutiveCar newCar(car.getName(), car.getSpeed());
			newCar.updatingModel();
			newCars.insert(newCar);
		}
		else
		{
			/* If type is simple -> no need to create new object */
			car.updatingModel();
			newCars.insert(car);
		}
	}
	/* Changing of previous list */
	cars = newCars;
	showInformation();
	return System::Void();
}

/* Function to show full information about car depending on their type */
void CourseWork::MyForm::showInformation()
{
	textBox3->Text = "";
	std::set<Car>::iterator it = cars.begin();
	for (int i = 0; it != cars.end(); i++, it++)
	{
		Car car = *it;
		std::string speed, cost;
		if (car.getType() == "executive")
		{
			ExecutiveCar newCar(car.getName(), car.getSpeed());
			speed = std::to_string(newCar.getSpeed());
			cost = std::to_string(newCar.getCost());
		}
		else
		{
			speed = std::to_string(car.getSpeed());
			cost = std::to_string(car.getCost());
		}

		/* Format of presentation */
		std::string carRow = std::to_string(i + 1) + 
			") Type: " + car.getType() +
			" Name: "  + car.getName() +
			" Speed: " + speed +
			" Cost: "  + cost + "\r\n"; 
			/* For new line need to use \r\n */

		textBox3->Text += msclr::interop::marshal_as<System::String^>(carRow);
	}
}