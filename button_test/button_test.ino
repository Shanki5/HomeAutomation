
int cloud_state[4] = {0,0,0,0}; 
int masterButtonPins[4] = {16,5,4,0};

void readbutton(){

  for (int i=0;i<4;i++){
    if(digitalRead(masterButtonPins[i]))
    {
      cloud_state[i] = !cloud_state[i];

    }
//    Serial.println(); 
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for(int i = 0;i < 4; i++)
  {
    pinMode(masterButtonPins[i],INPUT);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  readbutton();
  for(int i = 0; i < 4; i++)
    Serial.print(cloud_state[i]);
  Serial.println();
}
