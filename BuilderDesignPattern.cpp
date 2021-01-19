#include <iostream>
#include <string>
using namespace std;

/* PC Components */
class Motherboard
{
public:
    string chipset;
};

class CPU
{
public:
    string model;
};

class Memory
{
public:
    int x_gb;
};

class Storage
{
public:
    int y_gb;
};

/* Basic Assemble */
class Assembled
{
public:
    Motherboard* motherboard;
    CPU* cpu;
    Memory* memory;
    Storage* storage;

    void specifications()
    {
        cout << "Motherboard: " << motherboard->chipset << endl;
        cout << "CPU: " << cpu->model << endl;
        cout << "Memory: " << memory->x_gb << " gigabytes" << endl;
        cout << "Storage: " << storage->y_gb << " gigabytes" << endl;
    }
};

/* Builder constructs the smaller parts */
class Builder
{
public:
    virtual Motherboard* getMotherboard() = 0;
    virtual CPU* getCPU() = 0;
    virtual Memory* getMemory() = 0;
    virtual Storage* getStorage() = 0;
};

/* Director is responsible for the whole process */
class Director
{
    Builder* builder;

public:
    void setBuilder(Builder* newBuilder)
    {
        builder = newBuilder;
    }

    Assembled* getAssembled()
    {
        Assembled* assembled = new Assembled();

        assembled->motherboard = builder->getMotherboard();
        assembled->cpu = builder->getCPU();
        assembled->memory = builder->getMemory();
        assembled->storage = builder->getStorage();

        return assembled;
    }
};

/* Concrete builder for Intel PC */
class IntelBuilder : public Builder
{
public:
    Motherboard* getMotherboard()
    {
        Motherboard* motherboard = new Motherboard();
        motherboard->chipset = "ASUS TUF GAMING B460-PRO(Wi-Fi)";
        return motherboard;
    }

    CPU* getCPU()
    {
        CPU* cpu = new CPU();
        cpu->model = "Core i5-10500 Processor";
        return cpu;
    }

    Memory* getMemory()
    {
        Memory* memory = new Memory();
        memory->x_gb = 16;
        return memory;
    }

    Storage* getStorage()
    {
        Storage* storage = new Storage();
        storage->y_gb = 1024;
        return storage;
    }
};

/* Concrete builder for AMD PC */
class AMDBuilder : public Builder
{
public:
    Motherboard* getMotherboard()
    {
        Motherboard* motherboard = new Motherboard();
        motherboard->chipset = "ASUS TUF GAMING B550M-PLUS (Wi-Fi)";
        return motherboard;
    }

    CPU* getCPU()
    {
        CPU* cpu = new CPU();
        cpu->model = "Ryzen 5 5600x";
        return cpu;
    }

    Memory* getMemory()
    {
        Memory* memory = new Memory();
        memory->x_gb = 32;
        return memory;
    }

    Storage* getStorage()
    {
        Storage* storage = new Storage();
        storage->y_gb = 2048;
        return storage;
    }
};

int main()
{
    Assembled* assembled; // Final product

    Director director; // Controls the whole process

    /* Concrete builders */
    IntelBuilder intelbuilder;
    AMDBuilder amdbuilder;

    /* Build an Intel PC */
    cout << "Intel" << endl;
    director.setBuilder(&intelbuilder); // using IntelBuilder instance
    assembled = director.getAssembled();
    assembled->specifications();

    cout << endl;

    /* Build an AMD PC */
    cout << "AMD" << endl;
    director.setBuilder(&amdbuilder); // using IntelBuilder instance
    assembled = director.getAssembled();
    assembled->specifications();

    return 0;
}
