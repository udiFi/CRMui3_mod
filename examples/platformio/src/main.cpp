//Example use CRMui3  //Пример использования CRMui3
#include <Ticker.h> // Входит в состав ядра
#include "CRMui3.h"

#include "var.h"
#include "interface.h"
#include "update.h"
#include "api.h"


String lng() {
  // Вариант реализации многоязычности
  // Получить индекс языка
  // crm.getLang();
  String L = crm.getLang();
  uint8_t l = 0;
  if (L == "de") l = 1;
  else if (L == "ru") l = 2;
  switch (l) {
    case 0: return "English";
    case 1: return "Deutsch";
    case 2: return "Russian";
    default: return "n/a";
  }
}

//функции кнопок
void hw_butt() {
  Serial.println("HW BUTTON PRESS!");
}

// ------- Through a callBackButton Event -------------
void btnResponce(const char *name) {
  if (strcmp(name, "card3") == 0) {
    Serial.println("Card 3 Button press.");
    st3 = !st3;
    crm.webUpdate("card3", st3 ? "Открыта" : "Закрыта");
  }
}
// ----------------------------------------------------

void card_sw4() {
  Serial.println("Card 4 Button press.");
  st4 = !st4;
  crm.webUpdate("card4", st4 ? "Открыта" : "Закрыта");
}

void card_sw5() {
  Serial.println("Card 5 Button press.");
  st5 = !st5;
  crm.webUpdate("card5", st5 ? "Открыта" : "Закрыта");
}

void tablt2() {
  Serial.println("Button STOP press.");
  crm.webUpdate("t2", String(millis()));
}


void reboot() {
  crm.webNotif("info", "Reboot ESP", 5, 1);

  // Отправляет модуль на перезагрузку, с сохранением настроек, если требуется.
  crm.espReboot();
}

void setup() {
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  pinMode(4, INPUT_PULLUP);            // Button pin

  // Отключает управление WiFi средствами библиотеки
  //crm.disableWiFiManagement();

  // Включает возможность прошивать модуль по сети через Arduino IDE
  crm.useArduinoOta();

  // callBackButtonEvent. Обработка web кнопок по событию
  // crm.btnCallback([Event function]);
  crm.btnCallback(btnResponce);
  
  // обновление по кусочкам
  crm.updatePiece(pieceUpdate);

  // Инициализация библиотеки, памяти и прочих функций
  // Параметры со * обязательны.
  // crm.begin("[*Название проекта]", [*Ф-я интерфейса], [Ф-я обновления переменных], [Ф-я API], [Скорость серийного порта, доп. отладка]);
  //crm.begin("Project-28", interface, update);
  //crm.begin("Project-28", interface, NULL, NULL, 115200);
  crm.begin("DEMO Project", interface, update, api, 115200);

  // Авторизация в веб интерфейсе.
  // Параметры со * обязательны.
  // crm.setWebAuth("[*Имя пользователя]", "[Пароль]");
  //crm.setWebAuth("admin", "admin");

  // Авторизация на устройстве для API запросов. Без setWebAuth не работает.
  // Пример запроса: http://IP/api?k=d1h6d5&p1=2&...,
  //  где первый параметр должен быть ключ, имя параметра любое
  // crm.setApiKey("[API ключ]");
  //crm.setApiKey("d1h6d5");

  // Задать лицензионный ключ
  // Позволяет отключить уведомление о бесплатной версии, а так же задать свои контакты.
  // Переменные со * обязательны.
  // crm.license([*Лицензионный ключ], [Электронная почта], [Телеграм], [Домашняя страница]);
  //crm.license("5s72to1", "crm.dev@bk.ru", "user624", "https://github.com/WonderCRM/CRMui3");

  // Версия прошивки вашего проекта, если не используется, то отображается версия CRMui
  // crm.version ("[Любая строка]");
  crm.version("1.2.3.4.5");

  // Аналог FreeRTOS
  // NAME.once_ms(ms, Fn); - Выполнить единожды через указанный интервал
  // NAME.attach_ms(ms, Fn); - Цикличное выполнение через указанный интервал
  // NAME.detach(); - Деактивировать
  myLoop.attach_ms(2000, myLoopRun);

  // crm.wifiScan()
  // Возвращает список найденных точек доступа в виде JSON строки.
  // Переменные: s - статус / количество сетей; n - массив сетей [Имя, канал, rssi, шифрование], ...
  // Статус: -2 - сканирование не запущено; -1 - сканирует диапазоны; 0+ - количество найденных сетей
  // Способ опроса асинхронный, задержка минимум, ответ по готовности при следующем запросе

  // Конвертирование uint64_t в String
  // crm.uint64ToStr(uint64_t);
  //
  // Только для ESP32
  //
  // Глубокий / Лёгкий сон
  // Режим: 1 - глубокий, 0 - Лёгкий (сохраняются значения всех переменных)
  // crm.espSleep([Время в секундах], [режим]);
}


void loop() {
  // Обслуживание системных функций библиотеки
  crm.run();

  // Проверка состояния нажатия совтовых кнопок. Проверка не обязательна.
  if (crm.btnSwStatus()) {
    // Проверка конкретных кнопок на нажатие
    // crm.btnCallback("[ID кнопки]", [Функция для выполнения]);
    crm.btnCallback("reboot", reboot);    // Check "reboot" SW button
    crm.btnCallback("card4", card_sw4);   // Check "card4" SW button
    crm.btnCallback("card5", card_sw5);   // Check "card5" SW button
    crm.btnCallback("b3", tablt2);        // Check "b3" SW button
  }
  // Проверка аппаратных кнопок на нажатие
  // crm.btnCallback("[пин подключения кнопки]", [Функция для выполнения], [уровень при нажатии]);
  crm.btnCallback(4, hw_butt, LOW);      // Check pin4 HW button
}