void api(String p) {
  // Метод вызывается при API запросах
  // Обязательно с параметром, тип String
  //
  // Ответ на запрос, тип JSON
  // crm.apiResponse("[ID]", "[Значение]");

  Serial.print("API: ");
  Serial.println(p);

  DynamicJsonDocument doc(200);
  deserializeJson(doc, p);

  //Запрос http://IP/api?hum
  const char* hum = doc["hum"];
  if (hum != NULL) {
    crm.apiResponse("Humidity", "51%");
  }

  //Использование параметров
  //Запрос http://IP/api?random=500
  const char* rnd = doc["random"];
  if (rnd != NULL) {
    crm.apiResponse("Random", String(random(atoi(rnd))));
  }

  //Запрос http://IP/api?print=[any_text]
  const char* prt = doc["print"];
  if (prt != NULL) {
    Serial.println(prt);
  }
}