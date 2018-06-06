#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////

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