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
	cout<<"1.�b���n�J 2.�b���ӽ� 3.�޲z��"<<endl;
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
	fstream inOutUser( "mem.data", ios::in | ios::app | ios::binary);//�ϥΪ̸�� 
	int  result;
	bool f,key=false;
	if(inOutUser.is_open()){
		while(true){
			inOutUser.clear();
			inOutUser.seekg(0, ios::beg);
			cout<<"�п�J�b��:"<<endl;
			cin>>inNum;
			cout<<"�п�J�K�X:"<<endl;
			cin >> inPass;
			while(inOutUser >> num >> name >> pass && !inOutUser.eof()){
				if(inNum==num){
					key=true;
					if(inPass==pass){
						inOutUser.close();
						system("cls");
						cout << "�˷R��" << name << ",�w��i�J�p�j��޻Ȧ�,�z���b����:" << num << endl;
	 					inTransSelest(num);
	 					return;
					}else{
						cout << "�K�X���~\n"<<endl;
					}
					break;
				}
			}
			if(key==false){
				cout << "�L���b�K"<<endl;
				return;
			}
			key=false;
		}
	}else{
		cerr << "�ɮ׶}�ҥ���" << endl; 
	}
}
//�~ �� �� �� �� �b�� �~�� ��� �ƶq
void inTransSelest(int nume){
	fstream inOutTrans( "trans.data", ios::in | ios::app | ios::binary );//������ 
	fstream inOutProds( "prods.data", ios::in | ios::out | ios::binary );//���~���
	int re=0;
	//���~���
	string na;
	int id,number,price,year,month,day,time,minute;
	//�ϥΪ��ʶR��J��� 
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
			cout << "1. �ʶR 2. �M�� 3. �Ҧ��M�� 0.���}"<< endl;
			cout << "�п�J:";
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
					cout<<"\n��J���~�N���G";
					cin>>inId;
					cout<<"��J���~�ƶq�G";
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
					//�P�_���Ѫ��ɶ� 
					while(inOutTrans>>year>>month>>day>>time>>minute>>id>>na>>number>>price){
						if(nume==day){
							cout << year<<"\t"<<month<<"\t"<<day<<"\t"<<time<<"\t"<<minute<<"\t"<<id<<"\t"<<na<<"\t"<<number<<"\t"<<price<< endl;	
						}	
					}
					//inOutTrans.seekg(0);
				break;
				case 3:
					//�Ҧ���������e 
					while(inOutTrans>>year>>month>>day>>time>>minute>>id>>na>>number>>price){
						cout << year<<"\t"<<month<<"\t"<<day<<"\t"<<time<<"\t"<<minute<<"\t"<<id<<"\t"<<na<<"\t"<<number<<"\t"<<price<<"\n";	
					}
					inOutTrans.seekg(0);
				break;
			}
					
		}while(out);
	}else{
			cout<<"����";
	}
}
void accountApplication(){
	fstream inOutUser( "mem.data", ios::in | ios::out | ios::binary);//�ϥΪ̸��
	bool f=true;
	do{
		cout << "�п�J�b��: " << endl;
		cin >> inNum;
		while(inOutUser >> num >> name >> pass && !inOutUser.eof()){
			if(inNum==num){
				cout << "�b���w������"<< endl;
				break;
			}else{
				f=false;
				break;
			}
		}
		inOutUser.seekg(0);
	}while(f);
	cout << "�п�J�K�X: " << endl;
	cin >> inPass;
	cout << "�п�J�b��: " << endl;
	cin >> inName;
	inOutUser << inNum << "\t" << inName << "\t" << inPass << endl;
	cout << "��X���� " << endl;
}
void manager(){
	fstream inOutProds( "prods.data", ios::in | ios::out | ios::binary );//���~���
	fstream inOutUser( "mem.data", ios::in | ios::out | ios::binary);//�ϥΪ̸��
	fstream inOutTrans( "trans.data", ios::in | ios::out | ios::binary );//������ 
	cout<<"�п�J�b���G";
	cin>> inNum;
	cout<<"�п�J�K�X�G";
	cin>> inPass;
	if(inNum==0&&inPass=="0"){
		bool a=true;
		while(a){
			cout<<"1.��ﲣ�~ 2.�s�����~ 3.�Ȥ������ 0.���}"<<endl;
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
	cout<<"��J�~��ID�G";
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
    cout<<"�п�J�~���G";
	cin>>nam;
	cout<<"�п�J�����G";
	cin>>pic;
	cout<<"�п�J�ƥءG";
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
	//�Ҧ���������e 
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

