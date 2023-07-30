#include "interpreter.h"

#include <gtest/gtest.h>
#include <thread>
#include <fstream>


// 
TEST(SomeGtests, TestInputA)
{
	using namespace std::chrono_literals;
	std::vector<file_time> times; // времена создания файлов.
	times.reserve(4);

    int test_number = 3;
    
    std::shared_ptr<Collector>    collector_ptr   = std::make_shared<Collector>(static_cast<size_t>(test_number));
    std::unique_ptr<Interpreter>  interpreter_ptr = std::make_unique<Interpreter>(collector_ptr);

	std::istringstream input;

	// TEST DATA SET
	input.str("1\n{\n2\n3\n4\n5\n6\n}\n7\n{\n8\n");

	for (std::string line; std::getline(input, line); )
	{
		interpreter_ptr->handle_input(line);
		
		if (times.empty()) {
			times.push_back(collector_ptr->get_file_time());
		}
		else {
			if (times.back() != collector_ptr->get_file_time()) {
				times.push_back(collector_ptr->get_file_time());
			}
		}

		std::this_thread::sleep_for(1000ms);
	}

	if (input.eof()) {
		interpreter_ptr->handle_eof();
	}

	// DATA SET for COMPARE
	std::vector<std::string> good_strings = { "1", "2, 3, 4, 5, 6", "7", "8" };

	

	size_t i = 0;

	while(true) {
		auto seconds = std::chrono::duration_cast<std::chrono::seconds>(times[i].time_since_epoch()).count();
		std::stringstream filename;
		filename << "bulk" << seconds << ".log";

		std::string file_data;
		std::ifstream test_file;
		
		test_file.open(filename.str());

		bool open_flag = test_file.is_open();

		ASSERT_TRUE(open_flag == true);
 
		std::getline(test_file, file_data);
		
		ASSERT_TRUE(0 == file_data.compare(good_strings[i]));

		test_file.close();

		++i;
		if (i == times.size()) {
			break;
		}

		filename.clear();
	}


    // Assert
    ASSERT_TRUE(i == good_strings.size());
}