--города с 3 или менее государственными школами
SELECT "city", COUNT("name") AS 'number of public schools'
FROM "schools"
WHERE "type" LIKE "%Public%"
GROUP BY "city"
HAVING "number of public schools" <= 3
ORDER BY "number of public schools" DESC, "city";
