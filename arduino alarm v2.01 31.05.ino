#include <TimeLib.h>



// pin �o
int pirPin = 9; // PIR pin
int outPin = 12; // pir alg�lad�g�nda led r�leyi kontrol i�in
int outPinSiren = 13; //pir alg�lad�g�nda siren r�leyi kontrol i�in
int deger = 0; // p�rdan okunan de�er


//rf control
int pinA = 3;
int pinB = 2;
int dA;
int dB;

//Alarm Durumu devrede veya devre d�s�
int alarmDurum = 1;


//alarm �al�yor yada �alm�yor
int caliyor = 0;

//Zaman Ayarlari
time_t alarmZaman; // Alarm tetiklenince o zamanin tutuldugu degisken
time_t t = 1525979625; // 10.05.2018 19:30 - https://www.epochconverter.com

boolean kesmeDur=false;


void setup() {
  Serial.begin(9600);
  attachInterrupt(0, alarmKapat, RISING);
 attachInterrupt(1, alarmAc, RISING);
  //PIR
  pinMode(pirPin, INPUT); // PIR Pin'i giri� yap�l�yor
  pinMode(outPin, OUTPUT); //al�nan de�ere g�re lede ��k�� yap�l�yor
  pinMode(outPinSiren, OUTPUT); //siren pini ��k�� yap�l�yor

  //RF pin
  pinMode(pinA, INPUT); // rf Pin'i giri� yap�l�yor
  pinMode(pinB, INPUT);

  //Zamani ayarlama
  setTime(t);

  pinMode(7, OUTPUT);
}

void loop() {
if(!kesmeDur){
  //RF pinleri okunup dA-dB de�i�kenlerine atan�yor
  dA = digitalRead(pinA);
  dB = digitalRead(pinB);

  //Kumandadan alarm aktif pasif butonlar� alg�land�*****
  if (dA == HIGH) {  // Button A bas�ld�
    alarmDurum = 1;  //Alarm devrede              //***

  }

  if (dB == HIGH) {  // Button B bas�ld�          //***
    alarmDurum = 0;   // Alarm devre d���         //***

  }

  deger = digitalRead(pirPin);

  //Alarm aktif iken yap�lacaklar
  if (alarmDurum == 1 ) { //alarm aktif iken yap�lacaklar
digitalWrite(7,LOW);

    Serial.println(deger);


    if (deger == 1) {  //alarm tetiklendi�inde yap�lacaklar
      alarmZaman = now(); //alarm�n tetiklendi�i zaman� ald�k
      caliyor = 1;

    }


    else if (deger == 0) {

      digitalWrite(outPin , HIGH);
      // digitalWrite(outPinSiren,HIGH);
    }

  }

  if (now() - alarmZaman > 1 ) { //alarm belli bir s�re yand�ktan sonra s�nmesi i�in ko�ul

    caliyor = 0;

    digitalWrite(outPin, HIGH);   // rolede high kalap� low a��k ** ledde h�gh a��k
    digitalWrite(outPinSiren, HIGH);

  }


  //Alarm pasif iken yap�lacaklar
  if (alarmDurum == 0) { //Alarm pasif iken yap�lacaklar
    digitalWrite(outPin , HIGH);
    //Serial.println("sistem kapal�");
    digitalWrite(outPinSiren, HIGH); // siren kapal�

digitalWrite(7,HIGH);
  }


  //alarm �al�yormu
  if (caliyor == 1) {

    // siren a��p kapatma
    digitalWrite(outPinSiren, LOW);
    delay(500);
    digitalWrite(outPinSiren, HIGH);
    //delay(100);

    //led - r�le yan�p s�ner
    digitalWrite(outPin, LOW);
    delay(300);
    digitalWrite(outPin, HIGH);
    // delay(300);




  }

  else if (caliyor == 0) {

    digitalWrite(outPin, HIGH);   // rolede high kalap� low a��k ** ledde h�gh a��k
    digitalWrite(outPinSiren, HIGH);

  }



}


}//loop;

void alarmKapat() {
  kesmeDur=true;
  alarmDurum = 0;
  digitalWrite(outPin , HIGH);
  Serial.println("kesme kapal�");
  digitalWrite(outPinSiren, HIGH); // siren kapal�
delay(5000);
digitalWrite(7,HIGH);
}

void alarmAc() {
  kesmeDur=false;
  alarmDurum = 1;
  digitalWrite(outPin , LOW);
  Serial.println("kesme Acik");
  digitalWrite(outPinSiren, LOW); // siren acik
delay(5000);
digitalWrite(7,LOW);
}

