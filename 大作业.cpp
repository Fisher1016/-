#include <string>
#include <stdio.h>
#include <ctime>
#include <iostream>
#include<conio.h>
using namespace std;
const int N = 10;
class Package;
class Payment;
class Customer;
class Deliveryman;
class list;
int package_count = 0;
int c = 0;
int cc = 0;
int ccc = 0;
int cccc = 0;

class Time
{
public:
	int month;
	int date;
	int hour;
	int minute;
	string name;
	int flag;

	Time(string n)
	{
		name = n;
		month = 0;
		date = 0;
		hour = 0;
		minute = 0;
		flag = 0;
	}
	void set()
	{
		int a, b, c, d;
		cout << "Please enter the " << name << " (month date hour minnute)" << endl;

		cin >> a >> b >> c >> d; // 此处按照顺序输入 月 日 小时 分钟
		month = a;
		date = b;
		hour = c;
		minute = d;
		cout << endl;
	}
	void display()
	{
		if (month != 0)
			cout << "The " << name << " is " << month << "/" << date << " " << hour << ":" << minute << endl
			<< endl;
		else
		{
			cout << "No " << name << " information available!" << endl
				<< endl;
		}
	}
};

class Package
{
public:
	friend class Payment;
	friend class List;
	Time fetchtime{ "fetchtime" }; //用户输入（上门取件）

	string getplace;         //
	Time gettime{ "gettime" }; //实际取到寄件（系统记录 0->1)

	Time deliverytime{ "deliverytime" }; //开始寄出（仓库端）

	Time taketime{ "taketime" }; //实际收货人得到寄件 1->0

	Time paytime{ "paytime" };
	int paytype;
	string takeplace;

	//     time_t time_recv_call;         // 接到订单时间
	//     time_t time_to_pickup;         // 预约收取时间
	//     time_t time_of_pickup;         // 实际收取时间
	//     time_t time_arrived_warehouse; //进入仓库时间
	//     time_t time_go_out;            //离开仓库时间
	//     time_t real_delivery_time;     //实际送达时间

	// takedistance//函数

	double weight; //用户输入

	double ware;     //金额，由函数得出
	int state;       //(-2，-1，0，1，2)表示准备提货、提货、到达仓库、发货、已发货
	string curplace; //当前所在位置
	int speed;       //(-1,0,1)(三小时/当天/过夜）用户确定
	int distance;    //距离
	int cancel;
	int flag;        //标记包裹是否存在；

	Package()
	{
		cancel = 0;
		flag = 0;
	}

	// printsign（）
	// printpayment（）
	// taketime（）
	// cancel（）//用户取消 包删除
	// enum livesize{}
	// enum liveweight{}

	void set_curplace()
	{
		fflush(stdin);
		cout << "Please enter the current place." << endl;
		getline(cin, curplace);
		cout << "Successfully set current place!" << endl
			<< endl;
	}
	void display_curplace()
	{
		cout << "The package is currently at " << curplace << "." << endl
			<< endl;
	}

	void set_paytype()
	{
		cout << "Please enter the paytype.(-1: individual shipments; 1:monthly invoices)" << endl;
		cin >> paytype;
		cout << "Successfully set paytype!" << endl
			<< endl;
	}

	void display_paytype()
	{
		switch (paytype)
		{
		case -1:
			cout << "The paytype is individual shipments. " << endl
				<< endl;
			break;

		case 1:
			cout << "The paytype is monthly invoices. " << endl
				<< endl;
			break;

		default:
			cout << "No paytype information available." << endl
				<< endl;
			break;
		}
	}

	void set_ware()
	{
		double w;
		distance = (getplace.length() + takeplace.length()) * 10;

		cout << "Please enter the weight." << endl;
		cin >> w;
		weight = w;
		ware = weight * 10 * distance;
		cout << endl;
	};

	void display_ware()
	{
		cout << "The price is " << ware << "." << endl
			<< endl;
	}

