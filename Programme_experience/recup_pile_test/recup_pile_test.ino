void setup() {
  Serial.begin(2000000); //utilise un moniteur série de 2000000 de bit seconde
}

void loop() {
  int val = analogRead(A1); //recupére la tension
  
  //on affiche toujours des nombre avec 4 caractère
  if (val <= -1) {
    Serial.println("0000"); //traite le cas 0
  }
  else {
    if (val < 10) {
      Serial.print("0"); //pour ajouter des zero devant en cas de pb
    }
    if (val < 100) {
      Serial.print("0"); //pour ajouter des zero devant en cas de pb
    }
    if (val < 1000) {
      Serial.print("0"); //pour ajouter des zero devant en cas de pb
    }
  }
  Serial.println(val);
}
