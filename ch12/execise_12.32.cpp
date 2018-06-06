#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <string>
#include <memory>
#include <sstream>
#include <fstream>

#include "example.h"

using namespace std;

class QueryResult;
class TextQuery
{
  public:
    using line_no = StrBlob::size_type;
    TextQuery(ifstream &);
    QueryResult query(const string &) const;

  private:
    shared_ptr<StrBlob> file;
    map<string, shared_ptr<set<line_no>>> wm;
};

TextQuery::TextQuery(ifstream &is) : file(new StrBlob)
{
    string text;
    while (getline(is, text))
    {
        file->push_back(text);
        int n = file->size() - 1;
        istringstream line(text);
        string word;
        while (line >> word)
        {
            auto &lines = wm[word];
            if (!lines)
                lines.reset(new set<line_no>);
            lines->insert(n);
        }
    }
}

class QueryResult
{
    friend ostream &print(ostream &, const QueryResult &);

  public:
    using line_no = StrBlob::size_type;
    using ResultIter = set<line_no>::iterator;

    QueryResult(string s, shared_ptr<set<line_no>> p, shared_ptr<StrBlob> f) : sought(s), lines(p), file(f) {}

    ResultIter begin() { return lines->begin(); }
    ResultIter end() { return lines->end(); }
    shared_ptr<StrBlob> get_file() { return file; }

  private:
    string sought;
    shared_ptr<set<line_no>> lines;
    shared_ptr<StrBlob> file;
};

void runQueries(ifstream &infile)
{
    TextQuery tq(infile);
    while (true)
    {
        cout << "enter word to look for, or q to quit: ";
        string s;
        if (!(cin >> s) || s == "q")
            break;
        print(cout, tq.query(s)) << endl;
    }
}

QueryResult TextQuery::query(const string &sought) const
{
    static shared_ptr<set<line_no>> nodata(new set<line_no>);
    auto loc = wm.find(sought);
    if (loc == wm.end())
        return QueryResult(sought, nodata, file);
    else
        return QueryResult(sought, loc->second, file);
}

ostream &print(ostream &os, const QueryResult &qr)
{
    os << qr.sought << " occurs " << qr.lines->size() << " times" << endl;
    for (auto num : *qr.lines)
        os << "\t(line " << num + 1 << ")" << (ConstStrBlobPtr(*qr.file, num)).deref() << endl;
    return os;
}

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        cout << "usage: ./program file" << endl;
        return 0;
    }
    ifstream infile(argv[1]);
    runQueries(infile);
}