class switchCtrl
{
  private:
    int switchMode=0;
    int switchPin=0;
    int switchState=0;
    int switchDelay=1000;

    void switchInit()
    {
      pinMode(this->switchPin,INPUT);
      
      switch(this->switchMode)
      {
        case 0:this->switchInit_0();
        break;
        case 1:this->switchInit_1();
        break;
        case 2:this->switchInit_2();
        break;
      }
    }

    void switchInit_0()
    {
     digitalWrite(this->switchPin,LOW); 
    }
    
    void switchAction_0()
    {
      digitalWrite(this->switchPin,HIGH);
      delay(this->switchDelay);
      digitalWrite(this->switchPin,LOW);
    }

    void switchInit_1()
    {
     digitalWrite(this->switchPin,HIGH); 
    }
    
    void switchAction_1()
    {
      digitalWrite(this->switchPin,LOW);
      delay(this->switchDelay);
      digitalWrite(this->switchPin,HIGH);
    }

    void switchInit_2()
    {
      this->switchState=0;
      digitalWrite(this->switchPin,LOW);
    }
    
    void switchAction_2()
    {
      this->switchState=!this->switchState;
      if (this->switchState==1)
        digitalWrite(this->switchPin,HIGH);
      else
        digitalWrite(this->switchPin,LOW);
    }

    void switchInit_3()
    {
      this->switchState=1;
      digitalWrite(this->switchPin,HIGH);
    }

    void switchAction_3()
    {
      this->switchState=!this->switchState;
      if (this->switchState==1)
        digitalWrite(this->switchPin,HIGH);
      else
        digitalWrite(this->switchPin,LOW);
    }
    
  public:
    switchCtrl(int mode,int pin)
    {
      this->switchMode=mode;
      this->switchPin=pin;
      
      this->switchInit();
    }
    
    void switchAction()
    {
      switch(this->switchMode)
      {
        case 0:this->switchAction_0();
        break;
        case 1:this->switchAction_1();
        break;
        case 2:this->switchAction_2();
        break;
      }
    }

    void switchSetDelay(int delay)
    {
      this->switchDelay=delay;
    }
};
