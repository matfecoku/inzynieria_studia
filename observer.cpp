#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <mutex>
#include <thread>
#include <chrono>
#include <condition_variable>
#include <atomic>
#include <memory>

class Element {
private:
	int m_ID;
	int m_val1;
	std::string m_val2;

public:
	Element(int idEl, int v1, std::string v2)
		: m_ID(idEl), m_val1(v1), m_val2(v2) {
	}

	int getID() const {
		return m_ID;
	}
};

class IObserver {
public:
	virtual ~IObserver() {}
	virtual void Update(const std::string& msg_from_subject) = 0;
};

class ISubject {
public:
	virtual ~ISubject() {}
	virtual void Attach(IObserver* observer) = 0;
	virtual void Detach(IObserver* observer) = 0;
	virtual void Notify() = 0;
};

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
		}
		//Warehouse& magazyn = Warehouse::GetInstance();
		//magazyn.get_cv().notify_one();
	}
};

class Application {
private:
	int liczba_producentow = 2;
	int liczba_konsumentow = 2;
	int ilosc_produkcji = 20;
	int ilosc_konsumpcji = 20;

public:
	void run() {
		std::vector<std::thread> producenci_th;
		std::vector<std::thread> konsumenci_th;

		for (int i = 0; i < liczba_konsumentow; ++i) {
			//std::shared_ptr<Konsument> k = std::make_shared<Konsument>(i + 1, ilosc_konsumpcji);
			Konsument* k = new Konsument(i + 1, ilosc_konsumpcji);
			konsumenci_th.emplace_back(&Konsument::consume, k);
		}

		std::this_thread::sleep_for(std::chrono::seconds(2));

		for (int i = 0; i < liczba_producentow; ++i) {
			//std::shared_ptr<Producent> p = std::make_shared<Producent>(i + 1, ilosc_produkcji);
			Producent* p = new Producent(i + 1, ilosc_produkcji);
			producenci_th.emplace_back(&Producent::produce, p);
		}

		for (auto& producent : producenci_th) {
			producent.join();
		}

		for (auto& konsument : konsumenci_th) {
			konsument.join();
		}

		Warehouse& magazyn = Warehouse::GetInstance();
		magazyn.writeList();
	}
};

int main() {

	std::cout << "Poczatek aplikacji.\n\n";

	Application app;
	app.run();

	std::cout << "\nKoniec aplikacji.\n";
	return 0;
}