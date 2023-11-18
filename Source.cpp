#include <iostream>
#include <string>
using namespace std;

class Reservoir {
private:
     string name;
     string type;
     double width;
     double length;
     double maxDepth;

public:
    Reservoir() : width(0.0), length(0.0), maxDepth(0.0) {}

    Reservoir(const string& n, const string& t, double w, double l, double d)
        : name(n), type(t), width(w), length(l), maxDepth(d) {}

    ~Reservoir() {}

    Reservoir(const Reservoir& other)
        : name(other.name), type(other.type), width(other.width), length(other.length), maxDepth(other.maxDepth) {}

    double calculateVolume() const {
        return width * length * maxDepth;
    }

    double calculateSurfaceArea() const {
        return width * length;
    }

    bool sameType(const Reservoir& other) const {
        return type == other.type;
    }

    bool operator<(const Reservoir& other) const {
        if (type == other.type) {
            return calculateSurfaceArea() < other.calculateSurfaceArea();
        }
        else {
            return type < other.type;
        }
    }

    Reservoir& operator=(const Reservoir& other) {
        if (this != &other) {
            name = other.name;
            type = other.type;
            width = other.width;
            length = other.length;
            maxDepth = other.maxDepth;
        }
        return *this;
    }

    void displayInfo() const {
        cout << "Name: " << name << ", Type: " << type << ", Width: " << width << ", Length: " << length << ", Max Depth: " << maxDepth << endl;
    }

    string getName() const {
        return name;
    }
};


class ReservoirManager {
private:
    Reservoir* reservoirArray;
    int size;
    int capacity;

public:
    ReservoirManager() : reservoirArray(nullptr), size(0), capacity(0) {}

    explicit ReservoirManager(int initialCapacity) : reservoirArray(nullptr), size(0), capacity(initialCapacity) {
        if (capacity > 0) {
            reservoirArray = new Reservoir[capacity];
        }
    }

    ~ReservoirManager() {
        delete[] reservoirArray;
    }

    void addReservoir(const Reservoir& reservoir) {
        if (!reservoirArray) {
            reservoirArray = new Reservoir[1];
            capacity = 1;
        }
        else if (size < capacity) {
            reservoirArray[size] = reservoir;
            size++;
        }
        else {
            capacity *= 2;
            Reservoir* newReservoirArray = new Reservoir[capacity];

            for (int i = 0; i < size; i++) {
                newReservoirArray[i] = reservoirArray[i];
            }

            newReservoirArray[size] = reservoir;
            size++;

            delete[] reservoirArray;

            reservoirArray = newReservoirArray;
        }
    }

    void removeReservoir(int index) {
        if (index >= 0 && index < size) {
            for (int i = index; i < size - 1; i++) {
                reservoirArray[i] = reservoirArray[i + 1];
            }
            size--;

            if (size < capacity / 2) {
                capacity /= 2;
                Reservoir* newReservoirArray = new Reservoir[capacity];

                for (int i = 0; i < size; i++) {
                    newReservoirArray[i] = reservoirArray[i];
                }

                delete[] reservoirArray;

                reservoirArray = newReservoirArray;
            }
        }
    }

    void displayAllReservoirs() const {
        for (int i = 0; i < size; i++) {
            cout << "[" << i << "] - ";
            reservoirArray[i].displayInfo();
        }
    }

    Reservoir& operator[](int index) {
        if (index >= 0 && index < size) {
            return reservoirArray[index];
        }
        else {
            return reservoirArray[0];
        }
    }

    int getSize() const {
        return size;
    }
};

    int main() {
        int in_capacity = 4;
        ReservoirManager manager(in_capacity);
        manager.addReservoir(Reservoir("Lake One", "lake", 100, 200, 10));
        manager.addReservoir(Reservoir("Pond Two", "pond", 50, 50, 5));
        manager.addReservoir(Reservoir("Sea Three","sea", 150, 300, 15));
        manager.addReservoir(Reservoir("Sea Four", "sea", 120, 250, 20));

        manager.displayAllReservoirs();

        manager.removeReservoir(0);
        std::cout << "\nAfter removing object with index [0]:\n";
        manager.displayAllReservoirs();

        manager.addReservoir(Reservoir("Lake One", "lake", 100, 200, 10));
        std::cout << "\nAfter adding object:\n";
        manager.displayAllReservoirs();

        for (size_t i = 0; i < manager.getSize(); i++)
        {
            Reservoir& currentReservoir = manager[i];
            cout << currentReservoir.getName() << ":" << endl;
            cout << "Volume: " << currentReservoir.calculateVolume() << endl;
            cout << "Surface Area: " << currentReservoir.calculateSurfaceArea() << endl;
            cout << endl;
        }
        return 0;
    }