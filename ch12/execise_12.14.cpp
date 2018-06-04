#include<string>
#include<iostream>
#include<memory>

using namespace std;

struct destination
{
    destination() : ip("0.0.0.0"), port(0) {}
    destination(string _ip, int _port) : ip(_ip), port(_port) { }

    string ip;
    int port;
};

struct connection
{
    destination dest;

    ~connection(){
        cout << "connection destroy." << endl;
    }
};

connection connect(destination* pDest)
{
    connection ret;
    if(pDest)
        ret.dest = *pDest;
    cout << "connection connected." << endl;
    return ret;
}

void disconnect(connection)
{
    cout << "connection disconnected." << endl;
}

void f1(destination &d)
{
    connection c = connect(&d);

    // DoSomething
    cout << "connecting 1." << endl;
    throw runtime_error("xxx");
    cout << "connecting 2." << endl;

    disconnect(c);
}

void end_connection(connection *p) { if(p) disconnect(*p); }

void f2(destination &d)
{
    connection c = connect(&d);
    // shared_ptr<connection> p(&c, end_connection);
    shared_ptr<connection> p(&c, [](connection *p) { if(p) disconnect(*p); });

    // DoSomething
    cout << "connecting 1." << endl;
    throw runtime_error("yyy");
    cout << "connecting 2." << endl;
}

void f3(destination &d)
{
    connection c = connect(&d);
    unique_ptr<connection, decltype(end_connection) *> p(&c, end_connection);

    // DoSomething
    cout << "connecting 1." << endl;
    throw runtime_error("yyy");
    cout << "connecting 2." << endl;
}

int main(){
    destination d;
    try
    {
        f1(d);
    }
    catch(runtime_error err)
    {
        cout << "error :" << err.what() << endl;
    }

    cout << "-------" << endl;

    try
    {
        f2(d);
    }
    catch (runtime_error err)
    {
        cout << "error :" << err.what() << endl;
    }

    cout << "-------" << endl;

    try
    {
        f3(d);
    }
    catch (runtime_error err)
    {
        cout << "error :" << err.what() << endl;
    }
}