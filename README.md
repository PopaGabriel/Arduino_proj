# Arduino_proj
# Owner project: Popa Catalin Gabriel
#Componente: - Motor Servo SG90 9g 180 grade X 2
             - Breadboard
             - Arduino Uno
             - Display LCD
             - Fire
             - Senzor higrometru capacitiv cu alarma(senzo umiditate pamant)
             - Modul senzor lumina
Un utilizator o sa umple paharelul cu apa. Apasa lung pe buton astfel incat
contorul din interiorul arduinou-lui sa fie resetat, si dupa poate sa plece sa
isi vada de treaba. Aparatul monitorizeaza atat nivelul de apa din pamant cat si
intensitatea luminoasa iar atunci cand sunt depasite anumite limite acesta se
"apara" prin udare sau prin tragerea draperiei. Valorile preluate de catre cei
doi senzori sunt trimisi constant catre un ecran lcd, de asemenea tot pe ecran
o sa apara si procentajul de apa ramas.

Descrierea codului aplicaţiei (firmware):
  * Mediul de dezvoltare este cel dat de Arduino in sine.
  * Totul este implementat intr-un singur fisier numit
  arduino_pm_Popa_Catalin_Gabriel.ino.
  * Pentru a porni trebuie doar conectat arduino-ul, si montat totul, in rest 
  absolut tot ar trebuii sa fie usor de folosit, senzorul de umiditate probabil 
  ca o sa trebuiasca repornit intre folosiri (deoarece este un senzor foarte
  bun). Uneori este nevoie sa se mai regleze si senzorul de lumina cu o
  surubelnita. Senzorii verifica constant starea plantei si se tine cont de
  cata apa este in rezervor (daca a udat sau nu planta), aceasta poate fi udata
  si manual prin apasarea butonului de pe breadboard.
