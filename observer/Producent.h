#pragma once
#include <atomic>
#include "Warehouse.h"
#include <iostream>

class Element;

class Producent {
private:
	int m_id;
	int m_ilosc_produkcji;
	static std::atomic<int> s_ACT_ID;

public:
	Producent(int id, int ilosc) : m_id(id), m_ilosc_produkcji(ilosc) {}

	void produce() {
		Warehouse& magazyn = Warehouse::GetInstance();

		for (int i = 0; i < m_ilosc_produkcji; ++i) {

			int id = s_ACT_ID++;
			Element* temp = new Element(id, id, std::string("tu jest string"));

			{
				std::lock_guard<std::mutex> lock(magazyn.getMutex());
				std::cout << "Producent " << m_id << " dodal " << id << '\n';
			}
			magazyn.Add(temp);

			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}


		{
			std::lock_guard<std::mutex> lock(magazyn.getMutex());
			magazyn.setIsFinished(true);
			std::cout << "Producent " << m_id << " zakonczyl dzialanie.\n";
		}
	}
};

std::atomic<int> Producent::s_ACT_ID{ 1000 };