#include <unity.h>
#include <SyncDispatcher.h>

class Counter: public Pollable {
    public:
        int data;
        Counter(int data): data(data) {}
        virtual void poll() {
            data++;
        };
};

void test_syncdispatcher() {
    const int data = 12;
    SyncDispatcher syncDispatcher;
    Counter counter1(data);
    Counter counter2(data);
    Counter counter3(data);
    syncDispatcher.addPollable(&counter1);
    syncDispatcher.addPollable(&counter2);
    syncDispatcher.addPollable(&counter3);
    syncDispatcher.poll();
    syncDispatcher.poll();
    syncDispatcher.poll();
    TEST_ASSERT_EQUAL_INT(data+3, counter1.data);
    TEST_ASSERT_EQUAL_INT(data+3, counter2.data);
    TEST_ASSERT_EQUAL_INT(data+3, counter3.data);
}

void setUp() {

}

void tearDown() {
    
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_syncdispatcher);
    UNITY_END();

    return 0;
}