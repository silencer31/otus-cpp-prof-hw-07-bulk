#pragma once

#include "file_logger.h"

/**
* @brief ����� - ���������� ����������� ������ �� �������.
*/
class Interpreter {
public:
	Interpreter() = delete;
	
	explicit Interpreter(std::shared_ptr<Collector>  cltr_ptr)
		: collector_ptr(cltr_ptr) {
		// ������� File Logger � �������� ��� ��������� �� ��������� � �������.
		file_logger_ptr = std::make_shared<FileLogger>(collector_ptr);

		// � ��������� � ������� ��������� File Logger ��� ������������.
		collector_ptr->attach(file_logger_ptr);
	}
	
	~Interpreter() {
		collector_ptr->detach(file_logger_ptr);
	}

	/**
	* ��������� �������� ������.
	*/
	void handle_input(const std::string& command);

	/**
	* ��������� ����������� EOF.
	*/
	void handle_eof();

private:
	const std::shared_ptr<Collector>  collector_ptr; // ��������� �� ������ � ���������� � �������.
	std::shared_ptr<FileLogger>		  file_logger_ptr; // ��������� �� ������ ��� ������ ��������� ������ � ����.
};