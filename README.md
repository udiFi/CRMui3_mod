# CRMui3 WebFramework для esp8266 и esp32

## Описание проекта
**CRMui3** библиотека для Arduino IDE. Эта библиотека модифицированная от версии CRMui3 v.1.2.5 30 Dec 2021
"Ключи" CRMui3 работают и тут. Я нахожусь в telegram чате проэкта CRMui3.
[**Полная информация о библиотеке тут**](https://github.com/WonderCRM/CRMui3)

## Железо
Совместим с микроконтроллерами на ESP8266 (**ESP-12F лучше**) но не желательно вооще использовать и ESP32. 
У старых ревизий ESP-01 было замечено медленная скорость загрузки до 9кб/c и отключение wifi при загрузке.


## Отличие от оригинала

### Реализован метод который позволяет дублировать текст для сокращения размера жейсона для веб интерфейса

К примру есть какойто текст повторбщий и он раздувает размер интерфейса "Таймер 1...n"


```cpp
crm.page("&#xe81e; Таймер");
  crm.addReplause(1,"Таймер");
  crm.addReplause(2,"Таймер");
  for (size_t i = 0; i < 4; i++)
  {
    crm.output({OUTPUT_TEXT, "", "", "$1 " + String(i+1), "#ff5"});
    crm.output({OUTPUT_TEXT, "", "", "$2 " + String(i+1), "#ff5"});
  }
```
$nnn

crm.addReplause обновляется каждый раз при запросе интерфейса и если нужно скрывать то можно просто не обрабатывать. А если у вас отображается $1 то вы не установили книму текст.


### Реализован метод который позволяет работать веб интерфейсу не через конфиг
(Можно работать с web некоторыми элементами без сохранения в flash)
```cpp
crm.updatePiece(pieceUpdate);

crm.select({INPUT_SELECT_PIECE_UP,"select4", "Обновление без конфига", String(select4), {{"Отправить 0", "0"}, {"Отправить 1", "1"}}});

void pieceUpdate(String paramName, String value) {
  if(paramName == "select4"){
    select4 = !select4;
    Serial.printf("[Update_P] Select обновлен на %s без конфига\n",value.c_str());
    crm.webUpdate();// Если оно должно обновить все окно
  }
}
```
Что может использоваться
```cpp
INPUT_CHECKBOX_PIECE_UP

INPUT_PASSWORD_PIECE_UP
INPUT_TEXT_PIECE_UP
INPUT_COLOR_PIECE_UP
INPUT_DATE_PIECE_UP
INPUT_DATETIME_PIECE_UP
INPUT_TIME_PIECE_UP
INPUT_NUMBER_PIECE_UP

INPUT_SELECT_PIECE_UP
INPUT_EMAIL_PIECE_UP
```
### Реализован подобие pwa приложения
На экране приложения в момент загрузки будет отображается красивая иконка и название приложения.
Это работает в данный момент в любом браузере.

![PROJECT_PHOTO](https://github.com/udiFi/CRM3_mod/blob/main/portal-to-pwa.png)

### Поиск WiFi в web
В поиске WiFi найденные сети не дергаются и следущие поиски отображаются ниже. Если нет WiFi то отображается серым.

### Конфиг и интерфейс
В больших приложениях была поломка json из-за особенностей библиотеки ESPAsyncWebServer. Было разделено конфиг и веб интерфейс.
Для уменьшения конфига для CHECKBOX добавлен метод var_bool для получения булевого значения так как изменено строку "true" и "false" на "1" и "0". Если использовать "true" и "false" веб интерфейс поймет, но на esp передается "1" и "0";
var_bool возвращает false если не совпало значение с 1 или true.

### Бывшие баги
При работе с несколькими открытыми вкладками отображает все действия..

Renge не удваивает полоску в отображении.

20.08.2022 Баги с выгрузкой исправлены 
