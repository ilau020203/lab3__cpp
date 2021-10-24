#pragma once
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
static std::mutex cout_mutex;

class Barber
{
	bool busyness;
public:
	Barber(int id) :busyness(false) {
	}
	Barber(const Barber& barber) : busyness(false){}

	bool getBusyness() {
		return busyness;
	}

	
	void haircut(std::string name,int _id) {
		busyness = true;
		//cout_mutex.lock();
		std::cout << "Barber " << _id << " start haircut " << name << std::endl;
		//cout_mutex.unlock();
		std::this_thread::sleep_for(std::chrono::seconds(5));
		//cout_mutex.lock();
		std::cout << "Barber " << _id << "finish haircut " << name << std::endl;
		//cout_mutex.unlock();
		busyness = false;
	}
};

