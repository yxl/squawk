#define DEVICE_FIRST 0
#define DEVICE_LAST 0
#define WAIT_FOR_DEEP_SLEEP_EVENT_NUMBER (DEVICE_LAST+1)
#define FIRST_IRQ_EVENT_NUMBER (WAIT_FOR_DEEP_SLEEP_EVENT_NUMBER+1)
#define SHALLOW_SLEEP_CLOCK_MODE_NORMAL 0
#define SLEEP_MANAGER_ENABLED_IRQS 1

void doShallowSleep(long long millis) {
    sleep((millis - sysTimeMillis()) / 1000);
}

void doDeepSleep(long long millis, int remain_powered) {
    sleep((millis - sysTimeMillis()) / 1000);
}

void disableARMInterrupts() {
}

void enableARMInterrupts() {
}

int isSerialPortInUse(int device_type) {
    return 0;
}

int sysAvailable(int device_type) {
    return 0;
}

void freeSerialPort(int device_type) {
}

void systemGetEventHandler() {
}

void setMilliseconds(long long millis) {
}

void ioExecuteSys() {
}
