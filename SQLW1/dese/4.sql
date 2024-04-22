--10 городов с наибольшим количеством государственных школ
SELECT "city", COUNT("name") AS 'number of public schools'
FROM "schools"
WHERE "type" LIKE "%Public%"
GROUP BY "city"
ORDER BY "number of public schools" DESC, "city"
LIMIT 10;
