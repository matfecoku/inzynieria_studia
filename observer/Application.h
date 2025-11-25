#pragma once
#include <vector>
#include <thread>
#include "Konsument.h"
#include "Producent.h"

//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>
//#include <iostream>

class Application {
private:
	int liczba_producentow = 2;
	int liczba_konsumentow = 2;
	int ilosc_produkcji = 20;
	int ilosc_konsumpcji = 20;

public:
	void run() {
		//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		//_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
		//_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);

		//_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
		//_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);
		std::vector<std::thread> producenci_th;
		std::vector<std::thread> konsumenci_th;

		for (int i = 0; i < liczba_konsumentow; ++i) {
			//std::shared_ptr<Konsument> k = std::make_shared<Konsument>(i + 1, ilosc_konsumpcji);
			Konsument k = Konsument(i + 1, ilosc_konsumpcji);
			konsumenci_th.emplace_back(&Konsument::consume, k);
		}

		std::this_thread::sleep_for(std::chrono::seconds(2));

		for (int i = 0; i < liczba_producentow; ++i) {
			//std::shared_ptr<Producent> p = std::make_shared<Producent>(i + 1, ilosc_produkcji);
			Producent p = Producent(i + 1, ilosc_produkcji);
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