	void set_getplace()
	{
		fflush(stdin);
		cout << "Please enter the getplace." << endl;
		getline(cin, getplace);
		cout << "Successfully set getplace!" << endl
			<< endl;
	}

	void display_getplace()
	{
		cout << "The getplace is " << getplace << "." << endl
			<< endl;
	}
	void set_takeplace()
	{
		fflush(stdin);
		cout << "Please enter the takeplace." << endl;
		getline(cin, takeplace);
		cout << "Successfully set takeplace!" << endl
			<< endl;
	}

	void display_takeplace()
	{
		cout << "The destination is " << takeplace << "." << endl
			<< endl;
	}

	void set_state()
	{
		int s;

		cout << "Please enter the state (-2:ready to pick up; -1:picked up; 0:arrived at warehouse; 1:out for delivery 2:delivered)"
			<< endl;
		cin >> s;
		state = s;
		cout << "Successfully set status!" << endl
			<< endl;
	}

	void display_state()
	{
		switch (state)
		{
		case -2:
			cout << "The package is ready to pick up." << endl
				<< endl;
			break;
		case -1:
			cout << "The package is picked up." << endl
				<< endl;
			break;
		case 0:
			cout << "The package arrived at warehouse." << endl
				<< endl;
			break;
		case 1:
			cout << "The package is out for delivery." << endl
				<< endl;
			break;
		case 2:
			cout << "The package is delivered." << endl
				<< endl;
			break;

		default:
			cout << "No status information available." << endl
				<< endl;
			break;
		}
	}

	void set_speed()
	{
		int temp;
		cout << "Please enter the service speed (-1:in 3 hours; 0:today; 1:overnight)" << endl;
		cin >> temp;
		speed = temp;
		cout << "Successfully set speed!" << endl
			<< endl;
	}

	void display_speed()
	{
		switch (speed)
		{
		case -1:
			cout << "The service speed request is: in 3 hours." << endl
				<< endl;

			break;
		case 0:
			cout << "The service speed request is: today." << endl
				<< endl;
			break;
		case 1:
			cout << "The service speed request is: overnight." << endl
				<< endl;
			break;
		default:
			cout << "No service speed information available." << endl
				<< endl;
			break;
		}
	}

	void set()
	{
		fetchtime.set();
		gettime.set();

		set_getplace();
		set_curplace(); 
		curplace = getplace;
		set_takeplace();
		set_speed();
		set_paytype();

		set_ware();

		set_state();
		
		flag = 1;
	}

	void print_information()
	{
		system("clear");
		fetchtime.display();
		gettime.display();
		display_getplace();
		display_curplace();
		display_takeplace();
		display_speed();
		display_paytype();
		display_ware();
		display_state();
		paytime.display();
		taketime.display();
	}

	void display_payment()
	{
		display_paytype();
		paytime.display();
		display_ware();
	}

	void cancel_package()
	{
		cancel = 1;
		flag = 0;
		cout << "The package has been cancelled" << endl;
	}
};

class Customer
{
public:
	string company;
	string linkman;
	string telephone;
	string adress;
	string name;
	int flag;

	Customer() {
		flag = 0;
	}

	void set_name()
	{
		string nm;

		cout << "Please enter your name" << endl
			<< endl;
		getline(cin, nm); //此处输入用户名称

		name = nm;

		cout << "Successfully set name!" << endl
			<< endl;
	}

	void set_company()
	{
		string cpy;

		cout << "Please enter your company name ( if you are individual user, please enter 1 )" << endl
			<< endl;
		getline(cin, cpy); //此处输入公司名称

		company = cpy;

		cout << "Successfully set company!" << endl
			<< endl;
	}

	void set_linkman()
	{
		string lkm;

		cout << "Please enter the linkman's name" << endl
			<< endl;
		getline(cin, lkm); //此处输入联系人名称

		linkman = lkm;

		cout << "Successfully set linkman!" << endl
			<< endl;
	}

