#pragma once
#include "ISubject.h"
#include <mutex>
#include "Element.h"
#include <vector>
#include <list>
#include <iostream>
//#include <condition_variable>

class Warehouse : public ISubject {
private:
	static std::mutex s_mutex;
	std::vector<Element*> m_elements;
	std::list<IObserver*> m_observers;

	std::condition_variable m_cv;
	std::string m_msg;

	bool m_is_finished = false;

	Warehouse() {}
	~Warehouse() {
	}

public:

	Warehouse(const Warehouse&) = delete;
	Warehouse& operator=(const Warehouse&) = delete;

	static Warehouse& GetInstance() {
		static Warehouse s_instance;
		return s_instance;
	}

	void Attach(IObserver* observer) override {
		std::lock_guard<std::mutex> lock(s_mutex);
		m_observers.push_back(observer);
	}

	void Detach(IObserver* observer) override {
		std::lock_guard<std::mutex> lock(s_mutex);
		m_observers.remove(observer);
	}

	void Notify() override {
		std::lock_guard<std::mutex> lock(s_mutex);
		std::list<IObserver*>::iterator pierwszy = m_observers.begin();
		std::list<IObserver*>::iterator drugi = std::next(pierwszy);
		std::rotate(m_observers.begin(), drugi, m_observers.end());
		for (IObserver* obs : m_observers) {
			obs->Update(m_msg);
		}
	}

	void Add(Element* e) {
		{
			std::unique_lock<std::mutex> lock(s_mutex);

			std::string id = std::to_string(e->getID());
			m_elements.emplace_back(std::move(e));

			std::cout << "Dodano towar do magazynu (ID: " << id << ")\n";
			m_msg = "Nowy towar (ID: " + id + ")";

		}
		Notify();
	}

	void setMessage(const std::string& msg) {
		m_msg = msg;
	}

	Element* getAndRemove(int pos) {
		//std::unique_lock<std::mutex> lock(s_mutex);
		//m_cv.wait(lock, [this] { return !m_elements.empty() || m_is_finished;  });

		Element* return_val = nullptr;

		if (m_elements.empty()) {
			return return_val;
		}

		if (pos == -1) {
			return_val = m_elements.back();
			m_elements.pop_back();
		}
		else if (pos > 0) {
			for (auto it = m_elements.begin(); it != m_elements.end(); ++it) {
				if ((*it)->getID() == pos) {
					return_val = *it;
					m_elements.erase(it);
					break;
				}
			}
		}

		return return_val;
	}

	void writeList() {
		for (const auto& item : m_elements) {
			std::cout << item->getID() << std::endl;
		}
	}

	static std::mutex& getMutex() {
		return s_mutex;
	}

	std::condition_variable& get_cv() {
		return m_cv;
	}

	void setIsFinished(bool value) {
		m_is_finished = value;
		m_cv.notify_all();
	}

	bool getIsFinished() {
		return m_is_finished;
	}
};

std::mutex Warehouse::s_mutex;