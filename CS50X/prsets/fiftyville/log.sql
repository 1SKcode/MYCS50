-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Посмотрел что находится в таблице crime_scene_reports
SELECT * FROM crime_scene_reports LIMIT 10;

-- Происшесвтвие произошло 28 числа 7 месяца на улице 'Humphrey Street'
-- Выведем описание преступления за этот день в этом месте

SELECT description FROM crime_scene_reports WHERE day = 28 AND month = 7 AND street = 'Humphrey Street';

--description--
--Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
--Interviews were conducted today with three witnesses who were present at
--the time – each of their interview transcripts mentions the bakery.
--Littering took place at 16:36. No known witnesses.

--Идем смотреть отчеты допросов в нужное время с упоминанием пекарни.
 SELECT transcript FROM interviews WHERE day = 28 AND month = 7 AND transcript LIKE '%bakery%';

--Узнаем о: 1. Есть камеры наблюдения со стоянки! Можно посмотреть кто отъезжал в это время
--2. Про банкомат и улицу, где вор снимал деньги
--3. Авиабилеты.Он с кем-то говорил меньше минуты. Договорились вылетить САМЫМ РАННИМ РЕЙСОМ. Покупал билеты НЕ ОН а СООБЩНИК

--1. Смотрим bakery_security_logs в этот день в это время
SELECT * FROM bakery_security_logs WHERE day = 28 AND month = 7 AND year = 2021 AND hour = 10 AND minute >= 15 AND minute <= 25;
--Видим  несколько результатов.
--OK. Теперь ищем людей за этими номерными знаками

SELECT p.name
FROM people p
WHERE EXISTS (
   SELECT 1
   FROM bakery_security_logs
   WHERE p.license_plate = bakery_security_logs.license_plate
     AND bakery_security_logs.day = 28 AND bakery_security_logs.month = 7
     AND bakery_security_logs.year = 2021 AND bakery_security_logs.hour = 10
     AND bakery_security_logs.minute BETWEEN 15 AND 25
);

--2. Второй свидетель дал показания о месте и времени съема денег из банкомата

SELECT * FROM atm_transactions
WHERE year = 2021 AND month = 7
AND day = 28 AND atm_location = 'Leggett Street';

--OK. Есть список

--Ищем имена людей по их счету
SELECT people.name
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE EXISTS (
   SELECT 1
   FROM atm_transactions
   WHERE bank_accounts.account_number = atm_transactions.account_number
     AND year = 2021 AND month = 7
     AND day = 28 AND atm_location = 'Leggett Street'
);
--Супер. Запоним это!

-- Третий свидетей давший показания сказал о телефонном звонке. Узнаем это:
SELECT caller FROM phone_calls
WHERE year = 2021 AND month = 7 AND day = 28
AND duration <= 60; --Говорил меньше минуты!!

--имена звонящих

SELECT people.name FROM people
JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE phone_calls.year = 2021 AND phone_calls.month = 7 AND phone_calls.day = 28
AND phone_calls.duration <= 60;

--Ищем аэропорт города
SELECT * FROM airports
WHERE city = 'Fiftyville';

--самый ранний вылет
SELECT * FROM flights WHERE origin_airport_id = 8 AND flights.year = 2021 AND flights.month = 7 AND flights.day = 29 ORDER BY hour;

--пассажиры
SELECT people.name
FROM people
WHERE EXISTS (
   SELECT 1
   FROM passengers
   JOIN flights ON passengers.flight_id = flights.id
   JOIN airports ON flights.origin_airport_id = airports.id
   WHERE people.passport_number = passengers.passport_number
     AND airports.city = 'Fiftyville'
     AND flights.year = 2021 AND flights.month = 7 AND flights.day = 29 AND flights.hour = 8 AND flights.minute = 20
);

--куда направился
SELECT airports.city FROM airports
JOIN flights ON airports.id = flights.destination_airport_id
WHERE flights.origin_airport_id = 8
AND flights.year = 2021 AND flights.month = 7 AND flights.day = 29 AND flights.hour = 8 AND flights.minute = 20;

--ищем телефон преступника
SELECT phone_number FROM people ---(367) 555-5533 |
WHERE name = 'Bruce';

--ищем сообщника!

SELECT people.name
FROM people
INNER JOIN phone_calls ON people.phone_number = phone_calls.receiver
WHERE phone_calls.year = 2021 AND phone_calls.month = 7 AND phone_calls.day = 28
AND phone_calls.duration <= 60 AND phone_calls.caller = '(367) 555-5533';

-- ИТАК
-- Преступник:Bruce
-- Город: New York City
-- Сообщник: Robin
