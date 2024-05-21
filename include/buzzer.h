class ActiveBuzzer {
    private:
        int pin;
    public:
        ActiveBuzzer(int pin);
        void beep(int duration);
        void beep(int n, int duration);
        void beep();
};