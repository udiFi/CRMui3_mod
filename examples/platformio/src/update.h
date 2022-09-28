void pieceUpdate(String paramName, String value) {
  if(paramName == "select4"){
    select4 = !select4;
    Serial.printf("[Update_P] Select обновлен на %s без конфига\n",value.c_str());
    crm.webUpdate();
  }
}

void myLoopRun() {
 
  static int a[3] = {0};
  static int i = 0;
  if (i > 2) i = 0;
  a[i] = WiFi.RSSI();

  // Обновление значений элементов веб интерфейса
  // crm.webUpdate("[ID элемента]", "[Значение]");
  // Интервал отправки 1 раз в сек.
  int b = (a[0] + a[1] + a[2]) / 3;
  crm.webUpdate("rssi", String(b));
  crm.webUpdate("rssiraw", String(a[i]));
  crm.webUpdate("G_0", String(b));
  crm.webUpdate("G_1", String(random(-20, 60)));
  crm.webUpdate("G_2", String(random(0, 100)));
  i++;
}

void update() {
  // Метод вызывается при каждом изменении значения элементов через веб интерфейса
  Serial.println("Method update() run");
  Serial.println("Language: " + lng());

  // Получить(Записать) значение переменной из(в) конфига
  // crm.var("ID")
  // crm.var("ID", "Значение")
  bool a = crm.var_bool("card1");

  static bool b = false;
  if (b != a) {
    digitalWrite(2, a ? HIGH : LOW);

    // Отправить уведомление на страницу веб интерфейса
    // crm.webNotif("[Цвет]", "[Сообщение]", [время показа, с], [крестик закрыть (1, true)]);
    // Цвет: green, red, orange, blue, "" - без цвета
    crm.webNotif(a ? "Red" : "Green", a ? "Мотор запущен" : "Мотор остановлен", 5);

    b = a;
  }
}