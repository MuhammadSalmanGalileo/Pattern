#include <unity.h>
#include <Pollable.h>
#include <functional>

class TestIntervalPollable: public IntervalPollable {
    private: 
        virtual void intervalPoll() {
            data++;
        }
    
    public:
        int data;
        TestIntervalPollable(int data, unsigned long interval, std::function<unsigned long(void)> timeFunc): IntervalPollable(interval, timeFunc), data(data) {}
};

void test_interval() {
    const int data = 5, interval = 100;
    unsigned long time = 0;
    TestIntervalPollable test(data, interval, [&time](){
        return time;
    });
    time += 99;
    test.poll();
    TEST_ASSERT_EQUAL_INT(data+1, test.data);
    time += 1;
    test.poll();
    TEST_ASSERT_EQUAL_INT(data+1, test.data);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_interval);
    UNITY_END();
}