	void set_telephone()
	{
		string tlp;

		cout << "Please enter your telephone number" << endl
			<< endl;
		getline(cin, tlp); //此处输入联系人电话

		telephone = tlp;

		cout << "Successfully set telephone!" << endl
			<< endl;
	}

	void set_adress()
	{
		string ads;

		cout << "Please enter the your shipping address" << endl
			<< endl;
		getline(cin, ads); //此处输入地址

		adress = ads;

		cout << "Successfully set adress!" << endl
			<< endl;
	}

	void set()
	{
		set_name();
		set_company();
		set_linkman();
		set_telephone();
		set_adress();

		cout << "Successfully set all customer messages!" << endl
			<< endl;
		flag = 1;
	}

	void display_company()
	{
		if (company == "1")
		{
			cout << "The " << name << " is a individual customer" << endl
				<< endl;
		}
		else
		{
			cout << "company:\t" << company << endl
				<< endl;
		}
	}

	void display_linkman()
	{
		cout << "linkman:\t" << linkman << endl
			<< endl;
	}

	void display_telephone()
	{
		cout << "telephone:\t" << telephone << endl
			<< endl;
	}

	void display_adress()
	{
		cout << "adress:\t" << adress << endl
			<< endl;
	}

	void display()
	{
		cout << "The " << name << "'s all messages:"
			<< "\ncompany:\t" << company
			<< "\nlinkman:\t" << linkman
			<< "\ntelephone:\t" << telephone
			<< "\nadress:\t" << adress << endl
			<< endl;
	}
};

class Deliveryman
{
public:
	string deliveryman_phone;
	string deliveryman_name;
	string dname;
	string phone;
	int flag;
	Deliveryman() {
		flag = 0;
	}
	void set()
	{

		cout << "Please enter the diliveryman_name"
			<< endl;
		getline(cin, dname); //此处输入联系人名称
		deliveryman_name = dname;

		cout << "Please enter the " << dname << "'s telephone number" << endl
			<< endl;
		getline(cin, phone); //此处输入联系人电话
		deliveryman_phone = phone;

		cout << "Successfully set diliveryman!" << endl
			<< endl;
		flag = 1;
	}
	void display()
	{
		cout << "deliveryman:\t" << dname
			<< "\nphone:\t" << phone
			<< endl;
	}
};	

class List
{
public:
	int paytype;
	double weightsum = 0;
	int numbersum = 0;
	double waresum = 0;
	double paidsum = 0;
	double paid = 0;
	double debtsum = 0;
	string name;

	void sum(Package a)
	{
		paytype = a.paytype;
		weightsum = weightsum + a.weight;
		numbersum = numbersum + 1;
		if (paytype == -1)
		{
			paid = a.ware;
		}
		else if (paytype == 1)
		{
			paid = 0;
		}
		waresum = waresum + a.ware;
		paidsum = paidsum + paid;
		debtsum = waresum - paidsum;
	}

	void display_paytype()
	{
		cout << "paytype:\t" << paytype << endl
			<< endl;
	}

	void display_weightsum()
	{
		cout << "weightsum:\t" << weightsum << endl
			<< endl;
	}

	void display_numbersum()
	{
		cout << "numbersum:\t" << numbersum << endl
			<< endl;
	}

	void display_waresum()
	{
		cout << "waresum:\t" << waresum << endl
			<< endl;
	}

	void display_debtsum()
	{
		cout << "debtsum:\t" << debtsum << endl
			<< endl;
	}

	void display()
	{
		cout << "The " << name << "'s list:"
			<< "\npaytype:\t" << paytype
			<< "\nweightsum:\t" << weightsum
			<< "\nnumbersum:\t" << numbersum
			<< "\nwaresum:\t" << waresum
			<< "\ndebtsum:\t" << debtsum << endl
			<< endl;
	}
};

