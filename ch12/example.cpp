#include "example.h"

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

// int main()
// {
//     test1();
//     // test2();
// }