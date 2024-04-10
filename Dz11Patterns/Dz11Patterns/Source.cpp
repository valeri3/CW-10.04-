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
        cout << "Диспетчер получил от " << sender->toString() << " сообщение: " << message << endl;
    }

    void send(string message, Transport* receiver) {
        cout << "Диспетчер отправил " << receiver->toString() << " сообщение: " << message << endl;
    }
};

class Boeing : public Transport
{
public:
    Boeing(Dispatcher* dispatcher) : Transport(dispatcher) {}

    void communicate(string message) override
    {
        cout << "Самолет Boeing: " << message << endl;
        dispatcher->broadcast(message, this);
    }

    void send(string message) override {
        cout << "Самолет Boeing отправляет сообщение: " << message << endl;
        dispatcher->send(message, this);
    }

    string toString() const override
    {
        return "Самолет Boeing";
    }
};

class Airbus : public Transport
{
public:
    Airbus(Dispatcher* dispatcher) : Transport(dispatcher) {}

    void communicate(string message) override
    {
        cout << "Самолет Airbus: " << message << endl;
        dispatcher->broadcast(message, this);
    }

    void send(string message) override
    {
        cout << "Самолет Airbus отправляет сообщение: " << message << endl;
        dispatcher->send(message, this);
    }

    string toString() const override
    {
        return "Самолет Airbus";
    }
};

class Embraer : public Transport
{
public:
    Embraer(Dispatcher* dispatcher) : Transport(dispatcher) {}

    void communicate(string message) override
    {
        cout << "Самолет Embraer : " << message << endl;
        dispatcher->broadcast(message, this);
    }

    void send(string message) override
    {
        cout << "Самолет Embraer отправляет сообщение: " << message << endl;
        dispatcher->send(message, this);
    }

    string toString() const override
    {
        return "Самолет Embraer ";
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

    boeing->send("Запрос на посадку на взлетно-посадочную полосу 2");
    airbus->communicate("Требуется дозаправка перед дальним перелетом");
    embraer->send("Проверка систем готовности к полету");

    boeing->send("Изменение курса до 20 градусов");
    airbus->communicate("Меняю высоту на 3000 метров");
    embraer->send("Предупреждение о турбулентности");

    delete boeing;
    delete airbus;
    delete embraer;
}
