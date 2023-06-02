#include <iostream>
#include <string>

class Car
{
	std::string  manufacture;
	std::string  model;
	std::string  color;
	int          year;
	float        maxSpeed;

public:

	Car()
	{
		manufacture = "";
		model = "";
		color = "";
		year = 0;
		maxSpeed = 0;
	}

	class Builder
	{
		std::string  manufacture;
		std::string  model;
		std::string  color;
		int          year;
		float        maxSpeed;

	public:

		Builder() 
		{
			manufacture = "";
			model = "";
			color = "";
			year = 0;
			maxSpeed = 0;
		}

		Builder& setManufacture(std::string manufacture) { this->manufacture = manufacture; return *this; }
		Builder& setModel(std::string model)               { this->model       = model;  return *this; }
		Builder& setColor(std::string color)               { this->color       = color; return *this;}
		Builder& setYear(int year)                         { this->year      = year; return *this;}
		Builder& setMaxSpeed(float maxSpeed)               { this->maxSpeed    = maxSpeed; return *this;}
		Car build() 
		{
			Car car;
			car.manufacture = manufacture;
			car.model = model;
			car.color = color;
			car.year = year;
			car.maxSpeed = maxSpeed;
			return car;
		}
	};

	std::string getManufacture() { return manufacture; }
	std::string getModel()       { return model; }
	std::string getColor()       { return color; }
	int         getYear()      { return year; }
	float       getMaxSpeed()    { return maxSpeed; }
};

std::ostream& operator<<(std::ostream& os, const Car& obj) {
	Car tmp = obj;
	os << "[";
	os << tmp.getManufacture() << ", ";
	os << tmp.getModel() << ", ";
	os << tmp.getColor() << ", ";
	os << tmp.getYear() << ", ";
	os << tmp.getMaxSpeed();
	os << "]";
	return os;
}

int main() {


	Car chevrolet = Car::Builder().
		setManufacture("Chevrolet").
		setModel("Camaro").
		setColor("Yellow").
		setYear(2007).
		setMaxSpeed(270).
		build();

	std::cout << chevrolet << "\n";
	std::getchar();

	return 0;
}