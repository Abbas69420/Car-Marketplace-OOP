#ifndef VEHICLE
#define VEHICLE

#include <iostream>
using namespace std;

class Vehicle
{
protected:
    string brand;
    string model;
    int year;
    int mileage;
    string colour;
    string transmission;

public:
    Vehicle() : brand(""), model(""), year(0), mileage(0), colour(""), transmission("") {}

    Vehicle(string brand, string model, int year, int mileage, string colour, string transmission)
    {
        this->brand = brand;
        this->model = model;
        this->year = year;
        this->mileage = mileage;
        this->colour = colour;
        this->transmission = transmission;
    }

    virtual void displayDetails() const
    {
        cout << "Brand: " << brand << endl;
        cout << "Model: " << model << endl;
        cout << "Year: " << year << endl;
        cout << "Mileage: " << mileage << " km" << endl;
        cout << "Colour: " << colour << endl;
        cout << "Transmission: " << transmission << endl;
    }

    bool isEligibleForInspection() const
    {
        return (year > 2014 && mileage < 150000);
    }

    void updateMileage(int newMileage)
    {
        mileage = newMileage;
    }

    void updateColour(string newColour)
    {
        colour = newColour;
    }

    string getBrand() const
    {
        return brand;
    }
    string getModel() const
    {
        return model;
    }
    int getYear() const
    {
        return year;
    }
    int getMileage() const
    {
        return mileage;
    }

    virtual ~Vehicle() {}
    virtual string getVehicleType() const = 0;
};

#endif