//Package package[N];
//Customer customer[N];
//Deliveryman deliveryman[N];
Customer customer[10];
Package package[100];
Deliveryman deliveryman[10];
List list[10];

int login();
void register_customer();
void register_deliveryman();
void modify_package();
void package_manage();
void modify_customer(int cnum);
void customer_manage();
void dilivery_manage();
void account_administrator();
void account_deliveryman();
void account_company();
void account_person();
//void search_package(Time t);

/*void search_package(Time t) {
	int i;
	for (i = 0; i < 100; i++) {
		if (package[i].taketime.month == t.month && package[i].taketime.date == t.date && t.date) 
			switch(t.flag){
			case 1:
				if (package[i].taketime.hour <= 12) {
					package[i].print_information();
				}break;
			case 2:
				if (package[i].taketime.hour <= 12) {
					package[i].print_information();
				}break;
			case 0:
				package[i].print_information();
			}
			
		}
	}
	*/
void register_customer() {
	int cnum = 0;
	while (customer[cnum].flag == 1) {
		++cnum;
	}
	customer[cnum].set();
	cout << "Successful!Your number is :" << cnum << endl;
}

void register_deliveryman(){
	int dnum = 0;
	while (deliveryman[dnum].flag == 1) {
		++dnum;
	}
	deliveryman[dnum].set();
	cout << "Successful!Your number is :" << dnum << endl;
}

/*int modify(Package& a, int mo)
{
	switch (mo)
	{
	case 1:
		a.fetchtime.set();
	case 2:
		a.gettime.set();
	case 3:
		a.set_getplace();
	case 4:
		a.set_curplace();
	case 5:
		a.set_takeplace();
	case 6:
		a.set_speed();
	case 7:
		a.set_state();
	default:
		break;
	}

	return 1;
}
*/
int login()
{
	int account, state = 0;
	cout << "login_ID" << endl; //administrator account 1-digit dilivery
	// account 3-digit company account 5-digit personal account 7-digit
	cin >> account;
	if (account > 0 && account <= 9)
	{
		state = 1;
	}
	else if (account >= 100 && account <= 999)
	{
		state = 3;
	}
	else if (account >= 10000 && account <= 99999)
	{
		state = 5;
	}
	else if (account >= 1000000 && account <= 9999999)
	{
		state = 7;
	}
	else if (account == 0)
	{
		state = 0;
	}
	return state;
}

void modify_package()
{
	int pnum;
	int mo;
	while (cccc == 0)
	{
		pnum = 0;
		cout << "Enter the package number" << endl;
		cin >> pnum;
		cout << "1_fetchtime\n";
		cout << "2_gettime\n";
		cout << "3_getplace\n";
		cout << "4_curplace\n";
		cout << "5_takeplace\n";
		cout << "6_speed\n";
		cout << "7_state\n";
		cout << "9_Back To Previous" << endl;
		cout << "0_Back To Mainmenu" << endl;
		mo = 0;
		cin >> mo;
		switch (mo)
		{
		case 1:
			package[pnum].fetchtime.set();
			cout << "Successfully modified!";
			break;
		case 2:
			package[pnum].gettime.set();
			cout << "Successfully modified!";
			break;
		case 3:
			package[pnum].set_getplace();
			cout << "Successfully modified!";
			break;
		case 4:
			package[pnum].set_curplace();
			cout << "Successfully modified!";
			break;
		case 5:
			package[pnum].set_takeplace();
			cout << "Successfully modified!";
			break;
		case 6:
			package[pnum].set_speed();
			cout << "Successfully modified!";
			break;
		case 7:
			package[pnum].set_state();
			cout << "Successfully modified!";
			break;
		case 9:
			cccc = 1;
			ccc = 0;
			break;
		case 0:
			cccc = 1;
			ccc = 1;
			cc = 0;
			break;
		default:
			cout << "order error, press any key to return" << endl;
			_kbhit();
			break;
		}
	}
	cccc = 0;
}

