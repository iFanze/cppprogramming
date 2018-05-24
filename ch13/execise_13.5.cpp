#include <iostream>
#include <string>

using namespace std;

class HasPtr{
    public:

        // HasPtr():i(0), ps(nullptr) {}

        HasPtr(const std::string &s = std::string()):
            ps(new std::string(s)), i(0) {}

        // Solution 13.5
        HasPtr(const HasPtr &ptr): 
            ps(new std::string(*ptr.ps)), i(ptr.i) {
            cout << "HasPtr(const HasPtr &ptr)" << endl;
        }
        // Solution 13.5 end

        // Solution 13.8
        HasPtr& operator=(const HasPtr &ptr) {
            cout << "HasPtr& operator=" << endl;
            this->i = ptr.i;
            std::string *old = this->ps;
            if(!ptr.ps){
                this->ps = nullptr;
                return *this;
            }
            this->ps = new std::string(*ptr.ps);
            if(old)
                delete old;
            return *this;
        }
        // Solution 13.8 end

        // Solution 13.11
        ~HasPtr(){
            cout << "~HasPtr()" << endl;
            if (ps) 
                delete ps;
        }
        // Solution 13.11 end

      private:
        std::string *ps;
        int i;
};

int main(){
    HasPtr ptr("hello");

    HasPtr ptr2 = ptr;
    HasPtr ptr3(ptr);
    HasPtr *ptr4 = new HasPtr(ptr);

}