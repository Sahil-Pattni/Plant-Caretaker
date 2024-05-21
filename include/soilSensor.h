#define DRY 1
#define WET 0

class SoilSensor {
    private:
        int pin;
        const int THRESHOLD = 3000;
    public:
        SoilSensor(int pin);
        int determine();
        int reading();
};