void modify_customer(int cnum)
{
	while (cccc == 0)
	{
		cout << "1_company" << endl;
		cout << "2_linkman" << endl;
		cout << "3_telephone" << endl;
		cout << "4_adress" << endl;
		cout << "5_name" << endl;
		cout << "9_Back To Previous" << endl;
		cout << "0_Back To Mainmenu" << endl;
		int mo = 0;
		cin >> mo;
		switch (mo)
		{
		case 1:
			customer[cnum].set_company();
			break;
		case 2:
			customer[cnum].set_linkman();
			break;
		case 3:
			customer[cnum].set_telephone();
			break;
		case 4:
			customer[cnum].set_adress();
			break;
		case 5:
			customer[cnum].set_name();
			break;
		case 9:
			cccc = 1;
			ccc = 0;
			break;
		case 0:
			cccc = 1;
			ccc = 1;
			cc = 0;
			break;
		default:
			cout << "order error, press any key to return" << endl;
			_kbhit();
			break;
		}
	}
	cccc = 0;
}

void package_manage()

{ //包裹管理系统
	int p;
	while (ccc == 0)
	{
		cout << "1_register package information" << endl;
		cout << "2_query package information" << endl;
		cout << "3_modify package information" << endl;
		cout << "4_modify package status" << endl;
		cout << "9_Back To Previous" << endl;
		cout << "0_Back To Mainmenu" << endl;
		p = 0;
		cin >> p;
		switch (p)
		{
		case 1:
			//登记包裹信息
		{
			cout << "Enter the customer number" << endl;
			int cnum,pnum;
			cin >> cnum;
			pnum = cnum * 10;
			int i=0;
			while (package[pnum+i].flag == 1) {
				++i;
			}
			pnum = pnum + i;             //定位到包裹的位置
			package[pnum].set();
			list[cnum].sum(package[pnum]);
		}
		break;
		case 2: //查询包裹信息
		{
			cout << "Enter the package number" << endl;
			int pnum;            //通过订单号查询
			cin >> pnum;
			package[pnum].print_information();
		}
		break;
		case 3: //修改包裹信息
			modify_package();
			break;
		case 4:
			cout << "Enter the package number" << endl;
			int dcnum2;
			cin >> dcnum2;
			package[dcnum2].set_state();
			break;
		case 9:
		{
			ccc = 1;
			cc = 0;
		}
		break;
		case 0:
		{
			ccc = 1;
			cc = 0;
		}
		break;
		default:
		{
			cout << "order error, press any key to return" << endl;
			_kbhit();
		}
		break;
		}
	}
	ccc = 0;
}

void customer_manage()

{ //用户管理系统
	while (ccc == 0)
	{
		cout << "1_register customer information" << endl;
		cout << "2_query customer information" << endl;
		cout << "3_modify customer information" << endl;
		cout << "4_query package information" << endl;
		cout << "9_Back To Previous" << endl;
		cout << "0_Back To Mainmenu" << endl;
		int con;
		cin >> con;
		switch (con)
		{
		case 1:
			register_customer();
			break;
		case 2:
			cout << "Enter the customer number" << endl;
			int cnum2;
			cin >> cnum2;
			customer[cnum2].display();
			break;
		case 3:
			cout << "Enter the customer number" << endl;
			int cnum3;
			cin >> cnum3;
			modify_customer(cnum3);
			break;
		case 4:
			cout << "Enter the customer number" << endl;
			int cnum4;
			cin >> cnum4;
			cnum4 = 10 * cnum4;
			while (package[cnum4].flag == 1) {				
				package[cnum4].print_information();
				++cnum4;
			}
		case 9:
			ccc = 1;
			cc = 0;
			break;
		case 0:
			ccc = 1;
			cc = 0;
			break;
		default:
			cout << "order error, press any key to return" << endl;
			_kbhit();
			break;
		}
	}
	ccc = 0;
}

