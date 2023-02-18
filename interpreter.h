#pragma once

#include "collector.h"

/**
* @brief ����� - ���������� ����������� ������ �� �������.
*/
class Interpreter {
public:
	Interpreter() = delete;
	
	explicit Interpreter(std::shared_ptr<Collector>  c_ptr) 
		: collector_ptr(c_ptr) {}
	
	~Interpreter() = default;

	/**
	* ��������� �������� ������.
	*/
	void handle_input(const std::string& command);

	/**
	* ��������� ����������� EOF.
	*/
	void handle_eof();

private:
	const std::shared_ptr<Collector>  collector_ptr;
};