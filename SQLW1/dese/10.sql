--10 государственных школьных округов с самыми высокими расходами на одного ученика.
SELECT "name", "per_pupil_expenditure"
FROM "districts"
JOIN "expenditures" ON "expenditures"."district_id" = "districts"."id"
WHERE "type" LIKE '%Public%'
ORDER BY "per_pupil_expenditure"
DESC LIMIT 10;
