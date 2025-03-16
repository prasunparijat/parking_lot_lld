# Requirements :
- Vehicle -- Bike | Car | Truck + scope for other vehicles
- Time Tracking -- Timed Parking for Billing (Mostly hours)
- Bill Generation -- Calculate cost for each vehicle type for the amount of Time Tracked
- Filling -- First come , first serve
- Payment -- Collect payment + Free space

# Future work :
- Floors of the parking
- Waiting queue for the vehicles when parking is full

Clarify and chat with the interviewer anyways - to clear doubts or go through with the thoughtprocess

# Class Diagram UML :
- [Link](https://lucid.app/lucidchart/d508f4a9-661f-48f9-a84d-84d0814fb80a/edit?viewport_loc=-1534%2C-493%2C4399%2C2036%2CHWEp-vi-RSFO&invitationId=inv_850bbc19-0449-4fab-903e-72872b137491)


# UML - Unified Modelling Language
- Class Diagram
- Use Case Diagram

# Notes :
- enum class vs enum - Scoped Enum - Safer - No implicit conversion to integers - can use eCar, eBike to denote the same but rather I prefer CAR , BIKE etc.
- Virtual function - can be overridden, which means that the correct function to call is determined at runtime. Non-virtual functions can be hidden, which means that the derived class's implementation is used only when called through a derived class pointer or reference.

```cpp
class Animal {
public:
    void sound() { cout << " Generic animal sound" << endl; }
};

class Dog : public Animal {
public:
    void sound() { cout << "Woof!" << endl; } // Hides Animal::sound()
};

int main() {
    Dog dog;
    dog.sound(); // Output: Woof!
    return 0;
}
```
When accessed through a parent class's reference - the base implementation itself prevails - which can lead to bugs
```cpp
int main() {
    Animal* animal = new Dog();
    animal->sound(); // Output: Generic animal sound
    return 0;
}
```
- GetVacantSpot (ParkingLot Method) -- improvements :
  1) Keep a vector<GridPosition> of all the vacant spaces - and keep removing and adding from this pool when parked and when something leaves
  2) Not thread safe
- For windows - use the windows.h header file and then Sleep(x) to cause an intentional delay, For every system it is OS specific - as the this_thread did not work here.