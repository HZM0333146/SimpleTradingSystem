// Fig. 17.11: ClientData.cpp
// Class ClientData stores customer's credit information.
#include <string>
#include "Product.h"
using namespace std;

// default ClientData constructor
Product::Product( int numberValue, string foodItemsValue, double priceValue, int quantityValue){
   setNumber( numberValue );
   setFoodItems( foodItemsValue );
   setQuantity( quantityValue );
   setPrice( priceValue );
} 
// end ClientData constructor


int Product::getNumber() const{
   return number;
}
void Product::setNumber( int sNumberValue ){
   number = sNumberValue; 
} 


string Product::getFoodItems() const{
   return foodItems;
} 


void Product::setFoodItems( string sFoodItems ){
   
   int length = sFoodItems.size();
   length = ( length < 15 ? length : 14 );
   sFoodItems.copy( foodItems, length );
   foodItems[ length ] = '\0'; 
} 

int Product::getQuantity() const{
   return quantity;
} 

void Product::setQuantity( int sQuantityValue ){
	quantity=sQuantityValue;
} 

double Product::getPrice() const{
   return price;
} 

void Product::setPrice( double sPriceValue ){
   price = sPriceValue;
} 

