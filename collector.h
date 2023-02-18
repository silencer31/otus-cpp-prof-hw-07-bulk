#pragma once

#include "file_logger.h"

// Тип введённых данных.
enum class InputType {
	NO_INPUT,
	COMMAND,
	OPEN_BRACKET,
	CLOSE_BRACKET,
	END_INPUT
};

// Текущий тип хранилища команд.
enum class StorageType {
	UNKNOWN_T,
	STATIC_T,
	DYNAMIC_T
};

/**
* @brief Класс, содержащий коллекцию команд и управляющий ею.
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
	* Обработка ввода.
	*/
	void handle_input(InputType input_type, const std::string& command);

	/**
	* Вывод коллекции в консоль.
	*/
	void output_collection();

	/**
	*  Вывод всей коллекции в консоль и запись в файл.
	*  @param clear_flag - очищать ли коллекцию после вывода.
	*/
	void flush_collection(bool clear_flag);

	/**
	* Подготовка коллекции к новому вводу неизвестных данных.
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