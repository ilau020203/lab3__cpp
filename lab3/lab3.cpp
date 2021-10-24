// lab3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "Barber.h"
#include <iostream>
#include <queue>
#include <string>
#include <ctime>
#include<chrono>
#include<vector>
#include <thread>
const std::chrono::duration<double> workingHours= std::chrono::seconds(6);

void distribution(std::queue<std::string>& queueOfVisitors, std::queue<std::string>& queueOfFinish, std::vector<Barber>& barbers,std::vector<std::thread>& threads, std::chrono::system_clock::time_point start) {
    while (!queueOfVisitors.empty() || (start + workingHours > std::chrono::system_clock::now())) {
        if (!queueOfVisitors.empty()) {
            for (int i = 0; i < barbers.size(); i++) {
                if (!queueOfVisitors.empty()) {
                    if (!barbers[i].getBusyness()) {
                        queueOfFinish.push(queueOfVisitors.front());
                        
                        threads.push_back(std::thread([&](int i,Barber& barber) {
                            barber.haircut(queueOfFinish.back(), i);
                            }, i,std::ref(barbers[i])));
                        queueOfVisitors.pop();
                    }
                }
            }
        }
    }
}



int main()
{
    std::queue<std::string> queueOfFinish;
    std::queue<std::string> queueOfVisitors;
    std::vector<std::thread> threads;
    std::cout << "open barbershop" << std::endl;
    std::cout << "input count barbershop" << std::endl;
    int countBarbers;
    std::cin >> countBarbers;
    std::vector<Barber> barbers;
    for (int i = 0; i < countBarbers; i++) {
       
        barbers.push_back(Barber(i));
    }
    auto start = std::chrono::system_clock::now();
    auto distributionThread = std::thread(distribution, std::ref(queueOfVisitors),std::ref( queueOfFinish), std::ref(barbers), std::ref(threads), start);
    while (start + workingHours > std::chrono::system_clock::now()) {
        std::cout << "input visitor" << std::endl;
        std::string input;
        std::cin >> input;

        queueOfVisitors.push(input);
      /*  if (!queueOfVisitors.empty()) {
            distribution(queueOfVisitors, queueOfFinish, barbers, threads, start);
        }*/
    }

   
    for (int i =0 ; i<threads.size();i++){
        threads[i].join();
    }
    distributionThread.join();
}
