#include "file_logger.h"

#include <fstream>
#include <sstream>

/**
* Запись коллекции в файл с указанием временной метки.
*/
void FileLogger::write_commands_to_file(const std::vector<std::string>& collection, const file_time& ftime)
{
	auto seconds = std::chrono::duration_cast<std::chrono::seconds>(ftime.time_since_epoch()).count();
	
	std::stringstream filename;
	filename << "bulk" << seconds << ".log";

	std::ofstream file(filename.str(), std::ofstream::out);
	
	for (command_iterator comm_iter = collection.cbegin(); comm_iter != collection.cend(); ++comm_iter) {
		file << (*comm_iter);
		if (comm_iter + 1 != collection.cend()) {
			file << ", ";
		}
	}
}