#include<iostream>
#include<string>
#include<conio.h>
#include<Windows.h>
#include<thread>;

using namespace std;
#define Escape 27
#define Enter 13
#define e 101
#define r 114
#define w 119
#define MIN_TANK_VOLUME 20
#define MAX_TANK_VOLUME 150


class Tank
{

	const int VOLUME;// характеристика обЪекта (обьем бака я вляется его характеристикой )
	double fuel_level;// уровень топлива отображает состояние бака 
public:
	int get_Volome()const
	{
		return VOLUME;
	}

	double get_fuel_level1()const
	{
		return fuel_level;
	}
	void fill(double amout)
	{
		if (amout < 0)return;
		fuel_level += amout;
		if (fuel_level > VOLUME)fuel_level = VOLUME;
	}
	double give_fuel(double amount)
	{
		fuel_level -= amount;
		if (fuel_level < 0)fuel_level = 0;
		return fuel_level;

	}
	Tank(int volume) :VOLUME
	(
		volume < MIN_TANK_VOLUME ? MIN_TANK_VOLUME:
		volume > MAX_TANK_VOLUME ? MAX_TANK_VOLUME:
		volume
	)
	{
		
		
		fuel_level = 0;
		cout << "Tank is ready"<<this << endl;

	  
	}
	~Tank()
	{
		cout << "Tanl is over " << this << endl;
	}
	void info()const 
	{
		cout << "volume: " << VOLUME << "literts\n";
		cout << "fuel_level: " << get_fuel_level1() << "literts\n";
	
	}

};



#define MIN_CONSUMPTION 3
#define MAX_CONSUMPTION 30

class Engine
{

	const double CONSUMPTION;
	double consumption_per_second;
	bool is_started;


public:

	double get_CONSUPRION()const
	{
		return CONSUMPTION;
	}
	double get_consumption_per_second()const
	{
		return consumption_per_second;
	}
	void start()
	{
		is_started = true;
		
	}
	void stop()
	{
		is_started = false;
	}
	bool started()
	{
		return is_started;
	}
	void set_consumption_per_second()
	{
		consumption_per_second = CONSUMPTION * 3e-5;

	}
	Engine(int consumption):CONSUMPTION
	(
		consumption<MIN_CONSUMPTION?MIN_CONSUMPTION:
		consumption > MAX_CONSUMPTION ? MAX_CONSUMPTION :
		consumption
	)
	{
		set_consumption_per_second();
		is_started = false;
		cout << "Engine is ready "<<this<<endl;
	
	}
	~Engine()
	{
		cout << "Engine is over " << this << endl;
	}
	void info()const
	{
		cout << "CONSUMPTION:\n";
		cout << CONSUMPTION<<"liters/100kl\n";
		cout << consumption_per_second << "liters sekond\n";
	}


};
#define MAX_SPEED_LOW_LIMIT 120
#define MAN_SPEED_HING_LIMIT 400
class Car 
{
	Engine engine;
	Tank tank;
	int speed;
	const int MAX_SPEED;
	bool driver_inside;
	struct
	{
		std::thread panel_thread;

	}control_threads;
public:
	Car(int max_speed, double consumption, int volume) :engine(consumption), tank(volume),
		MAX_SPEED
		(
			max_speed < MAX_SPEED_LOW_LIMIT ? MAX_SPEED_LOW_LIMIT:
			max_speed > MAN_SPEED_HING_LIMIT ? MAN_SPEED_HING_LIMIT :
			max_speed
	)
	{
		
		speed = 0;
		driver_inside = false;
		cout << "Your car is ready  "<<this << endl;
		cout<<"press enter to get in" << endl;
	}
	~Car()
	{
		cout << "car is over" << this << endl;
	}
	void contol() 
	{
		char key;
		
		do
		{
			
			key = _getch();
			
			switch (key)
			{
			 case Enter:driver_inside ? get_out() : get_in();break;

			 case  e:
				if (tank.get_fuel_level1()>0)
				{
					driver_inside ? engine.start() : engine.stop(); break;
					
				}
				else
				{
					system("CLS");
					cout << "нет бензина ";
					Sleep(2000);
				}
				
			 case r:driver_inside ? engine.stop() : engine.start(); break;
			
			 case w:
				 if (engine.started() ==true and speed<MAX_SPEED)
				 {
					 speed++;
				 }
				 
					
				 
				 
				 
				 
				 break;

				
			case Escape:
				get_out();
			}
		    if (engine.started() == true and speed < 1)
			{
				do
				{
					(tank.give_fuel(0.0003));
					Sleep(2000);
				} while (tank.get_fuel_level1() != 0);
			}
		
			
		} while (key != Escape); 
		
		
	}
	void fill_car(int amount)
	{
		tank.fill(amount);
	
	}
	
	void info()const
	{
		engine.info();
		tank.info();
		cout << "MAX speed:" << MAX_SPEED << "km/h\n";
	}
	void get_in()
	{
		driver_inside = true;
		/*panel();*/
		control_threads.panel_thread = std::thread(&Car::panel, this);
	}
	void get_out()
	{
		driver_inside = false;
		if (control_threads.panel_thread.joinable())control_threads.panel_thread.join();
		system("CLS");
		cout << "вы вышли из машины " << endl;
	}
	void panel()
	{
		while (driver_inside)
		{
			
			system("CLS");
			cout << "Speed:" << speed << "km/h\n";
			cout << "Engine is:" << (engine.started() ? " started" : "stoped") << endl;
			cout << "fuel level:" << tank.get_fuel_level1() << " liters" << endl;
			cout << "Consimption:" << engine.get_consumption_per_second() << " liters/second";
			
			Sleep(2000);
		}
		
	}
};
//#define TANK_CHECK
//#define-определить (создать макропределение "макрос")
//#define ENGINE 
void main()
{
	setlocale(LC_ALL, "Russian");

	
#if defined TANK_CHECK
setlocale(LC_ALL, "");
	Tank tank(300);
	
	int fuel;
	do
	{
		cout << "введите объем топлива "; cin >> fuel;
		tank.fill(fuel);tank.info();
	} while (fuel);
#endif // TANK_CHECK

#ifdef ENGINE 
Engine engine(10);
	engine.info();
#endif // ENGINE

	
	
	Car BMW(250, 10, 80);
	/*BMW.info();*/
	BMW.fill_car(20);
	
	BMW.contol();
	
}


