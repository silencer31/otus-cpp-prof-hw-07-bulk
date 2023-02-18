#pragma once

#include "file_logger.h"

// ��� �������� ������.
enum class InputType {
	NO_INPUT,
	COMMAND,
	OPEN_BRACKET,
	CLOSE_BRACKET,
	END_INPUT
};

// ������� ��� ��������� ������.
enum class StorageType {
	UNKNOWN_T,
	STATIC_T,
	DYNAMIC_T
};

/**
* @brief �����, ���������� ��������� ������ � ����������� ��.
*/
class Collector {
public:
	Collector() = delete;

	explicit Collector(const std::shared_ptr<FileLogger>& flptr, int size) :
		file_logger_ptr(flptr), collection_max_size(size), storage_type(StorageType::UNKNOWN_T),
		open_brackets_number(0), close_brackets_number(0)
	{
		commands_collection.reserve(collection_max_size);
	}


	~Collector() {
		flush_collection(true);
	}
	
	/**
	* ��������� �����.
	*/
	void handle_input(InputType input_type, const std::string& command);

	/**
	* ����� ��������� � �������.
	*/
	void output_collection();

	/**
	*  ����� ���� ��������� � ������� � ������ � ����.
	*  @param clear_flag - ������� �� ��������� ����� ������.
	*/
	void flush_collection(bool clear_flag);

	/**
	* ���������� ��������� � ������ ����� ����������� ������.
	*/
	void reset_collection();

private:
	const std::shared_ptr<FileLogger> file_logger_ptr;
	
	int collection_max_size;
	std::vector<std::string> commands_collection;

	StorageType storage_type;
	int open_brackets_number;
	int close_brackets_number;

	file_time first_command_time;
};