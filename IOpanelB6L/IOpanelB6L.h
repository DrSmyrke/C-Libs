#define p0 2
#define p1 3
#define p2 4
#define portIO PORTD
void ledON(unsigned int num)
{
  pinModePD(p0,OUTPUT);
  pinModePD(p1,OUTPUT);
  pinModePD(p2,OUTPUT);
  digitalWrite(portIO,p0,LOW);
  digitalWrite(portIO,p1,LOW);
  digitalWrite(portIO,p2,LOW);

  if(num==2){
    digitalWrite(portIO,p1,HIGH);
    pinModePD(p2,INPUT);
  }
  if(num==3){
    digitalWrite(portIO,p0,HIGH);
    pinModePD(p2,INPUT);
  }
  if(num==4){
    pinModePD(p0,INPUT);
    digitalWrite(portIO,p1,HIGH);
  }
  if(num==1){
    pinModePD(p0,INPUT);
    digitalWrite(portIO,p2,HIGH);
  }
  if(num==5){
    pinModePD(p1,INPUT);
    digitalWrite(portIO,p2,HIGH);
  }
  if(num==6){
    pinModePD(p1,INPUT);
    digitalWrite(portIO,p0,HIGH);
  }
}