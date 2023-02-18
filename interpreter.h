#pragma once

#include "collector.h"

/**
* @brief Класс - анализатор поступающих команд из консоли.
*/
class Interpreter {
public:
	Interpreter() = delete;
	
	explicit Interpreter(std::shared_ptr<Collector>  c_ptr) 
		: collector_ptr(c_ptr) {}
	
	~Interpreter() = default;

	/**
	* Обработка введённой строки.
	*/
	void handle_input(const std::string& command);

	/**
	* Обработка полученного EOF.
	*/
	void handle_eof();

private:
	const std::shared_ptr<Collector>  collector_ptr;
};