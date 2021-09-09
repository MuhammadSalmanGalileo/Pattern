#include <unity.h>
#include <Observer.h>

class TestObservable: public ObservableState<int> {
    private:
        int _data;
    public:
        TestObservable(int data): _data(data) {}
        virtual int getState() {
            return _data;
        }
        void poll() {
            updateObservers();
        }
};

class TestObserver: public Observer {
    private:
        ObservableState<int> *_source;
        int data;
    public:
        TestObserver(ObservableState<int> *source): _source(source), data(0) {}

        virtual void update(Observable* source) {
            if(_source == source) {
                data = _source->getState();
            }
        }

        int getData() {
            return data;
        }
};

void test_total_scenario_observer_pattern() {
    const int data = 12;
    TestObservable testObservable(data);
    TestObserver testObserver(&testObservable);
    testObservable.addObserver(&testObserver);
    testObservable.poll();
    TEST_ASSERT_EQUAL_INT(data, testObservable.getState());
    TEST_ASSERT_EQUAL_INT(data, testObserver.getData());
}

void test_init_observable() {
    const int data = 12;
    TestObservable testObservable(data);
    TEST_ASSERT_EQUAL_INT(data, testObservable.getState());
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_init_observable);
    RUN_TEST(test_total_scenario_observer_pattern);
    UNITY_END();
    
    return 0;
}