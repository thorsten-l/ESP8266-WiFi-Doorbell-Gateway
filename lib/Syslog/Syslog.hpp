#ifndef __SYSLOG_HPP__
#define __SYSLOG_HPP__

class Syslog
{

private:
  void send(const char *buffer);

public:
  void logInfo(const char *message);
  void logInfo(const char *message, int value);
  void logInfo(const char *message, const char * value);
};

extern Syslog syslog;

#endif
