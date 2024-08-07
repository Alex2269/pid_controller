### Короткий посібник із використання fontconvert.c для створення власних шрифтів за допомогою MinGW.

 #### КРОК 1: ВСТАНОВЛЕННЯ MinGW

 Установіть MinGW (мінімалістичний GNU для Windows) із [MinGW.org](http://www.mingw.org/).
 Уважно прочитайте інструкції на [сторінці початку роботи](http://www.mingw.org/wiki/Getting_Started).
 Я пропоную встановити за допомогою «Інсталятора графічного інтерфейсу користувача».
 Щоб завершити початкову інсталяцію, вам слід інсталювати кілька «пакетів».
 Для нашої мети вам слід інсталювати лише пакети «Базове налаштування».
 Щоб зробити це:

 1. Відкрийте менеджер встановлення MinGW
 2. На панелі ліворуч натисніть «Основне налаштування».
 3. На правій панелі виберіть «mingw32-base», «mingw-gcc-g++», «mingw-gcc-objc» і «msys-base»
 і натисніть «Позначити для встановлення»
 4. У меню натисніть «Встановлення», а потім «Застосувати зміни».  У спливаючому вікні виберіть «Застосувати».


 #### КРОК 2: ВСТАНОВЛЕННЯ Freetype Library

 Щоб прочитати про проект freetype, відвідайте [freetype.org](https://www.freetype.org/).
 Щоб завантажити останню версію freetype, перейдіть на [сторінку завантаження](http://download.savannah.gnu.org/releases/freetype/)
 і виберіть файл «freetype-2.7.tar.gz» (або новішу версію, якщо доступна).
 Щоб уникнути довгих команд cd пізніше в командному рядку, я пропоную вам розархівувати файл у каталозі C:\.
 (Я також перейменував папку на "ft27")
 Перш ніж створювати бібліотеку, корисно прочитати ці статті:
 * [Використання MSYS з MinGW](http://www.mingw.org/wiki/MSYS)
 * [Встановлення та використання додаткових бібліотек з MinGW](http://www.mingw.org/wiki/LibraryPathHOWTO)
 * [Включити шлях](http://www.mingw.org/wiki/IncludePathHOWTO)

 Усередині розархівованої папки є ще одна папка під назвою "docs".  Відкрийте його та прочитайте INSTALL.UNIX (за допомогою блокнота).
 Зверніть увагу на пункт 3 (Створення та встановлення бібліотеки).  Отже, починаємо установку.
 Щоб надати відповідні команди, ми будемо використовувати командний рядок MSYS (а не cmd.exe Windows), який схожий на UNIX.
 Дотримуйтеся шляху C:\MinGW\msys\1.0 і двічі клацніть «msys.bat».  З’явиться середовище командного рядка.
 Введіть каталог "ft27" за допомогою команд cd:
 ```
 CDC
 cd футів 27
 ```

 а потім одну за одною введіть команди:
 ```
 ./configure --prefix=/mingw
 зробити
 зробити інсталяцію
 ```
 Після того, як ви закінчите, увійдіть до "C:\MinGW\include", і там має бути нова папка з назвою "freetype2".
 Це, сподіваюся, означає, що ви правильно встановили бібліотеку!!

 #### КРОК 3: Створіть fontconvert.c

 Перш ніж продовжити, я пропоную вам створити копію папки Adafruit_GFX_library у каталозі C:\.
 Потім у папці «fontconvert» відкрийте «makefile» за допомогою редактора (я використовував блокнот ++).
 Змініть команди, щоб у підсумку програма виглядала так:
 ```
all: fontconvert

CC     = gcc
CFLAGS = -Wall -I c:/mingw/include/freetype2
LIBS   = -lfreetype

fontconvert: fontconvert.c
	$(CC) $(CFLAGS) $< $(LIBS) -o $@
	strip $@

clean:
	rm -f fontconvert
 ```
 Поверніться в командний рядок і за допомогою команди cd увійдіть до каталогу fontconvert.
 ```
 cd /c/adafruit_gfx_library\fontconvert
 ```
 Дайте команду:
 ```
 make
 ```
 Ця команда, зрештою, створить файл "fontconvert.exe" у каталозі fontconvert.

 #### КРОК 4: створіть власні файли заголовків шрифтів

 Тепер, коли у вас є виконуваний файл, ви можете використовувати його для створення власних шрифтів для роботи з Adafruit GFX lib.
 Отже, якщо ми припустимо, що у вас уже є файл .ttf із вашими улюбленими шрифтами, перейдіть до командного рядка та введіть:
 ```
 ./fontconvert yourfonts.ttf 9 > yourfonts9pt7b.h

 ./fontconvert Ubuntu.ttf 8 > Ubuntu8pt7b.h
 ./fontconvert Ubuntu.ttf 9 > Ubuntu9pt7b.h
 ./fontconvert Ubuntu.ttf 10 > Ubuntu10pt7b.h
 ./fontconvert Ubuntu.ttf 11 > Ubuntu11pt7b.h
 ./fontconvert Ubuntu.ttf 12 > Ubuntu12pt7b.h

 ```
 Ви можете прочитати більше деталей на: [learn.adafruit](https://learn.adafruit.com/adafruit-gfx-graphics-library/using-fonts).

 Тараааааммм!!  ви щойно створили новий файл заголовка шрифту.  Помістіть його в папку "Шрифти", візьміть чашку кави
 і почніть грати зі своїм проектом модуля відображення Arduino (або будь-яким іншим ....)+.
