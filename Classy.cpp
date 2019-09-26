#include <string>
#include <iostream>
#include <stdio.h>
using namespace std;

class Classy
{
  private:
    string cname;
    bool type;
    string mess;
  
  public:
    void setName(string name)
    {
      cname = name;
      return;
    }

    string getName()
    {
      return cname;
    }

    void setType(bool isInterest)
    {
      type = isInterest;
      return;
    }

    bool getType()
    {
      if (type)
        cout << "This is an interest packet";
      else
        cout << "This is a data packet";
      return type;
    }
};
