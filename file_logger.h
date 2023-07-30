#pragma once

#include "Observ/observer.h"

#include <vector>
#include <string>
#include <memory>
#include <chrono>
#include <iostream>

using command_iterator = std::vector<std::string>::const_iterator;
using file_time = std::chrono::system_clock::time_point;

class Collector;

/**
* @brief Класс для записи коллекции команд в файл.
*/
class FileLogger : public Observer {
public:
	FileLogger() {}
	
	~FileLogger() = default;

	void write_commands_to_file(const std::vector<std::string>& collection, const file_time& ftime);

	/**
	* Реакция на появление данных в коллекторе.
	*/
	void update() override;

private:

};