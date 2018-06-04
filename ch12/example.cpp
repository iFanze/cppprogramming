#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>

using namespace std;

class StrBlobPtr;

class StrBlob
{
    friend class StrBlobPtr;
    friend class ConstStrBlobPtr;

  public:
    typedef vector<string>::size_type size_type;

    StrBlob() : data(make_shared<vector<string>>()) {}
    StrBlob(std::initializer_list<string> li) : data(make_shared<vector<string>>(li)) {}

    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    void push_back(const string &t) { data->push_back(t); }

    string &front();
    string &back();
    const string &const_front() const;
    const string &const_back() const;
    void pop_back();

    StrBlobPtr begin();
    StrBlobPtr end();

  private:
    shared_ptr<vector<string>> data;
    void check(size_type i, const string &msg) const;
};

class StrBlobPtr
{
  public:
    StrBlobPtr() : curr(0) {}
    StrBlobPtr(StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}
    string& deref() const;
    StrBlobPtr &incr();

  private:
    shared_ptr<vector<string>> check(std::size_t, const std::string &) const;
    weak_ptr<vector<string>> wptr;
    size_t curr;
};

class ConstStrBlobPtr
{
  public:
    ConstStrBlobPtr() : curr(0) {}
    ConstStrBlobPtr(const StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}
    const string& deref() const;
    ConstStrBlobPtr &incr();

  private:
    shared_ptr<vector<string>> check(std::size_t, const std::string &) const;
    weak_ptr<vector<string>> wptr;
    size_t curr;
};

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

shared_ptr<vector<string>>
ConstStrBlobPtr::check(size_t i, const string &msg) const
{
    auto ret = wptr.lock();
    if (!ret)
        throw std::runtime_error("unbound ConstStrBlobPtr");
    if (i >= ret->size())
        throw std::out_of_range(msg);
    return ret;
}

const string& ConstStrBlobPtr::deref() const
{
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}

ConstStrBlobPtr &ConstStrBlobPtr::incr()
{
    check(curr, "increment past end of ConstStrBlobPtr");
    ++curr;
    return *this;
}

//////////////////////////////////////////////////////////////////////////////////////

shared_ptr<vector<string>>
StrBlobPtr::check(size_t i, const string &msg) const
{
    auto ret = wptr.lock();
    if (!ret)
        throw std::runtime_error("unbound StrBlobPtr");
    if (i >= ret->size())
        throw std::out_of_range(msg);
    return ret;
}

string& StrBlobPtr::deref() const
{
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}

StrBlobPtr &StrBlobPtr::incr()
{
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}

//////////////////////////////////////////////////////////////////////////////////////

void StrBlob::check(size_type i, const string &msg) const
{
    if (i >= data->size())
        throw out_of_range(msg);
}

string &StrBlob::front()
{
    check(0, "front on empty StrBlob");
    return data->front();
}

string &StrBlob::back()
{
    check(0, "back on empty StrBlob");
    return data->back();
}

void StrBlob::pop_back()
{
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}

const string &StrBlob::const_front() const
{
    check(0, "front on empty StrBlob");
    return data->front();
}

const string &StrBlob::const_back() const
{
    check(0, "back on empty StrBlob");
    return data->back();
}

StrBlobPtr StrBlob::begin()
{
    return StrBlobPtr(*this);
}

StrBlobPtr StrBlob::end()
{
    auto ret = StrBlobPtr(*this, data->size());
    return ret;
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

void test1()
{
    StrBlob blob;
    blob.push_back("aaaa");
    blob.push_back("bbbb");
    blob.push_back("cccc");

    for (auto it = blob.begin();; it = it.incr())
    {
        try
        {
            cout << it.deref() << endl;
        }
        catch (std::out_of_range e)
        {
            break;
        }
    }
}

void test2()
{
    StrBlob blob;
    string str;
    ifstream fs("input.txt");
    while (fs >> str)
        blob.push_back(str);
    for (auto it = blob.begin();; it = it.incr())
    {
        try
        {
            cout << it.deref() << endl;
        }
        catch (std::out_of_range e)
        {
            break;
        }
    }
}

int main()
{
    test1();
    test2();
}