// Fig. 17.10: ClientData.h
// Class ClientData definition used in Fig. 17.12-Fig. 17.15.
#ifndef CLIENTDATA_H
#define CLIENTDATA_H

#include <string>
using namespace std;

class Product 
{
public:
   // default ClientData constructor
   Product( int = 0, string = "", double = 0.0, int = 0 );

   // accessor functions for accountNumber
   void setNumber( int );
   int getNumber() const;

   // accessor functions for lastName
   void setFoodItems( string );
   string getFoodItems() const;

   // accessor functions for firstName
   void setQuantity( int );
   int getQuantity() const;

   // accessor functions for balance
   void setPrice( double );
   double getPrice() const;
private:
   int number;
   char foodItems[15];
   int quantity;
   double price;
}; // end class ClientData

#endif