void dilivery_manage()
{ //快递员管理系统
	while (ccc == 0)
	{
		cout << "1_register dilivery information" << endl;
		cout << "2_query dilivery information" << endl;
		cout << "9_exit" << endl;
		int d;
		cin >> d;
		
		switch (d)
		{
		case 1:
			register_deliveryman();
			break;
		case 2:
			cout << "Enter the deliveryman number" << endl;
			int dnum2;
			cin >> dnum2;
			deliveryman[dnum2].display();
			break;
		case 9:
			ccc = 1;
			cc = 0;
			break;
		case 0:
			ccc = 1;
			cc = 0;
			break;
		default:
			cout << "order error, press any key to return" << endl;
			_kbhit();
			break;
		}
	}
	ccc = 0;
}

void account_administrator()
{
	int order;
	while (cc == 0)
	{
		cout << "1_Package" << endl;
		cout << "2_Customer" << endl;
		cout << "3_Diliveryman" << endl;
		cout << "0_Relanding" << endl;
		order = 0;
		cin >> order;
		if (order == 1)
		{
			package_manage();
		}
		else if (order == 2)
		{
			customer_manage();
		}
		else if (order == 3)
		{
			dilivery_manage();
		}
		else if (order == 0)
		{
			cc = 1;
			c = 0;
		}
		else
		{
			cout << "order error, press any key to return" << endl;
			_kbhit();
		}
	}
	cc = 0;
}

void account_deliveryman() //快递员系统
{
	int order;
	while (cc == 0)
	{
		cout << "1_query package information" << endl;
		cout << "2_modify package status" << endl;
		cout << "3_query package information in this period" << endl;
		cout << "0_Relanding" << endl;
		order = 0;
		cin >> order;

		switch (order)
		{
		case 1:
			cout << "Enter the package number" << endl;
			int dcnum1;
			cin >> dcnum1;
			package[dcnum1].print_information();
			break;
		case 2:
			cout << "Enter the package number" << endl;
			int dcnum2;
			cin >> dcnum2;
			package[dcnum2].set_state();
			break;
		case 3:
			cout << "Enter the period" << endl;


			break;
		case 0:
			cc = 1;
			c = 0;
			break;
		default:
			cout << "order error, press any key to return" << endl;
			_kbhit();
			break;
		}
	}
	cc = 0;
}

void account_company()
{
	int order;
	while (cc == 0)
	{
		cout << "Enter company number" << endl;
		int cpnum;
		cin >> cpnum;
		if (customer[cpnum].flag == 0) {
			register_customer();
		}
		cout << "1_modify account" << endl;
		cout << "2_register package information" << endl;
		cout << "3_modify package information" << endl;
		cout << "4_query package information" << endl;
		cout << "5_query order records" << endl;
		cout << "6_query monthly statement" << endl;
		cout << "7_months to be paid bill" << endl;
		cout << "8_cancel the package" << endl;
		cout << "0_relanding" << endl;
		order = 0;
		cin >> order;
		switch (order)
		{
		case 1:
			modify_customer(cpnum);
			break;
		case 2:
			int pnum2;
			pnum2 = cpnum*10;
			while (package[pnum2].flag == 1) {
				++pnum2;
			}
			package[pnum2].set();
			list[cpnum].sum(package[pnum2]);
			break;
		case 3:
			modify_package();
			break;
		case 4:
			cout << "Enter the package number" << endl;
			int pnum4;
			cin >> pnum4;
			package[pnum4].print_information();
			break;
		case 5:
			cpnum = 10 * cpnum;
			int i;
			for (i = 0; i < 10; i++) {
				if (package[cpnum].flag == 1 || package[cpnum].cancel == 1) {     //输出全部订单
					cout << "pack" << cpnum << ":";
					package[cpnum].print_information();
					++cpnum;
				}
			}
			break;
		case 6:
			list[cpnum].display();
			break;
		case 7:
			list[cpnum].display_debtsum();
			break;
		case 8:
			cout << "Enter the package number" << endl;
			while (package[cpnum].flag == 1) {
				cout << "pack" << cpnum << ":";
				package[cpnum].print_information();
				cout << endl;
				++cpnum;
			}
			int pnum8;
			cin >> pnum8;
			if (package[pnum8].state==-2) {
				package[pnum8].cancel_package();
			}
			else
				cout << "Sorry,it cannot be cancelled" << endl;
			break;
		case 0:
			cc = 1;
			c = 0;
			break;
		default:
			cout << "order error, press any key to return" << endl;
			_kbhit();
			break;
		}
	}
	cc = 0;
}

