#pragma once
#include "HashTable.h"

using namespace std;

class LexicalAnalyzer {
private:
	vector<string>keywords, operations, servicies_commands;
	string all_text;

	enum TypeTokens {
		INT,
		FLOAT,
		VAR,
		KEY_WORD,
		OPERAND,
		SERVICE_OPERAND,
		FUNCTION,
		ERROR,
	};

	enum stateDKA {
		state1,
		state2,
		state3,
		state4
	};

	int idx = 0;
	int text_size = all_text.size();

public:

	LexicalAnalyzer(vector<string>kws = {}, vector<string>opers = {}, vector<string>sv = {}, string text = "") {
		this->keywords = kws;
		this->operations = opers;
		this->servicies_commands = sv;
		this->all_text = text;
		text_size = this->all_text.size();
	}

	string next_str() {
		string str = "";
		while (this->all_text[idx] != '\n' && this->all_text[idx] != ' ') {
			str += all_text[idx];
			idx++;
			if (idx == text_size) {
				break;
			}
		}
		idx++;
		return str;
	}

	int get_state_dka(string s) {
		int n = s.size();
		if (n > 2) {
			if (s[n - 1] == ')' && s[n - 2] == '(') {
				for (int i = 0; i < n - 2; i++) {
					if (!isalpha(s[i]) && !isdigit(s[i])) {
						return ERROR;
					}
				}
				return FUNCTION;
			}
		}
		int state = state1;
		if (isdigit(s[0])) {		//смотрим по первому символу число это или нет
			state = state2;
		}
		else if (isalpha(s[0])) {		//смотрим по первому символу буква это или нет
			state = state3;
		}
		else {
			state =  state4;
		}

		if (state == state2) {
			bool is_point = false;
			for (int i = 1; i < s.size(); i++) {
				if (s[i] == '.') {
					if (!is_point) {			
						is_point = true;
					}
					else {
						return ERROR;			// если точка в числе попалась 2 раза, возвращаем ошибку
					}
				}else  if (!isdigit(s[i]) && s[i] != ';') {	// если попался неизвестный символ, возвращаем ошибку
					return ERROR;
				}
			}
			if (is_point) {
				return FLOAT;					// если у нас была одна точка, возвращаем тип float
			}
			else {
				return INT;						// если точек не было возвращаем INT
			}
		}
		else if (state == state3) {
			for (int i = 1; i < s.size(); i++) {
				if (!isalpha(s[i]) && s[i] !=';') {		// если не буква и не ; вернем ошибку
					return ERROR;
				}
			}

			if (find(keywords.begin(), keywords.end(), s) != keywords.end()){
				return KEY_WORD;						// возвращаем состояние ключевого слова или переменной
			}
			else {
				return VAR;
			}
		}
		else {
			if (find(operations.begin(), operations.end(), s) != operations.end()) {
				return OPERAND;
			}
			else if (find(servicies_commands.begin(), servicies_commands.end(), s) != servicies_commands.end()) {
				return SERVICE_OPERAND;
			}
			else {
				return ERROR;
			}
		}
	}
 
	HashTable analysis() {
		HashTable ht;
		bool start_function = false;
		while (idx < text_size) {
			string tmp_str = next_str();
			pair<string, string>lexem;
			int state = get_state_dka(tmp_str);

			if (state == INT) {
				lexem.first = "INT";
			}
			else if (state == FLOAT) {
				lexem.first = "FLOAT";
			}
			else if (state == VAR) {
				lexem.first = "VAR";
			}
			else if (state == KEY_WORD) {
				lexem.first = "KEY_WORD";
			}
			else if (state == OPERAND) {
				lexem.first = "OPERAND";
			}
			else if (state == SERVICE_OPERAND) {
				lexem.first = "SERVICE_OPERAND";
			}
			else if (state == FUNCTION) {
				lexem.first = "FUNCTION";
			}
			else {
				lexem.first = "ERROR";
			}

			lexem.second = tmp_str;
			ht.add(lexem);
		}
		return ht;
	}

};