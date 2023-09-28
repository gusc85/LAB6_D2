#include <SPI.h>
#include <SD.h>

File myFile;
File root;

int menu;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  SPI.setModule(0);

  Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output
  // or the SD library functions will not work.
  pinMode(PA_3, OUTPUT);

  if (!SD.begin(PA_3)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  root = SD.open("/");

  printDirectory(root,0);

  Serial.println("done!");
  imp_menu();
} 

//**********************************************************************************//

void loop()
{
  if(Serial.available()> 0){
    menu = Serial.read();
    if(menu == '1'){ // al presionar el número 1
      imp_KO();
    }
    else if(menu == '2'){ // al presionar el número 2
      imp_MA();
    }
    else if(menu == '3'){ // al presionar el número 3
      imp_AG();
    }
    else if (menu == '4') // al presionar el número 4
    {
      crear_dibujo();
    }
  }
}


//**********************************************************************************//

// IMPRIMIR DATOS DENTRO DE LA SD 
void printDirectory(File dir, int numTabs){
  while(true){

    File entry = dir.openNextFile();
    if (!entry){
      //no more files
      break;
    }
    for (uint8_t i=0; i<numTabs; i++){
      Serial.print('\t'); 
    }
    Serial.print(entry.name());
    if (entry.isDirectory()){
      Serial.println("/");
      printDirectory(entry, numTabs+1);
    } else {
      //files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}
//************************************************************************
void imp_KO(){
  myFile = SD.open("koopa.txt");
  if(myFile){
    Serial.println("koopa.TXT: ");

    while (myFile.available()){
      Serial.write(myFile.read());
    }
    //cerrar archivo
    myFile.close();
  } else{
    Serial.println("Error para abirir koopa.TXT");
  }
  imp_menu();
}
//***************************************************************************
void imp_MA(){
  myFile = SD.open("mario.txt");
  if(myFile){
    Serial.println("mario.TXT: ");

    while (myFile.available()){
      Serial.write(myFile.read());
    }
    //cerrar archivo
    myFile.close();
  } else{
    Serial.println("Error para abrir mario.TXT");
  }
  imp_menu();
}
//****************************************************************************
void imp_AG(){
  myFile = SD.open("aguacate.txt");
  if(myFile){
    Serial.println("aguacate.TXT: ");

    while (myFile.available()){
      Serial.write(myFile.read());
    }
    //cerrar archivo
    myFile.close();
  } else{
    Serial.println("Error para abrir aguacate.TXT");
  }
  imp_menu();
}

// MENÚ DONDE EL USUARIO ELIGIRÁ SU DIBUJO
void imp_menu(){
  Serial.println("");
  Serial.println("Por favor, presione el número correspondiente al dibujo que desea visualizar:");
  Serial.println("Presione 1 para visualizar a koopa");
  Serial.println("Presione 2 para visualizar a mario");
  Serial.println("Presione 3 para visualizar a un aguacate");
  Serial.println("Presione 4 para crear su propia imagen personalizada, y luego guardarla dentro de la SD"); 
  Serial.println("");  
}

//****************************************************************************

void crear_dibujo()
{
  Serial.println("Dibuje un círculo en la terminal utilizando caracteres.");
  Serial.println("Utilice 'o' para dibujar y '!' para terminar y guardar.");

  String dibujo = "";  // Variable para almacenar el dibujo

  while (true)
  {
    if (Serial.available() > 0)
    {
      char c = Serial.read();

      // Si el usuario envía '!', se guarda el dibujo dentro de la SD
      if (c == '!')
      {
        Serial.println("Guardando el dibujo...");

        // Guardar el dibujo en un archivo
        myFile = SD.open("NUEVO.txt", FILE_WRITE);

        if (myFile)
        {
          myFile.print(dibujo);
          myFile.close();
          Serial.println("Dibujo guardado correctamente");
        }
        else
        {
          Serial.println("Error al guardar el dibujo, por favor intente de nuevo");
        }

        imp_menu();
        break;
      }

      // Si el usuario envía 'o', se le permite dibujar
      if (c == 'o')
      {
        dibujo += '*';
        Serial.print('*');
      }
      else
      {
        Serial.print(c);
      }
    }
  }
}


    
