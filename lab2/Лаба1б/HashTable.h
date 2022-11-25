#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class HashTable {
private:
	int const threshold = 10;
	vector < pair < string, string>>table; // тип лексемы,  лексема
	int default_size_table = 50;
	int cnt_records = 0;
	long long h1(string str) {
		long long sum = 0;
		for (int i = 0; i < str.size(); i++) {
			sum += int(str[i]);
		}
		return sum % get_size();
	}

	long long h2(string str) {
		long long sum = 0;
		for (int i = 0; i < str.size(); i++) {
			sum += int(str[i]) + i;
		}
		return sum % get_size();
	}

	void update() {												// обновление хеш-таблицы, пересчёт всех значений хеш-функции
		vector < pair < string, string>>tmp_table;
		tmp_table = table;
		table.resize(table.size() * 2);
		table.assign(table.size(), { "", "" });
		int n = tmp_table.size();
		for (int i = 0; i < n; i++) {
			pair<string, string>data = tmp_table[i];
			add(data);
		}
	}


public:
	HashTable() {
		table.resize(default_size_table);
	};
	//~HashTable();

	void add(pair<string, string> p) {
		if (table.size() - cnt_records <= threshold) {
			update();
			add(p);
			return;
		}

		long long hash1 = h1(p.second);
		if (table[hash1].second == p.second) {
			return;
		}
		else if (table[hash1].second == "") {
			table[hash1] = p;
			cnt_records++;
			return;
		}

		long long hash2 = h2(p.second);
		if (hash2 == 0) {
			hash2 = 1;
		}

		int i = 1;
		while (true) {
			long long hash_id = (hash1 + i * hash2) % get_size();
			if (table[hash_id].second == p.second) {
				return;
			}
			else {
				if (table[hash_id].second == "") {
					table[hash_id] = p;
					cnt_records++;
					return;
				}
			}
			i++;
		}

		//		update();
		//		add(p);
	}


	int get_size()
	{
		return table.size();
	}

	pair<string, string> get_pair(int i)
	{
		return table[i];
	}

};