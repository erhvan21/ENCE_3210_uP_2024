#define button0
#define button1
#define button2
#define button3
#define button4
#define button5
#define button6
#define button7
#define button8
#define button9

#define buttonAdd
#define buttonSub
#define buttonDiv
#define buttonMul

#define buttonEqu

void buttonSetup(){
  pinMode(button0,INPUT);
  pinMode(button1,INPUT);
  pinMode(button2,INPUT);
  pinMode(button3,INPUT);
  pinMode(button4,INPUT);
  pinMode(button5,INPUT);
  pinMode(button6,INPUT);
  pinMode(button7,INPUT);
  pinMode(button8,INPUT);
  pinMode(button9,INPUT);

  pinMode(buttonAdd, INPUT);
  pinMode(buttonSub, INPUT);
  pinMode(buttonDiv, INPUT);
  pinMode(buttonMul, INPUT);

  pinMode(buttonEqu, INPUT);
}

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
