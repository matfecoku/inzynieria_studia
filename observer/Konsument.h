#pragma once
#include "IObserver.h"
#include "Warehouse.h"
#include <mutex>
#include <iostream>

class Konsument : public IObserver/*, public std::enable_shared_from_this<Konsument>*/ {
private:
	int m_id;
	int m_ilosc_konsumpcji;
public:
	Konsument(int id, int ilosc) : m_id(id), m_ilosc_konsumpcji(ilosc) {}

	~Konsument() {
		Warehouse::GetInstance().Detach(this);
	}

	void consume() {
		Warehouse& magazyn = Warehouse::GetInstance();
		magazyn.Attach(this);

		{
			std::lock_guard<std::mutex> lock(magazyn.getMutex());
			std::cout << "Konsument " << m_id << " czeka na produkty.\n";
		}

		while (!magazyn.getIsFinished()) {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			/*std::unique_ptr<Element> e = magazyn.getAndRemove(-1);
			if (e == nullptr) continue;
			std::lock_guard<std::mutex> lock(magazyn.getMutex());
			std::cout << "Konsument " << m_id << " usunal " << e->getID() << "\n";*/
		}

		{
			std::lock_guard<std::mutex> lock(magazyn.getMutex());
			std::cout << "Konsument " << m_id << " zakonczyl dzialanie.\n";
		}

	}

	void Update(const std::string& msg_from_subject) override {
		//std::lock_guard<std::mutex> lock(Warehouse::getMutex());
		std::cout << "Konsument " << m_id << " otrzymal powiadomienie: " << msg_from_subject << "\n";
		Warehouse& magazyn = Warehouse::GetInstance();
		Element* e = magazyn.getAndRemove(-1);
		if (e != nullptr) {
			//std::lock_guard<std::mutex> lock(magazyn.getMutex());
			std::cout << "Konsument " << m_id << " usunal " << e->getID() << "\n";
			delete e;
		}
		//Warehouse& magazyn = Warehouse::GetInstance();
		//magazyn.get_cv().notify_one();
	}
};