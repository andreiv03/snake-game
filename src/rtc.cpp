#include "rtc.hpp"

RTC_DS1307 rtc;

void initRTC() {
  rtc.begin();

  if (!rtc.isrunning()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}
