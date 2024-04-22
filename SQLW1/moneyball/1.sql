--как средняя зарплата игроков менялась с течением времени.
SELECT "year", ROUND(AVG("salary"), 2) AS 'average salary'
FROM "salaries"
GROUP BY "year"
ORDER BY "year" DESC;
