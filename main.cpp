#include <bits/stdc++.h>
#include <thread>
#include <windows.h>
using namespace std;

enum class VehicleType
{
    CAR,
    BIKE,
    TRUCK
};

class Payment
{
public:
    virtual double CalculateCost(double hours) = 0;
};

class BikePayment : public Payment
{
public:
    double CalculateCost(double hours)
    {
        return hours * 1;
    }
};

class CarPayment : public Payment
{
public:
    double CalculateCost(double hours)
    {
        return hours * 2;
    }
};

class TruckPayment : public Payment
{
public:
    double CalculateCost(double hours)
    {
        return hours * 5;
    }
};

class Vehicle
{
protected:
    int _id;
    Payment *_payment;
    chrono::time_point<chrono::system_clock> _parkTime;

public:
    virtual VehicleType GetType() = 0;

    double CalculateParkingTimeInHours()
    {
        return chrono::duration_cast<chrono::hours>(chrono::system_clock::now() - this->_parkTime).count();
    }

    double CalculateParkingTimeInMilliseconds()
    {
        return chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - this->_parkTime).count();
    }

    double CalculateParkingCost()
    {
        // const double hours = CalculateParkingTimeInHours();
        const double milliseconds = CalculateParkingTimeInMilliseconds();
        return this->_payment->CalculateCost(milliseconds); // can be written without the this keyword also
    }

    chrono::time_point<chrono::system_clock> GetParkTime()
    {
        return this->_parkTime;
    }

    void SetParkTime() { this->_parkTime = chrono::system_clock::now(); }

    int GetId() { return this->_id; }
};

using vVeh = vector<Vehicle *>;
using vvVeh = vector<vVeh>;

class Bike : public Vehicle
{
public:
    Bike(int id)
    {
        this->_id = id;
        this->_payment = new BikePayment();
    }
    VehicleType GetType() { return VehicleType::BIKE; }
};

class Car : public Vehicle
{
public:
    Car(int id)
    {
        this->_id = id;
        this->_payment = new CarPayment();
    }

    VehicleType GetType()
    {
        return VehicleType::CAR;
    }
};

class Truck : public Vehicle
{
public:
    Truck(int id)
    {
        this->_id = id;
        this->_payment = new TruckPayment();
    }
    VehicleType GetType() { return VehicleType::TRUCK; }
};

struct GridPosition
{
    int row;
    int col;
};

class ParkingLot
{
private:
    int _rows, _cols;
    vvVeh _parkingGrid;
    unordered_map<int, GridPosition> _parkedPostition;

public:
    ParkingLot(int rows, int cols)
    {
        _rows = rows;
        _cols = cols;
        _parkingGrid.resize(_rows, vVeh(_cols, nullptr));
    }

    GridPosition GetVacantSpot()
    {
        for (int i = 0; i < _rows; i++)
        {
            for (int j = 0; j < _cols; j++)
            {
                if (_parkingGrid[i][j] == nullptr)
                    return GridPosition{i, j};
            }
        }
        // cout << "No Vacant Spot" << endl;
        // return GridPosition{-1, -1};
        throw ::logic_error("No Vacant Spot");
    }

    void Park(Vehicle *vehicle)
    {
        GridPosition vacantSpot = GetVacantSpot();
        vehicle->SetParkTime();
        _parkingGrid[vacantSpot.row][vacantSpot.col] = vehicle;
        _parkedPostition[vehicle->GetId()] = vacantSpot;
        cout << "Vehicle Parked at Row : " << vacantSpot.row << " Column : " << vacantSpot.col << "\n"
             << "Remaining Spots : " << GetTotalAvailableSpots() << "\n\n";
    }

    GridPosition GetParkedPositionById(int id)
    {
        if (_parkedPostition.find(id) == _parkedPostition.end())
            throw ::logic_error("Vehicle not found");

        return _parkedPostition[id];
    }
    void PayAndLeave(int id)
    {
        GridPosition parkedPosition = GetParkedPositionById(id);
        double parkingCost = _parkingGrid[parkedPosition.row][parkedPosition.col]->CalculateParkingCost();
        cout << "Payable : " << parkingCost << " ---- "
             << "Transaction Completed\n\n";
        _parkingGrid[parkedPosition.row][parkedPosition.col] = nullptr;
        _parkedPostition.erase(id);
    }

    int GetTotalAvailableSpots()
    {
        return _rows * _cols - _parkedPostition.size();
    }
};

int main()
{
    ParkingLot parkingLot(2, 2);
    Car car(1), car2(2);
    Bike bike(3);
    Truck truck(4), truck2(5);
    try
    {
        parkingLot.Park(&car);
        Sleep(1000);
        parkingLot.Park(&car2);
        parkingLot.Park(&bike);
        parkingLot.Park(&truck);
        parkingLot.PayAndLeave(1);
        Sleep(1000);
        parkingLot.PayAndLeave(2);
        Sleep(1050);
        parkingLot.Park(&truck2);
        parkingLot.PayAndLeave(4);
        Sleep(1000);
        parkingLot.Park(&car2);
    }
    catch (logic_error e)
    {
        cout << e.what() << endl;
        return 1;
    }
    return 0;
}