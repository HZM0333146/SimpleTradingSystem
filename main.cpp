#include <iostream>
#include <fstream>
#include <ctime>
#include "Product.h"
#include <iomanip>
#include <ctime>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
void useLogIn();
void inTransSelest(int nume);
void accountApplication();
void changeTheProduct(fstream &updateFile);			
void browseProducts(fstream &transactionFile);
void outputLine( ostream&, const Product & );	
void customerTransactionInformation(fstream &transactionFile);
void manager();
void timeNew();
int inNum,num;
string inName,inPass,name, pass;
string inNa;
int main(int argc, char** argv) {
while(true){	
	cout<<"1.帳號登入 2.帳號申請 3.管理者"<<endl;
	int select; 
	time_t timel(0);
	cin>>select;
		switch(select){
			case 1:
				useLogIn();
			break;
			case 2:			
				accountApplication();
			break;
			case 3:
				manager();
			break; 
		}
	}

	return 0;
}

void useLogIn(){
	fstream inOutUser( "mem.data", ios::in | ios::app | ios::binary);//使用者資料 
	int  result;
	bool f,key=false;
	if(inOutUser.is_open()){
		while(true){
			inOutUser.clear();
			inOutUser.seekg(0, ios::beg);
			cout<<"請輸入帳號:"<<endl;
			cin>>inNum;
			cout<<"請輸入密碼:"<<endl;
			cin >> inPass;
			while(inOutUser >> num >> name >> pass && !inOutUser.eof()){
				if(inNum==num){
					key=true;
					if(inPass==pass){
						inOutUser.close();
						system("cls");
						cout << "親愛的" << name << ",歡迎進入聯大資管銀行,您的帳號為:" << num << endl;
	 					inTransSelest(num);
	 					return;
					}else{
						cout << "密碼有誤\n"<<endl;
					}
					break;
				}
			}
			if(key==false){
				cout << "無此帳密"<<endl;
				return;
			}
			key=false;
		}
	}else{
		cerr << "檔案開啟失敗" << endl; 
	}
}
//年 月 日 時 分 帳號 品項 單價 數量
void inTransSelest(int nume){
	fstream inOutTrans( "trans.data", ios::in | ios::app | ios::binary );//交易資料 
	fstream inOutProds( "prods.data", ios::in | ios::out | ios::binary );//產品資料
	int re=0;
	//產品資料
	string na;
	int id,number,price,year,month,day,time,minute;
	//使用者購買輸入資料 
	string inName;
	int inId,inNumber,inPrice,inYear=2017,inMonth=6,inDay=23,inTime=8,inMinute=30;
	Product product;
	bool out=true;
	char sdate[9];
	char stime[9];
	if(inOutTrans.is_open()){
		do{
			inOutTrans.clear();
			inOutTrans.seekg(0,ios::beg);
			cout << "1. 購買 2. 清單 3. 所有清單 0.離開"<< endl;
			cout << "請輸入:";
			cin >> re;
			switch(re){
				case 0:
					inOutTrans.close();
					out=false;
					system("cls");
					return;
				break;
				case 1:
					browseProducts(inOutProds);
					cout<<"\n輸入物品代號：";
					cin>>inId;
					cout<<"輸入物品數量：";
					cin>>inNumber;
					inOutProds.seekg(0);
					while(inOutProds&&!inOutProds.eof()){	
						inOutProds.read(reinterpret_cast< char * >( &product ),sizeof( Product ));
						if ( product.getNumber() !=0 ){
							if ( product.getNumber() ==inId ){
								outputLine( cout, product );
						  		break;
							}
						}
					}
					
					inOutTrans<<inYear<<"\t"<<inMonth<<"\t"<<inDay<<"\t"<<inTime<<"\t"
					<<inMinute<<"\t"<<nume<<"\t"<<product.getFoodItems()<<"\t"<<inNumber<<"\t"<<product.getPrice()<<endl;
				break;
				case 2:
					//判斷今天的時間 
					while(inOutTrans>>year>>month>>day>>time>>minute>>id>>na>>number>>price){
						if(nume==day){
							cout << year<<"\t"<<month<<"\t"<<day<<"\t"<<time<<"\t"<<minute<<"\t"<<id<<"\t"<<na<<"\t"<<number<<"\t"<<price<< endl;	
						}	
					}
					//inOutTrans.seekg(0);
				break;
				case 3:
					//所有交易的內容 
					while(inOutTrans>>year>>month>>day>>time>>minute>>id>>na>>number>>price){
						cout << year<<"\t"<<month<<"\t"<<day<<"\t"<<time<<"\t"<<minute<<"\t"<<id<<"\t"<<na<<"\t"<<number<<"\t"<<price<<"\n";	
					}
					inOutTrans.seekg(0);
				break;
			}
					
		}while(out);
	}else{
			cout<<"關閉";
	}
}
void accountApplication(){
	fstream inOutUser( "mem.data", ios::in | ios::out | ios::binary);//使用者資料
	bool f=true;
	do{
		cout << "請輸入帳號: " << endl;
		cin >> inNum;
		while(inOutUser >> num >> name >> pass && !inOutUser.eof()){
			if(inNum==num){
				cout << "帳號已有重複"<< endl;
				break;
			}else{
				f=false;
				break;
			}
		}
		inOutUser.seekg(0);
	}while(f);
	cout << "請輸入密碼: " << endl;
	cin >> inPass;
	cout << "請輸入帳戶: " << endl;
	cin >> inName;
	inOutUser << inNum << "\t" << inName << "\t" << inPass << endl;
	cout << "輸出完成 " << endl;
}
void manager(){
	fstream inOutProds( "prods.data", ios::in | ios::out | ios::binary );//產品資料
	fstream inOutUser( "mem.data", ios::in | ios::out | ios::binary);//使用者資料
	fstream inOutTrans( "trans.data", ios::in | ios::out | ios::binary );//交易資料 
	cout<<"請輸入帳號：";
	cin>> inNum;
	cout<<"請輸入密碼：";
	cin>> inPass;
	if(inNum==0&&inPass=="0"){
		bool a=true;
		while(a){
			cout<<"1.更改產品 2.瀏覽產品 3.客戶交易資料 0.離開"<<endl;
			int numberS;
			cin>>numberS;
			switch(numberS){
				case 0:
					a=false;
					break;
				case 1:
					changeTheProduct(inOutProds);
					break;
				case 2:
					browseProducts(inOutProds);
					break;
				case 3:
					customerTransactionInformation(inOutTrans);
					break;	
				
			}
		}
	
	}
}
void changeTheProduct(fstream &updateFile){
	int accountNumber;
	cout<<"輸入品項ID：";
	cin>>accountNumber;
   updateFile.seekg( ( accountNumber - 1001 ) * sizeof( Product ) );
   Product product;
   updateFile.read( reinterpret_cast< char * >( &product ),sizeof( Product ) );
   if ( product.getNumber() != 0 ){
	outputLine( cout, product );		 
      // update record balance
     double pic;
     int qit;
     string nam;
    cout<<"請輸入品項：";
	cin>>nam;
	cout<<"請輸入價錢：";
	cin>>pic;
	cout<<"請輸入數目：";
	cin>>qit;
	product.setFoodItems(nam);
	product.setPrice(pic);
	product.setQuantity(qit); 
	updateFile.seekp( ( accountNumber - 1001 ) * sizeof( Product ) );
	updateFile.write( reinterpret_cast< const char * >( &product ), sizeof( Product ) );
   } 
   else // display error if account does not exist
      cerr << "Account #" << accountNumber 
         << " has no information." << endl;
}
		
void browseProducts(fstream &productsFile){
	productsFile.seekg(0);
	Product product;
	while(productsFile&&!productsFile.eof()){	
		productsFile.read(reinterpret_cast< char * >( &product ),sizeof( Product ));
		if ( product.getNumber() != 0 ){
	      outputLine( cout, product );
	 	}
	}
}
		
void customerTransactionInformation(fstream &transactionFile){
	//所有交易的內容 
	string na;
	int id,number,price,year,month,day,time,minute;
	transactionFile.seekg(0,ios::beg);
	while(transactionFile>>year>>month>>day>>time>>minute>>id>>na>>number>>price){
			cout << year<<"\t"<<month<<"\t"<<day<<"\t"<<time<<"\t"<<minute<<"\t"<<id<<"\t"<<na<<"\t"<<number<<"\t"<<price<<endl;
	}
	transactionFile.seekg(0);
}
void outputLine( ostream &output, const Product &record )
{
   output << left << setw( 10 ) << record.getNumber()
      << setw( 16 ) << record.getFoodItems()
      << setw( 11 ) << record.getPrice()
      << setw( 10 ) << setprecision( 2 ) << right << fixed 
      << showpoint << record.getQuantity() << endl;
}	

