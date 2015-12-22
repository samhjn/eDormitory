const int switchPin[1]={2};  //Control a switch
const int otherPin[1]={3};  //For other output devices

const int sensorPin[3]={A0,A1,A2}; 

const int idPin[4]={A3,A4,A5,A6};

const int rolePin[3]={4,5,6}; 
/*
rolePin[0] 1=Input client  0=Output client
rolePin[1] 1=Lasting switch  0=Moment switch
rolePin[2] 1=HIGH default   0=Low default
*/

const int REFRESH_COUNT=10000;
