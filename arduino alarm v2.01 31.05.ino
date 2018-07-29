#include <TimeLib.h>



// pin ýo
int pirPin = 9; // PIR pin
int outPin = 12; // pir algýladýgýnda led röleyi kontrol için
int outPinSiren = 13; //pir algýladýgýnda siren röleyi kontrol için
int deger = 0; // pýrdan okunan deðer


//rf control
int pinA = 3;
int pinB = 2;
int dA;
int dB;

//Alarm Durumu devrede veya devre dýsý
int alarmDurum = 1;


//alarm çalýyor yada çalmýyor
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
  pinMode(pirPin, INPUT); // PIR Pin'i giriþ yapýlýyor
  pinMode(outPin, OUTPUT); //alýnan deðere göre lede çýkýþ yapýlýyor
  pinMode(outPinSiren, OUTPUT); //siren pini çýkýþ yapýlýyor

  //RF pin
  pinMode(pinA, INPUT); // rf Pin'i giriþ yapýlýyor
  pinMode(pinB, INPUT);

  //Zamani ayarlama
  setTime(t);

  pinMode(7, OUTPUT);
}

void loop() {
if(!kesmeDur){
  //RF pinleri okunup dA-dB deðiþkenlerine atanýyor
  dA = digitalRead(pinA);
  dB = digitalRead(pinB);

  //Kumandadan alarm aktif pasif butonlarý algýlandý*****
  if (dA == HIGH) {  // Button A basýldý
    alarmDurum = 1;  //Alarm devrede              //***

  }

  if (dB == HIGH) {  // Button B basýldý          //***
    alarmDurum = 0;   // Alarm devre dýþý         //***

  }

  deger = digitalRead(pirPin);

  //Alarm aktif iken yapýlacaklar
  if (alarmDurum == 1 ) { //alarm aktif iken yapýlacaklar
digitalWrite(7,LOW);

    Serial.println(deger);


    if (deger == 1) {  //alarm tetiklendiðinde yapýlacaklar
      alarmZaman = now(); //alarmýn tetiklendiði zamaný aldýk
      caliyor = 1;

    }


    else if (deger == 0) {

      digitalWrite(outPin , HIGH);
      // digitalWrite(outPinSiren,HIGH);
    }

  }

  if (now() - alarmZaman > 1 ) { //alarm belli bir süre yandýktan sonra sönmesi için koþul

    caliyor = 0;

    digitalWrite(outPin, HIGH);   // rolede high kalapý low açýk ** ledde hýgh açýk
    digitalWrite(outPinSiren, HIGH);

  }


  //Alarm pasif iken yapýlacaklar
  if (alarmDurum == 0) { //Alarm pasif iken yapýlacaklar
    digitalWrite(outPin , HIGH);
    //Serial.println("sistem kapalý");
    digitalWrite(outPinSiren, HIGH); // siren kapalý

digitalWrite(7,HIGH);
  }


  //alarm çalýyormu
  if (caliyor == 1) {

    // siren açýp kapatma
    digitalWrite(outPinSiren, LOW);
    delay(500);
    digitalWrite(outPinSiren, HIGH);
    //delay(100);

    //led - röle yanýp söner
    digitalWrite(outPin, LOW);
    delay(300);
    digitalWrite(outPin, HIGH);
    // delay(300);




  }

  else if (caliyor == 0) {

    digitalWrite(outPin, HIGH);   // rolede high kalapý low açýk ** ledde hýgh açýk
    digitalWrite(outPinSiren, HIGH);

  }



}


}//loop;

void alarmKapat() {
  kesmeDur=true;
  alarmDurum = 0;
  digitalWrite(outPin , HIGH);
  Serial.println("kesme kapalý");
  digitalWrite(outPinSiren, HIGH); // siren kapalý
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

