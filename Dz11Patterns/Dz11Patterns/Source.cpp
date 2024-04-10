#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Dispatcher;

class Transport
{
protected:
    Dispatcher* dispatcher;
public:
    Transport(Dispatcher* dispatcher) : dispatcher(dispatcher) {}

    virtual void communicate(string message) = 0;
    virtual void send(string message) = 0;
    virtual string toString() const = 0;
};

class Dispatcher
{
private:
    vector<Transport*> transports;
public:
    void registerTransport(Transport* transport)
    {
        transports.push_back(transport);
    }

    void broadcast(string message, Transport* sender)
    {
        cout << "��������� ������� �� " << sender->toString() << " ���������: " << message << endl;
    }

    void send(string message, Transport* receiver) {
        cout << "��������� �������� " << receiver->toString() << " ���������: " << message << endl;
    }
};

class Boeing : public Transport
{
public:
    Boeing(Dispatcher* dispatcher) : Transport(dispatcher) {}

    void communicate(string message) override
    {
        cout << "������� Boeing: " << message << endl;
        dispatcher->broadcast(message, this);
    }

    void send(string message) override {
        cout << "������� Boeing ���������� ���������: " << message << endl;
        dispatcher->send(message, this);
    }

    string toString() const override
    {
        return "������� Boeing";
    }
};

class Airbus : public Transport
{
public:
    Airbus(Dispatcher* dispatcher) : Transport(dispatcher) {}

    void communicate(string message) override
    {
        cout << "������� Airbus: " << message << endl;
        dispatcher->broadcast(message, this);
    }

    void send(string message) override
    {
        cout << "������� Airbus ���������� ���������: " << message << endl;
        dispatcher->send(message, this);
    }

    string toString() const override
    {
        return "������� Airbus";
    }
};

class Embraer : public Transport
{
public:
    Embraer(Dispatcher* dispatcher) : Transport(dispatcher) {}

    void communicate(string message) override
    {
        cout << "������� Embraer : " << message << endl;
        dispatcher->broadcast(message, this);
    }

    void send(string message) override
    {
        cout << "������� Embraer ���������� ���������: " << message << endl;
        dispatcher->send(message, this);
    }

    string toString() const override
    {
        return "������� Embraer ";
    }
};

void main()
{
    setlocale(LC_ALL, "Russian");

    Dispatcher* dispatcher = new Dispatcher;

    Transport* boeing = new Boeing(dispatcher);
    Transport* airbus = new Airbus(dispatcher);
    Transport* embraer = new Embraer(dispatcher);

    dispatcher->registerTransport(boeing);
    dispatcher->registerTransport(airbus);
    dispatcher->registerTransport(embraer);

    boeing->send("������ �� ������� �� �������-���������� ������ 2");
    airbus->communicate("��������� ���������� ����� ������� ���������");
    embraer->send("�������� ������ ���������� � ������");

    boeing->send("��������� ����� �� 20 ��������");
    airbus->communicate("����� ������ �� 3000 ������");
    embraer->send("�������������� � ��������������");

    delete boeing;
    delete airbus;
    delete embraer;
}
