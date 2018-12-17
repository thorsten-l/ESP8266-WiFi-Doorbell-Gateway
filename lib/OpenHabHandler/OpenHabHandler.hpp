#ifndef __OPENHAB_HANDLER_H__
#define __OPENHAB_HANDLER_H__

class OpenHabHandler
{
private:
  void sendValueV1(const char *value);
  void sendValueV2(const char *value);

public:
  void sendValue(const char *value);
};

extern OpenHabHandler openHabHandler;

#endif
