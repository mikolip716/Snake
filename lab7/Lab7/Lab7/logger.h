#pragma once
#pragma warning(disable:4996)
#include <fstream>
#include <chrono>
#include <ctime>
#include <mutex>
class Logger {
	std::mutex m;
	std::ofstream f;
	unsigned short int level;
	void log(const std::string& level, const std::string& message) {
		std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::lock_guard<std::mutex> locker(m);
		f << level << " | " << std::ctime(&time) << "	" << message << '\n';
	}
public:
	Logger(const std::string& filename, unsigned short int level = 0) {
		set_level(level);
		f.open(filename);
	}
	~Logger() { f.close(); }
	void set_level(const unsigned short int& level) {
		if (level > 4)
			throw std::invalid_argument("level must be [0,4]");
		this->level = level;
	}
	void change_file(const std::string& filename) {
		f.close();
		f.open(filename);
	}
	void critical(const std::string& message) { log("CRITICAL", message); }
	void error(const std::string& message) { if (level < 4) log("ERROR", message); }
	void warning(const std::string& message) { if (level < 3)log("WARNING", message); }
	void info(const std::string& message) { if (level < 2)log("INFO", message); }
	void debug(const std::string& message) { if (level == 0) log("DEBUG", message); }
};