void account_person()
{
	cout << "Enter person number" << endl;
	int psnum;
	cin >> psnum;
	if (customer[psnum].flag == 0) {
		register_customer();
	}
	int order;
	while (cc == 0)
	{
		cout << "1_modify account" << endl;
		cout << "2_register package information" << endl;
		cout << "3_modify package information" << endl;
		cout << "4_query package information" << endl;
		cout << "5_querying records" << endl;
		cout << "6_modify package status" << endl;
		cout << "7_months to be paid bill" << endl;
		cout << "8_cancel the package" << endl;
		cout << "0_Relanding" << endl;
		order = 0;
		cin >> order;
		switch (order)
		{
		case 1:
			modify_customer(psnum);
			break;
		case 2:
			while (package[psnum].flag == 1) {
				++psnum;
			}
			package[psnum].set();
			list[psnum].sum(package[psnum]);
			break;
		case 3:
			modify_package();
			break;
		case 4:
			cout << "Enter the package number" << endl;
			int pnum4;
			cin >> pnum4;
			package[pnum4].print_information();
			break;
		case 5:
			psnum = 10 * psnum;
			int i;
			for (i = 0; i < 10; i++) {
				if (package[psnum].flag == 1 || package[psnum].cancel == 1) {     //输出全部订单
					cout << "pack" << psnum << ":";
					package[psnum].print_information();
					++psnum;
				}
			}
			break;
		case 6:
			for (i = 0; i < 10; i++) {
				if (package[psnum].flag == 1 ) {     //输出全部订单
					cout << "pack" << psnum << ":";
					package[psnum].print_information();
					++psnum;
				}
			}
			cout << "Enter the package number" << endl;
			int psnum6;
			cin >> psnum6;
			package[psnum6].set_state();
			break;
		case 7:
			list[psnum].display_debtsum();
			break;
		case 8:
			cout << "Enter the package number" << endl;
			while (package[psnum].flag == 1) {
				cout << "pack" << psnum << ":";
				package[psnum].print_information();
				cout << endl;
				++psnum;
			}
			int pnum;
			cin >> pnum;
			if (package[pnum].state==-2) {
				package[pnum].cancel_package();
			}
			else
				cout << "Sorry,it cannot be cancelled" << endl;
			break;
		case 0:
			cc = 1;
			c = 0;
			break;
		default:
			cout << "order error, press any key to return" << endl;
			_kbhit();
			break;
		}
	}
	cc = 0;
}

int main()
{

	while (c == 0)
	{
		int login_account;
		cout << "enter 0 to exit" << endl;
		login_account = login();

		switch (login_account)
		{
		case 1:
			account_administrator();
			break;
		case 3:
			account_deliveryman();
			break;
		case 5:
			account_company();
			break;
		case 7:
			account_person();
			break;
		case 0:
			c = 1;
			break;
		default:
			cout << "login_ID is error" << endl;
			break;
		}
		
		cout << "c=" << c << ",cc=" << cc << ",ccc=" << ccc << ",cccc=" << cccc << ",login_account =" << login_account << endl;
		login_account = 0;
	}
	c = 0;
	return 0;
}