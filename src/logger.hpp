#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <sstream>

#define LOG_SILENT 0
#define LOG_ERROR 1
#define LOG_WARNING 2
#define LOG_INFO 3


#define LOG_DEFAULT 3

#define debug(level) logger(level, __PRETTY_FUNCTION__, __FILE__, __LINE__)

// Nice, but will only work in bash :D
#define BSLOG_ERROR "\033[0;31m-ERROR-\033[0;0m"
#define BSLOG_WARNING "\033[0;33m-WARNING-\033[0;0m"
#define BSLOG_INFO "\033[0;34m-INFO-\033[0;0m"


#define CONSOLE_COLOR_RED "\033[0;31m"
#define CONSOLE_COLOR_GOLD "\033[0;33m"
#define CONSOLE_COLOR_NORMAL "\033[0;0m"

// extern unsigned GlobalLogLevel;
static unsigned GlobalLogLevel = LOG_INFO;

class logger {
 public:

  logger() {};
  logger(unsigned loglevel, std::string name, std::string file, int line) :
        m_loglevel(loglevel),
        m_name(name),
        m_file(file),
        m_line(line) {}

  ~logger() {
    if(m_loglevel <= GlobalLogLevel) {
      m_Outstream << m_Stream.rdbuf();
    }
  }

  std::ostream& getOutStream() { return m_Outstream; }

  template <class T>
  std::ostream& operator<<(const T& thing) {

    switch (m_loglevel) {
      case 1: { m_Stream << BSLOG_ERROR << "  " << thing; break; }
      case 2: { m_Stream << BSLOG_WARNING << "  " << thing; break; }
      case 3: { m_Stream << BSLOG_INFO << "  " << thing; break; }
    }

    return m_Stream;
  }

private:
  unsigned m_loglevel = LOG_DEFAULT;
  std::stringstream m_Stream;
  std::ostream& m_Outstream = std::cout;
  std::string m_name = "";
  std::string m_file = "";
  int m_line = 0;
};
#endif
