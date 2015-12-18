class sensorCtrl
{
  private:
    int sensorPin=0;
    int sensorMode=0;

    void sensorInit()
    {
      
    }
  public:
    sensorCtrl(int mode,int pin)
    {
      this->sensorMode=mode;
      this->sensorPin=pin;

      this->sensorInit();
    }

    int sensorRead()
    {
      return analogRead(this->sensorPin);
    }
};
