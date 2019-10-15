#include "Classy.cpp"
using namespace std;
int main()
{
  Classy fst;
  Classy snd;
  fst.setName("First one Suckers");
  snd.setName("shrtnme");
  fst.setType(true);
  snd.setType(false);
  cout << fst.getName()<<"\n";
  fst.getType();
  
  Classy * ptr = (Classy *) &snd;
  int l = sizeof(snd);
  for(int i = 0; i < l; i++)
  {
    //printf("%X %04X%c", *(ptr+i), *(pt+i), (i%16==15)?'\n':',');
  }  
  //fst = *ptr;
  
  uint8_t* data = reinterpret_cast<uint8_t*>(&snd);
  uint8_t lis[l];
  for(int i = 0; i < l; i++) 
  {
    lis[i] = *(data+i);
    printf("%02X%c", *(data+i), (i%16==15)?'\n':' ');
  }  
  ptr = reinterpret_cast<Classy*>(lis);
  cout << "\n" << ptr->getName()<<"\n";
  ptr->getType();
}
