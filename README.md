# inbyggda-system-inl-mning-del-2

# Passagesystem

Det här projektet är ett enkelt passagesystem byggt med Arduino Uno i Wokwi.

Systemet använder keypad, RFID, RTC, servo, buzzer, RGB LED och shift register.

## Funktion

När systemet startar är det låst. Då lyser den röda lampan och servon är stängd.

Rätt kod är:

1234

När rätt kod skrivs in blir lampan grön och servon öppnas i 3 sekunder. Sedan stängs servon igen och lampan blir röd.

Om fel kod skrivs in låter buzzern.

Varje siffra på keypaden gör att lampan blinkar blått.

## RFID

RFID aktiveras med knappen A på keypaden.

Efter att A har tryckts kan man trycka TAP på RFID kortet i Wokwi. Då öppnas systemet på samma sätt som med rätt kod.

RFID aktiveras med A för att undvika att Wokwi läser kortet direkt och skapar loop.

## Knappar och färger

1234 öppnar systemet  
A aktiverar RFID  
* rensar koden  

Röd = låst  
Grön = öppet  
Blå = knapptryck registrerat  

## RTC

RTC används för att läsa tiden. Tiden skrivs ut i Serial Monitor när systemet startar och när systemet öppnas.
